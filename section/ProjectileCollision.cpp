#include "include/moho.h"

enum LayerCallback {
    LAYERCALLBACK_None,
    LAYERCALLBACK_OnExitWater,
    LAYERCALLBACK_OnEnterWater,
};

void __thiscall Projectile::CheckWorldCollision(Segment3f* movement) {
    if (! this->collideSurface) {
        return;
    }

    STIMap* mapData = this->sim->mapData;
    float distMoved = movement->Extent * 2.0;
    
    float terrainDist = pInf;
    GeomLine3 line{
        movement->Origin - movement->Direction * movement->Extent,
        movement->Direction,
        0.0,
        distMoved
    };
    Vector3f hitPos;
    CGeomHitResult terrainHit{NaN, NaN};
    if (mapData->heightField->Intersection(&line, &hitPos, &terrainHit)->IsntNaN()) {
        terrainDist = terrainHit.distance;
        this->impactInterp = terrainDist / distMoved;
        this->impactPosition = hitPos;
        this->impactType = Moho::IMPACT_Terrain;
    }
    if (! mapData->hasWater) {
        return;
    }

    LayerCallback layercallback = LAYERCALLBACK_None;
    if (this->belowWater) {
        if (this->nextPos.y > mapData->waterLevel) {
            layercallback = LAYERCALLBACK_OnExitWater;
        }
    } else {
        if (mapData->waterLevel > this->nextPos.y) {
            layercallback = LAYERCALLBACK_OnEnterWater;
        }
    }
    if (this->destroyOnWater || (layercallback && terrainDist != pInf)) {
        Vector3f *curPos = &this->sstiData.pos;
        Plane3f waterPlane{{0.0, 1.0, 0.0}, mapData->waterLevel};
        Vector3f dif{this->nextPos - *curPos};
        CColHitResult waterHit{NaN, NaN, 0, 0};
        Vector3f normDif;
        dif.Normalize(&normDif);
        GeomLine3 dirLine{*curPos, normDif, nInf, pInf};
        dirLine.PlaneIntersection(&waterPlane, &waterHit, &dif);
        float waterDist = waterHit.distance;
        if (this->destroyOnWater && terrainDist > waterDist) {
            if (dif.IsntNaN()) {
                this->impactInterp = waterDist / distMoved;
                this->impactPosition = dif;
                this->impactType = Moho::IMPACT_Water;
            } else {
                this->impactInterp = 0.0;
                this->impactPosition = *curPos;
                this->impactType = Moho::IMPACT_Water;
            }
        }
        if (terrainDist < waterDist) {
            layercallback = LAYERCALLBACK_None;
        }
    }
    if (layercallback != LAYERCALLBACK_None) {
        if (layercallback == LAYERCALLBACK_OnExitWater) {
            this->SetCurrentLayer(Moho::LAYER_Air);
            this->Callback("OnExitWater");
            this->belowWater = false;
        } else {
            this->SetCurrentLayer(Moho::LAYER_Water);
            this->Callback("OnEnterWater");
            this->belowWater = true;
        }
    }
}
