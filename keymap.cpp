#include "keymap.h"

int translate_key_to_grid(int key,int &x, int &y){
  switch(key){

  case 0x5a: /*z*/ x=0; y=0; return 1;
  case 0x58: /*x*/ x=1; y=0; return 1;
  case 0x43: /*c*/ x=2; y=0; return 1;
  case 0x56: /*v*/ x=3; y=0; return 1;
  case 0x42: /*b*/ x=4; y=0; return 1;
  case 0x4e: /*n*/ x=5; y=0; return 1;
  case 0x4d: /*m*/ x=6; y=0; return 1;
  case 0x2c: /*,*/ x=7; y=0; return 1;
  case 0x2e: /*.*/ x=8; y=0; return 1;
  case 0x2f: /*/*/ x=9; y=0; return 1;
  
  case 0x41: /*a*/ x=0; y=1; return 1;
  case 0x53: /*s*/ x=1; y=1; return 1;
  case 0x44: /*d*/ x=2; y=1; return 1;
  case 0x46: /*f*/ x=3; y=1; return 1;
  case 0x47: /*g*/ x=4; y=1; return 1;
  case 0x48: /*h*/ x=5; y=1; return 1;
  case 0x4a: /*j*/ x=6; y=1; return 1;
  case 0x4b: /*k*/ x=7; y=1; return 1;
  case 0x4c: /*l*/ x=8; y=1; return 1;
  case 0x3b: /*;*/ x=9; y=1; return 1;
  case 0x27: /*'*/ x=10; y=1; return 1;
  case 0x01000004: /*\n*/ x=11; y=1; return 1;

  case 0x51: /*q*/ x=0; y=2; return 1;
  case 0x57: /*w*/ x=1; y=2; return 1;
  case 0x45: /*e*/ x=2; y=2; return 1;
  case 0x52: /*r*/ x=3; y=2; return 1;
  case 0x54: /*t*/ x=4; y=2; return 1;
  case 0x59: /*y*/ x=5; y=2; return 1;
  case 0x55: /*u*/ x=6; y=2; return 1;
  case 0x49: /*i*/ x=7; y=2; return 1;
  case 0x4f: /*o*/ x=8; y=2; return 1;
  case 0x50: /*p*/ x=9; y=2; return 1;
  case 0x5b: /*[*/ x=10; y=2; return 1;
  case 0x5d: /*]*/ x=11; y=2; return 1;
  case 0x5c: /*\*/ x=12; y=2; return 1;
  case 0x01000007: /*del*/ x=13; y=2; return 1;
  case 0x01000011: /*end*/ x=14; y=2; return 1;
  case 0x01000017: /*pg down*/ x=15; y=2; return 1;

  case 0x31: /*1*/ x=0; y=3; return 1;
  case 0x32: /*2*/ x=1; y=3; return 1;
  case 0x33: /*3*/ x=2; y=3; return 1;
  case 0x34: /*4*/ x=3; y=3; return 1;
  case 0x35: /*5*/ x=4; y=3; return 1;
  case 0x36: /*6*/ x=5; y=3; return 1;
  case 0x37: /*7*/ x=6; y=3; return 1;
  case 0x38: /*8*/ x=7; y=3; return 1;
  case 0x39: /*9*/ x=8; y=3; return 1;
  case 0x30: /*0*/ x=9; y=3; return 1;
  case 0x2d: /*-*/ x=10; y=3; return 1;
  case 0x3d: /*=*/ x=11; y=3; return 1;
  case 0x01000003: /*back*/ x=12; y=3; return 1;
  case 0x01000006: /*insert*/ x=13; y=3; return 1;
  case 0x01000010: /*home*/ x=14; y=3; return 1;
  case 0x01000016: /*pg up*/ x=15; y=3; return 1;

  default:
    x=-1; y=-1; return 0;
  }
}
