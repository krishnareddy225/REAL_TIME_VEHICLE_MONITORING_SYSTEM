#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "adc.h"
#include "adc_defines.h"
#include "types.h"
#include "interrupt.h"
#include "can.h"
#include "can_defines.h"
#define Min 0.43
#define Max 2.45

u32 adcval;
f32 ear;
u32 fuel_per;

main(){
	CANF txF;
	Init_CAN1();
	init_adc();
	txF.ID=2;
	txF.vbf.RTR=0;
	txF.vbf.DLC=1;
	//txF.Data1=1;
	//txF.Data2=0;
	while(1){
		read_adc(1,&adcval,&ear);
		fuel_per = ((ear-Min)/(Max-Min))*100;	 
		delay_ms(500); 
		txF.Data1=fuel_per;
		txF.Data2=0;
		CAN1_Tx(txF);		
		txF.Data1=((~txF.Data1)&0x0);
	}
}


