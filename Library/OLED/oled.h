#ifndef _OLED_H_
#define _OLED_H_

#include "stdint.h"
#include "stdbool.h"

enum OLED_color{
	brack,
	red,
	blue,
	green,
	white
};


void OLEDSetColor(uint8_t  C,uint8_t B, uint8_t A);
void OLEDInit();
void OLEDSetting();
void OLEDOn();
void OLEDOff();
void OLEDOnDim();
void OLEDFillEnable(bool fill,bool copy);
void OLEDFillc(uint8_t C,uint8_t B, uint8_t A);
void OLEDFill();
void OLEDClear();
void OLEDPointc(uint8_t x,uint8_t y,uint8_t C,uint8_t B, uint8_t A);
void OLEDPoint(uint8_t x,uint8_t y);
void OLEDLine(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2, uint8_t C,uint8_t B, uint8_t A);
void OLEDRectc(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2);
void OLEDRect(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2,uint8_t C,uint8_t B,uint8_t A,uint8_t Carea,uint8_t Barea,uint8_t Aarea);
void OLEDLogo();

#endif //_OLED_H_
