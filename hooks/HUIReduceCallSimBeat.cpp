asm(
  //Do not call sim beat when camera move start/end
  ".section h0; .set h0,0x73B3B0;"
  ".byte 0xEB;"

  //Do not call sim beat when unit selected/deselected
  ".section h1; .set h1,0x73B43D;"
  ".byte 0xEB;"

  //Do not call sim beat when ordering a unit
  ".section h2; .set h2,0x73CBC9;"
  ".byte 0xEB;"

  /*Do not call sim beat when pause
  ".section h3; .set h3,0x73C6AD;"
  ".byte 0xEB;"

  //Do not call sim beat when remove build order of factory
  ".section h4; .set h4,0x73CDA5;"
  ".byte 0xEB;"

  //Do not call sim beat when set factory waypoint
  ".section h5; .set h5,0x73CC69;"
  ".byte 0xEB;"*/
);