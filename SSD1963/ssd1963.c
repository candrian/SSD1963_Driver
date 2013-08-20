#define F_CPU 8000000UL
//
//  ssd1963.c
//  SSD1963
//
//  Created by candrian on 8/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <util/delay.h>     // Blocking delay functions
#include "ssd1963.h"

unsigned int    HDP=799;    //Horizontal Display Period
unsigned int    HT=1000;    //Horizontal Total
unsigned int    HPS=51;     //LLINE Pulse Start Position
unsigned int    LPS=3;      //Horizontal Display Period Start Position
unsigned char   HPW=8;      //LLINE Pulse Width
unsigned int    VDP=479;    //Vertical Display Period
unsigned int    VT=530;     //Vertical Total
unsigned int    VPS=24;     //LFRAME Pulse Start Position
unsigned int    FPS=23;     //Vertical Display Period Start Positio
unsigned char   VPW=3;      //LFRAME Pulse Width

void LCD_init(){
    
    //Configure outputs
    CONTROL_DDR     |=  (1<<CS) | (1<<RS) | (1<<WR) | (1<<RD);
    DDR_DATA0_7     =   0xFF;
    DDR_DATA8_13    |=  (1<<DATA8) | (1<<DATA9) | (1<<DATA10) | (1<<DATA11) | (1<<DATA12) | (1<<DATA13);
    DDR_DATA14_15   |=  (1<<DATA14) | (1<<DATA15);
    
    
    CONTROL_PORT    |=  (1<<CS);
    CONTROL_PORT    |=  (1<<RD);
    CONTROL_PORT    |=  (1<<WR);
    CONTROL_PORT    |=  (1<<RS);
    
	_delay_ms(100);	

	LCD_Instruction(set_pll_mn);	
	LCD_Write_DATA(0x0023);
	LCD_Write_DATA(0x0002);
	LCD_Write_DATA(0x0004);
    
	LCD_Instruction(set_pll);       //PLL enable
	LCD_Write_DATA(0x0001);
    
	_delay_ms(1);	
    
	//LCD_Instruction(set_pll);
	LCD_Write_DATA(0x0003);
    
	_delay_ms(10);	
    
	LCD_Instruction(soft_reset);    //Software reset
    
	_delay_ms(5);	
    
	LCD_Instruction(set_lshift_freq);	
	LCD_Write_DATA(0x0004);
	LCD_Write_DATA(0x0093);
	LCD_Write_DATA(0x00e0);	
    
	LCD_Instruction(set_lcd_mode_);     //LCD SPECIFICATION
	LCD_Write_DATA(0x0000);
	LCD_Write_DATA(0x0000);
	LCD_Write_DATA((HDP>>8)&0X00FF);    //Set HDP
	LCD_Write_DATA(HDP&0X00FF);
    LCD_Write_DATA((VDP>>8)&0X00FF);    //Set VDP
	LCD_Write_DATA(VDP&0X00FF);
    LCD_Write_DATA(0x0000);
    
	LCD_Instruction(set_hori_period);   //HSYNC
	LCD_Write_DATA((HT>>8)&0X00FF);     //Set HT
	LCD_Write_DATA(HT&0X00FF);
	LCD_Write_DATA((HPS>>8)&0X00FF);    //Set HPS
	LCD_Write_DATA(HPS&0X00FF);
	LCD_Write_DATA(HPW);                //Set HPW
	LCD_Write_DATA((LPS>>8)&0X00FF);    //Set HPS
	LCD_Write_DATA(LPS&0X00FF);
	LCD_Write_DATA(0x0000);
    
	LCD_Instruction(set_vert_period);	//VSYNC
	LCD_Write_DATA((VT>>8)&0X00FF);     //Set VT
	LCD_Write_DATA(VT&0X00FF);
	LCD_Write_DATA((VPS>>8)&0X00FF);    //Set VPS
	LCD_Write_DATA(VPS&0X00FF);
	LCD_Write_DATA(VPW);                //Set VPW
	LCD_Write_DATA((FPS>>8)&0X00FF);    //Set FPS
	LCD_Write_DATA(FPS&0X00FF);		
    
	LCD_Instruction(set_gpio_value);
	LCD_Write_DATA(0x000F);             //GPIO[3:0] out 1
    
	LCD_Instruction(set_gpio_conf);
	LCD_Write_DATA(0x0007);             //GPIO3=input, GPIO[2:0]=output
	LCD_Write_DATA(0x0001);             //GPIO0 normal
    
	LCD_Instruction(set_address_mode);  //rotation
	LCD_Write_DATA(0x0000);		
    
	LCD_Instruction(set_pixel_data_interface);  //pixel data interface
	LCD_Write_DATA(0x0003);		
    
	_delay_ms(5);			
    
	LCD_Instruction(set_gamma_curve);   
	LCD_Write_DATA(0x0008);             //Gamma curve 3
    
	LCD_Write_DATA(set_display_on);     //display on
    
	LCD_Instruction(set_pwm_conf);      //set PWM for B/L
	LCD_Write_DATA(0x0001);
	LCD_Write_DATA(0x0088);             //medium backlight
	LCD_Write_DATA(0x0001);
	LCD_Write_DATA(0x00F0);
	LCD_Write_DATA(0x0000);
	LCD_Write_DATA(0x0000);
    
    CONTROL_PORT    |=  (1<<CS);
    CONTROL_PORT    |=  (1<<RD);
    CONTROL_PORT    |=  (1<<WR);
    CONTROL_PORT    |=  (1<<RS);
    
   }

