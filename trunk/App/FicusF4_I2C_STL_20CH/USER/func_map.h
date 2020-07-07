#ifndef _FUNC_MAP_H
#define _FUNC_MAP_H


/* Ficus_PIN_MAPPING
 * Pinout:http://www.viewtool.com/demo/STM32/Ficus_document_html/d5/db5/ficuspinout.html
*/
/*
*** GPIO Definition Table
	*/
#define J15_P1_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN5)
#define J15_P2_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN6)
#define J15_P3_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN13)
#define J15_P4_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN2)
#define J15_P5_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN0)
#define J15_P6_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN1)
#define J15_P7_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN2)
#define J15_P8_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN2)
#define J15_P9_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN3)
#define J15_P10_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN3)
#define J15_P11_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN4)

#define J2_P1_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN0)
#define J2_P2_GPIO	 (VGI_GPIO_PORTB|VGI_GPIO_PIN11)
#define J2_P3_GPIO	 (VGI_GPIO_PORTA|VGI_GPIO_PIN3)
#define J2_P4_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN12)
#define J2_P5_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN1)
#define J2_P6_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN13)
#define J2_P7_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN1)
#define J2_P8_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN4)
#define J2_P9_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN0)
#define J2_P10_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN5)
#define J2_P11_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN8)
#define J2_P12_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN1)
#define J2_P13_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN2)
#define J2_P14_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN2)
#define J2_P15_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN3)
#define J2_P16_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN10)
#define J2_P17_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN2)
#define J2_P18_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN7)
#define J2_P19_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN3)
#define J2_P20_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN5)

#define J6_P1_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN2)
#define J6_P2_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN3)

#define J1_P1_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN8)
#define J1_P2_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN9)

#define J4_P1_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN12)
#define J4_P2_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN13)


#define J8_P1_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN11)
#define J8_P2_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN6)
#define J8_P3_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN12)
#define J8_P4_GPIO	 (VGI_GPIO_PORTA|VGI_GPIO_PIN7)
#define J8_P5_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN10)
#define J8_P6_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN3)
#define J8_P7_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN15)
#define J8_P8_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN4)


#define J18_P1_GPIO	 (VGI_GPIO_PORTA|VGI_GPIO_PIN4)
#define J18_P2_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN5)
#define J18_P3_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN5)
#define J18_P4_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN1)
#define J18_P5_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN6)
#define J18_P6_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN0)

#define J7_P1_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN3)

#define J50_P1_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN14)
#define J50_P3_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN15)
#define J50_P4_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN4)
#define J50_P5_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN0)
#define J50_P6_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN5)
#define J50_P7_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN1)
#define J50_P8_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN6)
#define J50_P9_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN7)
#define J50_P10_GPIO (VGI_GPIO_PORTD|VGI_GPIO_PIN11)
#define J50_P11_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN8)
#define J50_P12_GPIO (VGI_GPIO_PORTD|VGI_GPIO_PIN12)
#define J50_P13_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN9)
#define J50_P14_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN12)
#define J50_P15_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN10)
#define J50_P16_GPIO (VGI_GPIO_PORTE|VGI_GPIO_PIN11)

#define J28_P1_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN11)
#define J28_P2_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN7)
#define J28_P3_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN10)
#define J28_P4_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN6)
#define J28_P5_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN12)
#define J28_P6_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN5)

#define J33_P1_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN3)

#define J5_P1_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN11)
#define J5_P2_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN9)
#define J5_P3_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN10)
#define J5_P4_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN5)
#define J5_P5_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN3)
#define J5_P6_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN15)
#define J5_P7_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN12)
#define J5_P8_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN7)

#define J17_P1_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN8)
#define J17_P2_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN2)
#define J17_P3_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN12)
#define J17_P4_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN11)
#define J17_P5_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN10)
#define J17_P6_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN0)
#define J17_P7_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN8)

#define J45_GPIO  	 (VGI_GPIO_PORTA|VGI_GPIO_PIN6)
#define J46_GPIO  	 (VGI_GPIO_PORTA|VGI_GPIO_PIN7)
#define J47_GPIO  	 (VGI_GPIO_PORTB|VGI_GPIO_PIN12)
#define J48_GPIO  	 (VGI_GPIO_PORTB|VGI_GPIO_PIN13)

#define J19_P1_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN2)
#define J19_P2_GPIO	  (VGI_GPIO_PORTE|VGI_GPIO_PIN3)
#define J19_P3_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN4)
#define J19_P4_GPIO	  (VGI_GPIO_PORTE|VGI_GPIO_PIN5)
#define J19_P5_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN6)
#define J19_P6_GPIO	  (VGI_GPIO_PORTC|VGI_GPIO_PIN13)
#define J19_P7_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN0)
#define J19_P8_GPIO	  (VGI_GPIO_PORTC|VGI_GPIO_PIN1)
#define J19_P9_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN2)
#define J19_P10_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN3)
#define J19_P11_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN0)
#define J19_P12_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN1)
#define J19_P13_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN2)
#define J19_P14_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN3)
#define J19_P15_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN4)
#define J19_P16_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN5)

