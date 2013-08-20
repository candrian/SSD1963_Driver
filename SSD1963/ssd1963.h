#define CS  PB6 //STK500 -> XT1
#define RS  PB7 //STK500 -> XT2
#define WR  PB2
#define RD  PB4

#define CONTROL_PORT    PORTB
#define CONTROL_DDR     DDRB

#define DATA0   PD0
#define DATA1   PD1
#define DATA2   PD2
#define DATA3   PD3
#define DATA4   PD4
#define DATA5   PD5
#define DATA6   PD6
#define DATA7   PD7

#define DATA8   PC0
#define DATA9   PC1
#define DATA10  PC2
#define DATA11  PC3
#define DATA12  PC4
#define DATA13  PC5

#define DATA14  PB0
#define DATA15  PB1

#define PORT_DATA0_7    PORTD
#define PORT_DATA8_13   PORTC
#define PORT_DATA14_15  PORTB

#define DDR_DATA0_7     DDRD
#define DDR_DATA8_13    DDRC
#define DDR_DATA14_15   DDRB

#define DATA    0
#define COMMAND 1


#define nop                 0x00
#define soft_reset          0x01
#define get_power_mode      0x0A
#define get_address_mode    0x0B
#define get_pixel_format    0x0C
#define get_display_mode    0x0D
#define get_signal_mode     0x0E
#define enter_sleep_mode    0x10
#define exit_sleep_mode     0x11
#define enter_partial_mode  0x12
#define enter_normal_mode   0x13
#define exit_invert_mode    0x20
#define enter_invert_mode   0x21
#define set_gamma_curve     0x26
#define set_display_off     0x28
#define set_display_on      0x29
#define set_column_address  0x2A
#define set_page_address    0x2B
#define write_memory_start  0x2C
#define read_memory_start   0x2E
#define set_partial_area    0x30
#define set_scroll_area     0x33
#define set_tear_off        0x34
#define set_tear_on         0x35
#define set_address_mode    0x36
#define set_scroll_start    0x37
#define exit_idle_mode      0x38
#define enter_idle_mode     0x39
#define set_pixel_format    0x3A
#define write_memory_continue   0x3C
#define read_memory_continue    0x3E
#define set_tear_scanline   0x44
#define get_scanline        0x45
#define read_ddb            0xA1
#define set_lcd_mode_       0xB0
#define get_lcd_mode        0xB1
#define set_hori_period     0xB4
#define get_hori_period     0xB5
#define set_vert_period     0xB6
#define get_vert_period     0xB7
#define set_gpio_conf       0xB8
#define get_gpio_conf       0xB9
#define set_gpio_value      0xBA
#define get_gpio_status     0xBB
#define set_post_proc       0xBC
#define get_post_proc       0xBD
#define set_pwm_conf        0xBE
#define get_pwm_conf        0xBF
#define set_lcd_gen0        0xC0
#define get_lcd_gen0        0xC1
#define set_lcd_gen1        0xC2
#define get_lcd_gen1        0xC3
#define set_lcd_gen2        0xC4
#define get_lcd_gen2        0xC5
#define set_lcd_gen3        0xC6
#define get_lcd_gen3        0xC7
#define set_gpio0_rop       0xC8
#define get_gpio0_rop       0xC9
#define set_gpio1_rop       0xCA
#define get_gpio1_rop       0xCB
#define set_gpio2_rop       0xCC
#define get_gpio2_rop       0xCD
#define set_gpio3_rop       0xCE
#define get_gpio3_rop       0xCF
#define set_dbc_conf        0xD0
#define get_dbc_conf        0xD1
#define set_dbc_th          0xD4
#define get_dbc_th          0xD5
#define set_pll             0xE0
#define set_pll_mn          0xE2
#define get_pll_mn          0xE3
#define get_pll_status      0xE4
#define set_deep_sleep      0xE5
#define set_lshift_freq     0xE6
#define get_lshift_freq     0xE7
#define set_pixel_data_interface    0xF0
#define get_pixel_data_interface    0xF1

#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
#define Gray		   0x2104
#define PURPLE		   0xF11F
#define Orange         0xFD20


/*
 LCD_Write_COM(set_pll_mn);          //PLL multiplier, set PLL clock to 120M
 LCD_Write_DATA(0x1E);               //N=0x36 for 6.5M, 0x23 for 10M crystal
 LCD_Write_DATA(0x02);
 LCD_Write_DATA(0x54);
 
 LCD_Write_COM(0xE0);                //PLL enable
 LCD_Write_DATA(0x01);
 
 _delay_ms(10);
 
 LCD_Write_COM(set_pll);
 LCD_Write_DATA(0x03);
 
 _delay_ms(10);
 
 LCD_Write_COM(soft_reset);          //Software reset
 
 _delay_ms(100);
 
 LCD_Write_COM(set_lshift_freq);		//PLL setting for PCLK, depends on resolution
 LCD_Write_DATA(0x03);
 LCD_Write_DATA(0xFF);
 LCD_Write_DATA(0xFF);
 
 LCD_Write_COM(set_lcd_mode_);		//LCD SPECIFICATION
 LCD_Write_DATA(0x24);
 LCD_Write_DATA(0x00);
 LCD_Write_DATA(0x03);               //Set HDP	799
 LCD_Write_DATA(0x1F);
 LCD_Write_DATA(0x01);               //Set VDP	479
 LCD_Write_DATA(0xDF);
 LCD_Write_DATA(0x00);
 
 LCD_Write_COM(set_hori_period);		//HSYNC
 LCD_Write_DATA(0x03);               //Set HT	928
 LCD_Write_DATA(0xA0);
 LCD_Write_DATA(0x00);               //Set HPS	46
 LCD_Write_DATA(0x2E);
 LCD_Write_DATA(0x30);               //Set HPW	48
 LCD_Write_DATA(0x00);               //Set LPS	15
 LCD_Write_DATA(0x0F);
 LCD_Write_DATA(0x00);
 
 LCD_Write_COM(set_vert_period);		//VSYNC
 LCD_Write_DATA(0x02);               //Set VT	525
 LCD_Write_DATA(0x0D);
 LCD_Write_DATA(0x00);               //Set VPS	16
 LCD_Write_DATA(0x10);
 LCD_Write_DATA(0x10);               //Set VPW	16
 LCD_Write_DATA(0x00);               //Set FPS	8
 LCD_Write_DATA(0x08);
 
 LCD_Write_COM(set_gpio_value);
 LCD_Write_DATA(0x0F);               //GPIO[3:0] out 1
 
 LCD_Write_COM(set_gpio_conf);
 LCD_Write_DATA(0x07);               //GPIO3=input, GPIO[2:0]=output
 LCD_Write_DATA(0x01);               //GPIO0 normal
 
 LCD_Write_COM(set_address_mode);	//rotation
 LCD_Write_DATA(0x22);
 
 LCD_Write_COM(set_pixel_data_interface);    //pixel data interface
 LCD_Write_DATA(0x03);
 
 _delay_ms(1);
 
 //setXY(0, 0, 799, 479);
 LCD_Write_COM(set_display_on);		//display on
 
 LCD_Write_COM(set_pwm_conf);		//set PWM for B/L
 LCD_Write_DATA(0x06);
 LCD_Write_DATA(0xf0);
 LCD_Write_DATA(0x01);
 LCD_Write_DATA(0xf0);
 LCD_Write_DATA(0x00);
 LCD_Write_DATA(0x00);
 
 LCD_Write_COM(set_dbc_conf); 
 LCD_Write_DATA(0x0d);	
 
 LCD_Write_COM(write_memory_start); 
 */