void LCD_Instruction(uint8_t  command)    {  

    //Select Command mode
    CONTROL_PORT    &=  ~(1<<RS);
    
    //Chip Select
    CONTROL_PORT    &=  ~(1<<CS);
    //Stop Read if exists
    CONTROL_PORT    |=  (1<<RD);

    LCD_Write_Bus(command, COMMAND);
    
    //Write signal
    CONTROL_PORT    &=  ~(1<<WR);
    //Stop Write cycle
    CONTROL_PORT    |=  (1<<WR);
    //Chip unselect
    CONTROL_PORT    |=  (1<<CS);

}

void LCD_Write_DATA(uint8_t  data)    {  

    //Select Data mode
    CONTROL_PORT    |=  (1<<RS);
    
    //Chip Select
    CONTROL_PORT    &=  ~(1<<CS);
    //Stop Read if exists
    CONTROL_PORT    |=  (1<<RD);

    LCD_Write_Bus(data, DATA);
    
    //Write signal
    CONTROL_PORT    &=  ~(1<<WR);
    CONTROL_PORT    |=  (1<<WR);
    
    //Chip unselect
    CONTROL_PORT    |=  (1<<CS);
 
}


void LCD_Write_Bus(uint16_t data, uint8_t type){
    
    PORT_DATA0_7    =   data;
    
    if (type==DATA) {
        
        PORT_DATA8_13   =   data>>8;
        data            =   data>>14;
        if (data&0x01==1) {
            PORT_DATA14_15  |=  (1<<PB0);
        }else{
            PORT_DATA14_15  &=  ~(1<<PB0);
        }
        data            =   data>>1;
        if (data&0x01==1) {
            PORT_DATA14_15  |=  (1<<PB1);
        }else{
            PORT_DATA14_15  &=  ~(1<<PB1);
        }
    }
}

void adjust_backlight(uint8_t PWM_Value){
    // 	if(PWM_Value==255) PWM_Value=0;
    // 	else if (PWM_Value==0) PWM_Value=255;
	LCD_Instruction(set_pwm_conf); //set PWM for B/L
	LCD_Write_DATA(0x0001);
	LCD_Write_DATA(PWM_Value);
	LCD_Write_DATA(0x0001);
	LCD_Write_DATA(0x00F0);
	LCD_Write_DATA(0x0000);
	LCD_Write_DATA(0x0000);
}

void LCD_Set_AREA(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2){
    LCD_Instruction(set_column_address);
    LCD_Write_DATA(x1>>8);
    LCD_Write_DATA(0x00FF&x1); 
    LCD_Write_DATA(x2>>8);
    LCD_Write_DATA(0x00FF&x2);      
    
    LCD_Instruction(set_page_address);
    LCD_Write_DATA(y1>>8);
    LCD_Write_DATA(0x00FF&y1);
    LCD_Write_DATA(y2>>8);
    LCD_Write_DATA(0x00FF&y2); 
    
    //LCD_Instruction(WriteDatatoGRAM);
    
}

void show_colour_bar(void){
	unsigned int i,j;
	LCD_Instruction(write_memory_start);
    for(i=0;i<480UL;i++){
        for(j=0;j<800UL;j++){
            if(i>400UL)LCD_Write_DATA(White);
            else if(i>350)LCD_Write_DATA(Blue);
            else if(i>300)LCD_Write_DATA(Green);
            else if(i>250)LCD_Write_DATA(Cyan);
            else if(i>200)LCD_Write_DATA(Red);
            else if(i>150)LCD_Write_DATA(Blue2);	  
            else if(i>100)LCD_Write_DATA(Magenta);
            else if(i>50)LCD_Write_DATA(Yellow);
            else LCD_Write_DATA(Black);
        }	 
    }
}

void LCD_Fill(unsigned long color){
	unsigned int j,m;
	unsigned long ia;
	LCD_Instruction(write_memory_start);
    
    for(ia=0;ia<384000UL;ia++){
        LCD_Write_DATA(color);
    }
    
}