#define J20_P1_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN6)
#define J20_P2_GPIO	  (VGI_GPIO_PORTA|VGI_GPIO_PIN7)
#define J20_P3_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN4)
#define J20_P4_GPIO	  (VGI_GPIO_PORTC|VGI_GPIO_PIN5)
#define J20_P5_GPIO   (VGI_GPIO_PORTB|VGI_GPIO_PIN0)
#define J20_P6_GPIO	  (VGI_GPIO_PORTB|VGI_GPIO_PIN1)
#define J20_P7_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN7)
#define J20_P8_GPIO	  (VGI_GPIO_PORTE|VGI_GPIO_PIN8)
#define J20_P9_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN9)
#define J20_P10_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN10)
#define J20_P11_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN11)
#define J20_P12_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN12)
#define J20_P13_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN13)
#define J20_P14_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN14)
#define J20_P15_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN15)
#define J20_P16_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN10)
#define J20_P17_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN1)
#define J20_P18_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN12)
#define J20_P19_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN6)
#define J20_P20_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN14)
#define J20_P21_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN4)

#define J21_P1_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN8)
#define J21_P2_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN9)
#define J21_P3_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN10)
#define J21_P4_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN11)
#define J21_P5_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN12)
#define J21_P6_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN13)
#define J21_P7_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN14)
#define J21_P8_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN15)
#define J21_P9_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN6)
#define J21_P10_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN7)
#define J21_P11_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN8)
#define J21_P12_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN9)
#define J21_P13_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN8)
#define J21_P14_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN9)
#define J21_P15_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN10)
#define J21_P16_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN11)
#define J21_P17_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN12)
#define J21_P18_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN13)
#define J21_P19_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN14)
#define J21_P20_GPIO  (VGI_GPIO_PORTA|VGI_GPIO_PIN15)
#define J21_P21_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN10)
#define J21_P22_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN11)

#define J22_P1_GPIO   (VGI_GPIO_PORTC|VGI_GPIO_PIN12)
#define J22_P2_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN0)
#define J22_P3_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN1)
#define J22_P4_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN2)
#define J22_P5_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN3)
#define J22_P6_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN4)
#define J22_P7_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN5)
#define J22_P8_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN6)
#define J22_P9_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN7)
#define J22_P10_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN3)
#define J22_P11_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN4)
#define J22_P12_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN5)
#define J22_P13_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN6)
#define J22_P14_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN7)
#define J22_P15_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN8)
#define J22_P16_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN9)
#define J22_P17_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN0)
#define J22_P18_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN1)

#define J14_P1_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN9)
#define J14_P2_GPIO	  (VGI_GPIO_PORTA|VGI_GPIO_PIN10)
#define J14_P3_GPIO   (VGI_GPIO_PORTA|VGI_GPIO_PIN11)
#define J14_P4_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN0)
#define J14_P5_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN1)
#define J14_P6_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN2)
#define J14_P7_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN3)
#define J14_P8_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN4)
#define J14_P9_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN5)
#define J14_P10_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN6)
#define J14_P11_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN7)

#define J11_P1_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN14)
#define J11_P2_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN15)
#define J11_P3_GPIO   (VGI_GPIO_PORTD|VGI_GPIO_PIN0)
#define J11_P4_GPIO	  (VGI_GPIO_PORTD|VGI_GPIO_PIN1)
#define J11_P5_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN7)
#define J11_P6_GPIO	  (VGI_GPIO_PORTE|VGI_GPIO_PIN8)
#define J11_P7_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN9)
#define J11_P8_GPIO	  (VGI_GPIO_PORTE|VGI_GPIO_PIN10)
#define J11_P9_GPIO   (VGI_GPIO_PORTE|VGI_GPIO_PIN11)
#define J11_P10_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN12)
#define J11_P11_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN13)
#define J11_P12_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN14)
#define J11_P13_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN15)
#define J11_P14_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN8)
#define J11_P15_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN9)
#define J11_P16_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN10)
#define J11_P17_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN11)
#define J11_P18_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN5)
#define J11_P19_GPIO  (VGI_GPIO_PORTD|VGI_GPIO_PIN4)
#define J11_P20_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN1)
#define J11_P21_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN0)
#define J11_P22_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN5)
#define J11_P23_GPIO  (VGI_GPIO_PORTC|VGI_GPIO_PIN4)
#define J11_P24_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN13)
#define J11_P25_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN14)
#define J11_P26_GPIO  (VGI_GPIO_PORTB|VGI_GPIO_PIN15)

#define J42_GPIO  	  (VGI_GPIO_PORTC|VGI_GPIO_PIN11)
#define J43_GPIO  	  (VGI_GPIO_PORTC|VGI_GPIO_PIN12)
#define J44_GPIO  	  (VGI_GPIO_PORTA|VGI_GPIO_PIN0)


