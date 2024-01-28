#pragma once

#include "global.h"


// adaptation of boost 1.36 from assembly reconstruction

//namespace boost {
//namespace detail {

struct sp_counted_base : VirtualClass
{
	using virtual_class = struct vtable_sp_counted_base : vtable_ {
		void (__thiscall *dtr)(sp_counted_base *);
		void (__thiscall *dispose)(sp_counted_base *);
		void (__thiscall *destroy)(sp_counted_base *);
		void* (__thiscall *get_deleter)(sp_counted_base *);
	};
	virtual_class* Virtual() const { return reinterpret_cast<virtual_class*>(vtable); }

	int use_count_;
	int weak_count_;
	
    void add_ref_copy() {
        ++use_count_;
    }
    bool add_ref_lock() {
        if (use_count_ == 0) {
			return false;
		}
        ++use_count_;
        return true;
    }
	void release() {
        if (--use_count_ == 0) {
            Virtual()->dispose(this);
            weak_release();
        }
    }

    void weak_add_ref() {
        ++weak_count_;
    }
	void weak_release() {
		if (--weak_count_ == 0) {
			Virtual()->destroy(this);
		}
	}
};

template<class X>
struct sp_counted_impl_p : sp_counted_base
{
	X * px_;
};

template<class P, class D>
struct sp_counted_impl_pd : sp_counted_base
{
	P ptr;
	D del;
};

template<class T>
struct weak_count
{
	sp_counted_base * pi_;
	
	~weak_count() {
		if (pi_ != 0) {
			pi_->weak_release();
		}
	}
};

//} // namespace detail

template<class T>
struct weak_ptr
{
	T *px;
	weak_count<T> pn;

	T* operator->() const {
		return px;
	}
};

//} // namespace boost
