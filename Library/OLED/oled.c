#include "oled.h"
#include "spi.h"
#include "gpio.h"
#include "logo.h"

volatile uint8_t g_C;
volatile uint8_t g_B;
volatile uint8_t g_A;

void OLEDInit(){
	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET);

	HAL_SPI_Init(&hspi1);

	OLEDOff();
	OLEDOn();
	OLEDFillEnable(1,1);
	OLEDSetting();

	OLEDClear();

}

void OLEDSetColor(uint8_t  C,uint8_t B, uint8_t A){
	g_C=C;
	g_B=B;
	g_A=A;
}


void OLEDSetting(){
	uint8_t setting[2]={0xA0, 0b01100000};//QT095B用  ssd1331データシートのFigure 26参照
	HAL_SPI_Transmit(&hspi1, setting, 2, 10);

}

void OLEDOff(){
	uint8_t on_off[1]={0xAE};
	HAL_SPI_Transmit(&hspi1, on_off, 1, 10);
}
void OLEDOn(){
	uint8_t on_off[1]={0xAF};
	HAL_SPI_Transmit(&hspi1, on_off, 1, 10);
}
void OLEDDim(){
	uint8_t on_off[1]={0xAC};
	HAL_SPI_Transmit(&hspi1, on_off, 1, 10);
}
void OLEDFillEnable(bool fill,bool copy){
//	uint8_t data[2]={0x26,0x00010001};
	uint8_t data[2]={0x26,(uint8_t)fill<<0 | (uint8_t)copy<<4};
	HAL_SPI_Transmit(&hspi1, data, 2, 10);

}

void OLEDClear(){
	uint8_t data[5]={0x25,0,0,95,63};
	HAL_SPI_Transmit(&hspi1, data, 5, 100);
	HAL_Delay(1);//これ入れないと一部クリアされない


}

void OLEDFillc(uint8_t C,uint8_t B, uint8_t A){
	  OLEDRect(0, 0, 45, 63 , C,B,A, C,B,A);//分割以内とうまく描画できない(多分通信時間とかの問題
	  OLEDRect(45, 0, 95, 63 , C,B,A, C,B,A);
	  HAL_Delay(1);

}

void OLEDFill(){
	OLEDFillc(g_C, g_B, g_A);
}

void OLEDLine(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2, uint8_t C,uint8_t B, uint8_t A){
	uint8_t data[8]={0x21,c1,r1,c2,r2,C,B,A};
	HAL_SPI_Transmit(&hspi1, data, 8, 100);

}

void OLEDRect(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2,uint8_t C,uint8_t B,uint8_t A,uint8_t Carea,uint8_t Barea,uint8_t Aarea){
	uint8_t data[11]={0x22,c1,r1,c2,r2,C,B,A,Carea,Barea,Aarea};
	HAL_SPI_Transmit(&hspi1, data, 11, 100);

}

void OLEDRectc(uint8_t c1,uint8_t r1,uint8_t c2,uint8_t r2){
	OLEDRect(c1, r1, c2, r2, g_C, g_B, g_A, g_C, g_B, g_A);
}

void OLEDPointc(uint8_t x,uint8_t y,uint8_t C,uint8_t B, uint8_t A){
	OLEDLine(x, y, x, y, C, B, A);
}

void OLEDPoint(uint8_t x,uint8_t y){
	OLEDPointc(x, y, g_C, g_B, g_A);
}

void OLEDLogo(){
	for(int x=0;x<32;x++){
		for(int y=0;y<32;y++){
			OLEDSetColor(logo_c[31-y][32-x], logo_b[31-y][32-x], logo_a[31-y][32-x]);
			OLEDRectc(x*2+16, y*2,x*2+16+1, y*2+1);

		}
	}
}