#define J28_P2_P4_I2C_STL_CH0      (0)
#define J50_P6_P8_I2C_STL_CH1      (1)
#define J50_P10_P12_I2C_STL_CH2    (2)
#define J50_P14_P16_I2C_STL_CH3    (3)
#define J50_P1_P3_I2C_STL_CH4      (4)
#define J50_P5_P7_I2C_STL_CH5      (5)
#define J50_P9_P10_I2C_STL_CH6     (6)
#define J50_P13_P15_I2C_STL_CH7    (7)
#define J18_P1_P5_I2C_STL_CH8      (8)
#define J18_P4_P6_I2C_STL_CH9      (9)
#define J2_P1_P5_I2C_STL_CH9       (9)
#define J8_P1_P3_I2C_STL_CH10      (10)
#define J8_P5_J50_P4_I2C_STL_CH11  (11)
#define J8_P2_P4_I2C_STL_CH12      (12)
#define J8_P6_P8_I2C_STL_CH13      (13)
#define J1_P1_P2_I2C_STL_CH14      (14)
#define J2_P7_P9_I2C_STL_CH15      (15)
#define J2_P17_P19_I2C_STL_CH16    (16)
#define J2_P8_P10_I2C_STL_CH17     (17)
#define J2_P12_P14_I2C_STL_CH18    (18)
#define J5_P1_P7_I2C_STL_CH19      (19)

#define J28_P2_P4_I2C		  (0)
#define J28_P1_P3_I2C         (1)


#define J8_P2_P4_P6_P8_SPI0_NSS0    	(0)
#define J8_P2_P4_P6_J50_P4_SPI0_NSS1    (1)
#define J8_P2_P4_P6_J50_P6_SPI0_NSS2    (2)
#define J8_P2_P4_P6_J50_P8_SPI0_NSS3    (3)
#define J8_P2_P4_P6_J50_P10_SPI0_NSS4   (4)
#define J8_P2_P4_P6_J50_P12_SPI0_NSS5   (5)
#define J8_P2_P4_P6_J50_P14_SPI0_NSS6   (6)
#define J8_P2_P4_P6_J50_P16_SPI0_NSS7   (7)
#define J8_P1_P3_P5_P7_SPI1_NSS8    	(8)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS9    (9)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS10   (10)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS11   (11)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS12   (12)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS13   (13)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS14   (14)
#define J8_P1_P3_P5_J50_P7_SPI1_NSS15   (15)

#define J15_P7_ADC_CH2		(1<<2)
#define J15_P9_ADC_CH3		(1<<3)	

#define J2_P1_ADC_CH0		(1<<0)
#define J2_P3_ADC_CH3		(1<<3)
#define J2_P5_ADC_CH1		(1<<1)
#define J2_P14_ADC_CH2		(1<<2)
#define J2_P18_ADC_CH7		(1<<7)

#define J6_P1_ADC_CH2		(1<<2)
#define J6_P2_ADC_CH3		(1<<3)	

#define J18_P1_ADC_CH7		(1<<4)
#define J18_P3_ADC_CH2		(1<<5)
#define J18_P5_ADC_CH3		(1<<6)
#define J18_P8_ADC_CH1		(1<<1)
#define J18_P10_ADC_CH0		(1<<0)

#define J5_P8_ADC_CH1		(1<<1)
#define J5_P10_ADC_CH0		(1<<0)



#define J2_P1_CNT_CH0 		(1<<0)
#define J2_P5_CNT_CH1		(1<<1)

#define J18_P5_CNT_CH2		(1<<2)
#define J18_P10_CNT_CH0 	(1<<0)
#define J18_P8_CNT_CH1		(1<<1)

#define J28_P4_CNT_CH3		(1<<3)


#define J15_P7_PWM_CH2		(1<<2)
#define J15_P9_PWM_CH3		(1<<3)

#define J2_P1_PWM_CH0		(1<<0)
#define J2_P3_PWM_CH3		(1<<3)
#define J2_P5_PWM_CH1		(1<<1)
#define J2_P11_PWM_CH6		(1<<6)
#define J2_P18_PWM_CH5		(1<<5)

#define J6_P1_PWM_CH2		(1<<2)
#define J6_P2_PWM_CH3		(1<<3)

#define J1_P1_PWM_CH6		(1<<6)
#define J1_P2_PWM_CH7		(1<<7)

#define J8_P2_PWM_CH5		(1<<5)
#define J8_P4_PWM_CH6		(1<<6)

#define J18_P8_PWM_CH1		(1<<1)
#define J18_P10_PWM_CH0		(1<<0)
#define J18_P9_PWM_CH4		(1<<4)


#define J18_P1_DAC_CH0		(1<<0)
 
#define J1_P1_P2_CAN_CH0		(0)
#define J4_P1_P2_CAN_CH1		(1) 

#define J5_P2_P3_UART_CH0		(0)
#define J6_P1_P2_UART_CH1		(1)



#endif