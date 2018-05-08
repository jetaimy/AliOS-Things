#include <k_api.h>
#include "stm32l4xx_hal.h"
#include "gc0329.h"

extern i2c_dev_t brd_i2c3_dev;

CAMERA_DrvTypeDef   gc0329_drv = 
{
  gc0329_Init,
  gc0329_ReadID,  
  gc0329_Config,
};

/* Initialization sequence for VGA resolution (640x480)*/
const unsigned char GC0329_VGA[][2]=
{
 	{0xfe , 0x80},
	{0xfc , 0x16},
	{0xfc , 0x16},
	{0xfe , 0x00},


	{0xfa,0x00},	   

	{0x70 , 0x48},
	{0x73 , 0x90},
	{0x74 , 0x80},
	{0x75 , 0x80},
	{0x76 , 0x94}, //80 jambo 
	{0x77 , 0x62},
	{0x78 , 0x47},
	{0x79 , 0x40},

	{0x03 , 0x02},
	{0x04 , 0x40},


	////////////////////analog////////////////////
	{0xfc , 0x16},
	{0x09 , 0x00},
	{0x0a , 0x02},
	{0x0b , 0x00},
	{0x0c , 0x02},
	{0x17 , 0x15}, //0x14
	{0x19 , 0x05},
	{0x1b , 0x24},
	{0x1c , 0x04},
	{0x1e , 0x08},
	{0x1f , 0x08}, //C8 
	{0x20 , 0x01},
	{0x21 , 0x48},
	{0x22 , 0xba},
	{0x23 , 0x22},
	{0x24 , 0x16},


	////////////////////blk////////////////////
	////added for MID
	{0x26 , 0xf4}, //BLK
	{0x2a , 0x2c},
	{0x2b , 0x2c},
	{0x2c , 0x2c},
	{0x2d , 0x2c},


	{0x26 , 0xf7}, //BLK
	{0x28 , 0x7f}, //BLK limit
	{0x29 , 0x00},
	{0x32 , 0x00}, //04 darkc
	{0x33 , 0x20}, //blk ratio
	{0x34 , 0x20},
	{0x35 , 0x20},
	{0x36 , 0x20},

	{0x3b , 0x04}, //manual offset
	{0x3c , 0x04},
	{0x3d , 0x04},
	{0x3e , 0x04},

	////////////////////ISP BLOCK ENABLE////////////////////
	{0x40 , 0xff},
	{0x41 , 0x24},//[5]skin detection
	{0x42 , 0xfa},//disable ABS 
	{0x46 , 0x03},
	{0x4b , 0xca},
	{0x4d , 0x01},
	{0x4f , 0x01},
	{0x70 , 0x48},

	////////////////////DNDD////////////////////
	{0x80 , 0x07}, // 0xe7 20140915
    {0x81 , 0xc2}, // 0x22 20140915
	{0x82 , 0x90}, //DN auto DNDD DEC DNDD //0e //55 jambo
	{0x83 , 0x05},
	{0x87 , 0x40}, // 0x4a  20140915  

	////////////////////INTPEE////////////////////
	{0x90 , 0x8c}, //ac
	{0x92 , 0x05},
	{0x94 , 0x05},
	{0x95 , 0x45}, //0x44
	{0x96 , 0x88}, 

	////////////////////ASDE////////////////////
	{0xfe , 0x01},
	{0x18 , 0x22}, 
	{0xfe , 0x00},
	{0x9c , 0x0a},
	{0xa0 , 0xaf},
	{0xa2 , 0xff}, 
	{0xa4 , 0x30}, //50 jambo 
	{0xa5 , 0x31}, 
	{0xa7 , 0x35}, 

	////////////////////RGB gamma////////////////////
	{0xfe , 0x00},
	{0xbf , 0x0b},
	{0xc0 , 0x1d},
	{0xc1 , 0x33},
	{0xc2 , 0x49},
	{0xc3 , 0x5d},
	{0xc4 , 0x6e},
	{0xc5 , 0x7c},
	{0xc6 , 0x99},
	{0xc7 , 0xaf},
	{0xc8 , 0xc2},
	{0xc9 , 0xd0},
	{0xca , 0xda},
	{0xcb , 0xe2},
	{0xcc , 0xe7},
	{0xcd , 0xf0},
	{0xce , 0xf7},
	{0xcf , 0xff},

#if 0
		case GC0329_RGB_Gamma_m1:						//smallest gamma curve
			{0xfe, 0x00},
			{0xbf, 0x06},
			{0xc0, 0x12},
			{0xc1, 0x22},
			{0xc2, 0x35},
			{0xc3, 0x4b},
			{0xc4, 0x5f},
			{0xc5, 0x72},
			{0xc6, 0x8d},
			{0xc7, 0xa4},
			{0xc8, 0xb8},
			{0xc9, 0xc8},
			{0xca, 0xd4},
			{0xcb, 0xde},
			{0xcc, 0xe6},
			{0xcd, 0xf1},
			{0xce, 0xf8},
			{0xcf, 0xfd},
			
		case GC0329_RGB_Gamma_m2:
			{0xBF, 0x08},
			{0xc0, 0x0F},
			{0xc1, 0x21},
			{0xc2, 0x32},
			{0xc3, 0x43},
			{0xc4, 0x50},
			{0xc5, 0x5E},
			{0xc6, 0x78},
			{0xc7, 0x90},
			{0xc8, 0xA6},
			{0xc9, 0xB9},
			{0xcA, 0xC9},
			{0xcB, 0xD6},
			{0xcC, 0xE0},
			{0xcD, 0xEE},
			{0xcE, 0xF8},
			{0xcF, 0xFF},
			
			
		case GC0329_RGB_Gamma_m3:			
			{0xfe , 0x00},
			{0xbf , 0x0b},
			{0xc0 , 0x1d},
			{0xc1 , 0x33},
			{0xc2 , 0x49},
			{0xc3 , 0x5d},
			{0xc4 , 0x6e},
			{0xc5 , 0x7c},
			{0xc6 , 0x99},
			{0xc7 , 0xaf},
			{0xc8 , 0xc2},
			{0xc9 , 0xd0},
			{0xca , 0xda},
			{0xcb , 0xe2},
			{0xcc , 0xe7},
			{0xcd , 0xf0},
			{0xce , 0xf7},
			{0xcf , 0xff},
			
			
		case GC0329_RGB_Gamma_m4:
			{0xBF, 0x0E},
			{0xc0, 0x1C},
			{0xc1, 0x34},
			{0xc2, 0x48},
			{0xc3, 0x5A},
			{0xc4, 0x6B},
			{0xc5, 0x7B},
			{0xc6, 0x95},
			{0xc7, 0xAB},
			{0xc8, 0xBF},
			{0xc9, 0xCE},
			{0xcA, 0xD9},
			{0xcB, 0xE4},
			{0xcC, 0xEC},
			{0xcD, 0xF7},
			{0xcE, 0xFD},
			{0xcF, 0xFF},
			
			
		case GC0329_RGB_Gamma_m5:
			{0xBF, 0x10},
			{0xc0, 0x20},
			{0xc1, 0x38},
			{0xc2, 0x4E},
			{0xc3, 0x63},
			{0xc4, 0x76},
			{0xc5, 0x87},
			{0xc6, 0xA2},
			{0xc7, 0xB8},
			{0xc8, 0xCA},
			{0xc9, 0xD8},
			{0xcA, 0xE3},
			{0xcB, 0xEB},
			{0xcC, 0xF0},
			{0xcD, 0xF8},
			{0xcE, 0xFD},
			{0xcF, 0xFF},
			
			
		case GC0329_RGB_Gamma_m6:										// largest gamma curve
			{0xBF, 0x14},
			{0xc0, 0x28},
			{0xc1, 0x44},
			{0xc2, 0x5D},
			{0xc3, 0x72},
			{0xc4, 0x86},
			{0xc5, 0x95},
			{0xc6, 0xB1},
			{0xc7, 0xC6},
			{0xc8, 0xD5},
			{0xc9, 0xE1},
			{0xcA, 0xEA},
			{0xcB, 0xF1},
			{0xcC, 0xF5},
			{0xcD, 0xFB},
			{0xcE, 0xFE},
			{0xcF, 0xFF},
			
		case GC0329_RGB_Gamma_night:									//Gamma for night mode
			{0xBF, 0x0B},
			{0xc0, 0x16},
			{0xc1, 0x29},
			{0xc2, 0x3C},
			{0xc3, 0x4F},
			{0xc4, 0x5F},
			{0xc5, 0x6F},
			{0xc6, 0x8A},
			{0xc7, 0x9F},
			{0xc8, 0xB4},
			{0xc9, 0xC6},
			{0xcA, 0xD3},
			{0xcB, 0xDD},
			{0xcC, 0xE5},
			{0xcD, 0xF1},
			{0xcE, 0xFA},
			{0xcF, 0xFF},
			
		default:
			//GC0329_RGB_Gamma_m3
			{0xfe , 0x00},
			{0xbf , 0x0b},
			{0xc0 , 0x1d},
			{0xc1 , 0x33},
			{0xc2 , 0x49},
			{0xc3 , 0x5d},
			{0xc4 , 0x6e},
			{0xc5 , 0x7c},
			{0xc6 , 0x99},
			{0xc7 , 0xaf},
			{0xc8 , 0xc2},
			{0xc9 , 0xd0},
			{0xca , 0xda},
			{0xcb , 0xe2},
			{0xcc , 0xe7},
			{0xcd , 0xf0},
			{0xce , 0xf7},
			{0xcf , 0xff},
			
#endif

	////////////////////Y gamma////////////////////
	{0xfe , 0x00},
	{0x63 , 0x00},
	{0x64 , 0x06},
	{0x65 , 0x0d},
	{0x66 , 0x1b},
	{0x67 , 0x2b},
	{0x68 , 0x3d},
	{0x69 , 0x50},
	{0x6a , 0x60},
	{0x6b , 0x80},
	{0x6c , 0xa0},
	{0x6d , 0xc0},
	{0x6e , 0xe0},
	{0x6f , 0xff},
	 
	 
	//////////////////CC///////////////////
#if 1 //main
	{0xfe , 0x00},
	{0xb3 , 0x44},
	{0xb4 , 0xfd},
	{0xb5 , 0x02},
	{0xb6 , 0xfa},
	{0xb7 , 0x48},
	{0xb8 , 0xf0},
#else //sub
	{0xfe , 0x00},
	{0xb3 , 0x42},//40
	{0xb4 , 0xff},//00
	{0xb5 , 0x06},//06
	{0xb6 , 0xf0},//00
	{0xb7 , 0x44},//40
	{0xb8 , 0xf0},//00
#endif

	// crop 
	{0x50 , 0x01},


	////////////////////YCP////////////////////
	{0xfe , 0x00},

	{0xd0 , 0x40},
	{0xd1 , 0x28},
	{0xd2 , 0x28},

	{0xd3 , 0x40}, //cont 0x40
	{0xd5 , 0x00},

	{0xdd , 0x14}, 
	{0xde , 0x34}, 

	////////////////////AEC////////////////////
	{0xfe , 0x01},
	{0x10 , 0x40}, // before Gamma 
	{0x11 , 0x21}, //
	{0x12 , 0x13},	// center weight *2
	{0x13 , 0x50}, //4 //4}, // AE Target
	{0x17 , 0xa8},	//88, 08, c8, a8
	{0x1a , 0x21},
	{0x20 , 0x31},	//AEC stop margin
	{0x21 , 0xc0},
	{0x22 , 0x60}, 
	{0x3c , 0x50},
	{0x3d , 0x40}, 
	{0x3e , 0x45}, //read 3f for status

////////////////////AWB////////////////////
	#if 0 /////oppo AWB
	{0xfe, 0x01},
	{0x06, 0x16},
	{0x07, 0x06},
	{0x08, 0x98},
	{0x09, 0xee},
	{0x50, 0xfc},
	{0x51, 0x20},
	{0x52, 0x0b},
	{0x53, 0x20},
	{0x54, 0x40},
	{0x55, 0x10},
	{0x56, 0x20},
	{0x58, 0xa0},
	{0x59, 0x28},
	{0x5a, 0x02},
	{0x5b, 0x63},
	{0x5c, 0x34},
	{0x5d, 0x73},
	{0x5e, 0x11},
	{0x5f, 0x40},
	{0x60, 0x40},
	{0x61, 0xc8},
	{0x62, 0xa0},
	{0x63, 0x40},
	{0x64, 0x50},
	{0x65, 0x98},
	{0x66, 0xfa},
	{0x67, 0x70},
	{0x68, 0x58},
	{0x69, 0x85},
	{0x6a, 0x40},
	{0x6b, 0x39},
	{0x6c, 0x18},
	{0x6d, 0x28},
	{0x6e, 0x41},
	{0x70, 0x02},
	{0x71, 0x00},
	{0x72, 0x10},
	{0x73, 0x40},
	{0x80, 0x60},
	{0x81, 0x50},
	{0x82, 0x42},
	{0x83, 0x40},
	{0x84, 0x40},
	{0x85, 0x40},
	{0x74, 0x40},
	{0x75, 0x58},
	{0x76, 0x24},
	{0x77, 0x40},
	{0x78, 0x20},
	{0x79, 0x60},
	{0x7a, 0x58},
	{0x7b, 0x20},
	{0x7c, 0x30},
	{0x7d, 0x35},
	{0x7e, 0x10},
	{0x7f, 0x08},
	#endif
#if 1 //main
	{0xfe , 0x01},
	{0x06 , 0x12},
	{0x07 , 0x06},
	{0x08 , 0x9c},
	{0x09 , 0xee},
	{0x50 , 0xfc},
	{0x51 , 0x28},
	{0x52 , 0x10},
	{0x53 , 0x20},
	{0x54 , 0x12},
	{0x55 , 0x16},
	{0x56 , 0x30},
	{0x58 , 0x60},
	{0x59 , 0x08},
	{0x5a , 0x02},
	{0x5b , 0x63},
	{0x5c , 0x35},
	{0x5d , 0x72},
	{0x5e , 0x11},
	{0x5f , 0x40},
	{0x60 , 0x40},
	{0x61 , 0xc8},
	{0x62 , 0xa0},
	{0x63 , 0x40},
	{0x64 , 0x50},
	{0x65 , 0x98},
	{0x66 , 0xfa},
	{0x67 , 0x80},
	{0x68 , 0x60},
	{0x69 , 0x90},
	{0x6a , 0x40},
	{0x6b , 0x39},
	{0x6c , 0x30},
	{0x6d , 0x60},
	{0x6e , 0x41},
	{0x70 , 0x10},
	{0x71 , 0x00},
	{0x72 , 0x10},
	{0x73 , 0x40},
	{0x80 , 0x60},
	{0x81 , 0x50},
	{0x82 , 0x42},
	{0x83 , 0x40},
	{0x84 , 0x40},
	{0x85 , 0x40},
	{0x74 , 0x40},
	{0x75 , 0x58},
	{0x76 , 0x24},
	{0x77 , 0x40},
	{0x78 , 0x20},
	{0x79 , 0x60},
	{0x7a , 0x58},
	{0x7b , 0x20},
	{0x7c , 0x30},
	{0x7d , 0x35},
	{0x7e , 0x10},
	{0x7f , 0x08},
#else //sub
	{0xfe , 0x01},
	{0x06 , 0x16},
	{0x07 , 0x06},
	{0x08 , 0x98},
	{0x09 , 0xee},
	{0x50 , 0xfc},
	{0x51 , 0x20},
	{0x52 , 0x1b},//0b
	{0x53 , 0x10},//20
	{0x54 , 0x10},//40
	{0x55 , 0x10},
	{0x56 , 0x20},
	{0x57 , 0xa0},
	{0x58 , 0xa0},
	{0x59 , 0x28},
	{0x5a , 0x02},
	{0x5b , 0x63},
	{0x5c , 0x04},//34
	{0x5d , 0x73},
	{0x5e , 0x11},
	{0x5f , 0x40},
	{0x60 , 0x40},
	{0x61 , 0xc8},//d8 //c8
	{0x62 , 0xa0},///88 //A0
	{0x63 , 0x40},
	{0x64 , 0x40},//37
	{0x65 , 0xd0},
	{0x66 , 0xfa},
	{0x67 , 0x70},
	{0x68 , 0x58},
	{0x69 , 0xa5}, //85 jaambo
	{0x6a , 0x40},
	{0x6b , 0x39},
	{0x6c , 0x18},
	{0x6d , 0x28},
	{0x6e , 0x41},
	{0x70 , 0x40},
	{0x71 , 0x00},
	{0x72 , 0x10},
	{0x73 , 0x30},//awb outdoor-th
	{0x80 , 0x60},
	{0x81 , 0x50},
	{0x82 , 0x42},
	{0x83 , 0x40},
	{0x84 , 0x40},
	{0x85 , 0x40},
	{0x86 , 0x40},
	{0x87 , 0x40},
	{0x88 , 0xfe},
	{0x89 , 0xa0},
	{0x74 , 0x40},
	{0x75 , 0x58},
	{0x76 , 0x24},
	{0x77 , 0x40},
	{0x78 , 0x20},
	{0x79 , 0x60},
	{0x7a , 0x58},
	{0x7b , 0x20},
	{0x7c , 0x30},
	{0x7d , 0x35},
	{0x7e , 0x10},
	{0x7f , 0x08},
#endif

	///////////////////ABS///////////////////////
	{0x9c , 0x00},
	{0x9e , 0xc0},
	{0x9f , 0x40},

	////////////////////CC-AWB////////////////////
	{0xd0 , 0x00},
	{0xd2 , 0x2c}, 
	{0xd3 , 0x80},

	///////////////////LSC //////////////////////

	{0xfe , 0x01},
	{0xc0 , 0x0b},
	{0xc1 , 0x07},
	{0xc2 , 0x05},
	{0xc6 , 0x0b},
	{0xc7 , 0x07},
	{0xc8 , 0x05},
	{0xba , 0x39},
	{0xbb , 0x24},
	{0xbc , 0x23},
	{0xb4 , 0x39},
	{0xb5 , 0x24},
	{0xb6 , 0x23},
	{0xc3 , 0x00},
	{0xc4 , 0x00},
	{0xc5 , 0x00},
	{0xc9 , 0x00},
	{0xca , 0x00},
	{0xcb , 0x00},
	{0xbd , 0x2b},
	{0xbe , 0x00},
	{0xbf , 0x00},
	{0xb7 , 0x09},
	{0xb8 , 0x00},
	{0xb9 , 0x00},
	{0xa8 , 0x31},
	{0xa9 , 0x23},
	{0xaa , 0x20},
	{0xab , 0x31},
	{0xac , 0x23},
	{0xad , 0x20},
	{0xae , 0x31},
	{0xaf , 0x23},
	{0xb0 , 0x20},
	{0xb1 , 0x31},
	{0xb2 , 0x23},
	{0xb3 , 0x20},
	{0xa4 , 0x00},
	{0xa5 , 0x00},
	{0xa6 , 0x00},
	{0xa7 , 0x00},
	{0xa1 , 0x3c},
	{0xa2 , 0x50},
	{0xfe , 0x00},

	//////////////////// flicker ///////////////////

	{0x05, 0x02},
	{0x06, 0x2c}, 
	{0x07, 0x00},
	{0x08, 0xb8},
	
	{0xfe, 0x01},
	{0x29, 0x00},	//anti-flicker step [11:8]
	{0x2a, 0x60},	//anti-flicker step [7:0]
	
	{0x2b, 0x02},	//exp level 0  14.28fps
	{0x2c, 0xa0}, 
	{0x2d, 0x03},	//exp level 1  12.50fps
	{0x2e, 0x00}, 
	{0x2f, 0x03},	//exp level 2  10.00fps
	{0x30, 0xc0}, 
	{0x31, 0x05},	//exp level 3  7.14fps
	{0x32, 0x40}, 
	{0x33, 0x20}, 
	{0xfe, 0x00},

////////////////////out ///////////////////

	{0x44 , 0xa6},
	{0xf0 , 0x07},
	{0xf1 , 0x01},	
};

/* Initialization sequence for QVGA resolution (320x240) */
const unsigned char GC0329_QVGA[][2]=
{
 	{0xff , 0xff},	
};

/* Initialization sequence for QQVGA resolution (160x120) */
const char GC0329_QQVGA[][2]=
{
 	{0xff , 0xff},	
};

void gc0329_mclk_onoff(int on)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/*xiehj add RCC_OSCILLATORTYPE_HSI48*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
	/*xiehj add*/
	if(on)
		RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	else
		RCC_OscInitStruct.HSI48State = RCC_HSI48_OFF;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
}

void gc0329_power_onoff(int on)
{
	if(on){
#ifdef ALIOS_HAL
		//gc0329_mclk_onoff(1);
		hal_gpio_output_high(&brd_gpio_table[GPIO_CAM_PD]);
		hal_gpio_output_low(&brd_gpio_table[GPIO_CAM_RST]);
		krhino_task_sleep(krhino_ms_to_ticks(50));
		hal_gpio_output_low(&brd_gpio_table[GPIO_CAM_PD]);
	       krhino_task_sleep(krhino_ms_to_ticks(50));
		hal_gpio_output_high(&brd_gpio_table[GPIO_CAM_RST]);
		krhino_task_sleep(krhino_ms_to_ticks(100));
#else
		HAL_GPIO_WritePin(CAM_PD_GPIO_Port, CAM_PD_Pin, GPIO_PIN_RESET);
              krhino_task_sleep(krhino_ms_to_ticks(10));
		HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_RESET);
		krhino_task_sleep(krhino_ms_to_ticks(50));
	  	HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_SET);
#endif
	}
	else{
#ifdef ALIOS_HAL
		hal_gpio_output_low(&brd_gpio_table[GPIO_CAM_RST]);
		krhino_task_sleep(krhino_ms_to_ticks(10));
		hal_gpio_output_high(&brd_gpio_table[GPIO_CAM_PD]);
		//gc0329_mclk_onoff(0);
#else
		HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_RESET);
		krhino_task_sleep(krhino_ms_to_ticks(50));
		HAL_GPIO_WritePin(CAM_PD_GPIO_Port, CAM_PD_Pin, GPIO_PIN_SET);
#endif
	}
}

uint8_t CAMERA_IO_Read(uint8_t DevAddr, uint8_t Reg)
{
  uint8_t read_value = 0;

  hal_i2c_mem_read(&brd_i2c3_dev, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&read_value, 1, AOS_WAIT_FOREVER);    

  return read_value;
}

void CAMERA_IO_Write(uint8_t DevAddr, uint8_t Reg, uint8_t Value)
{
  hal_i2c_mem_write(&brd_i2c3_dev, DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&Value, 1, AOS_WAIT_FOREVER);
}

uint8_t gc0329_ReadID(void)
{  
  /* Get the camera ID */
 // CAMERA_IO_Write(0xfe, 0x00);
  CAMERA_IO_Write(GC0329_I2CADDR,0xfc, 0x16);
  return (CAMERA_IO_Read(GC0329_I2CADDR, GC0329_CHIPID));
}

void gc0329_Init(uint16_t DeviceAddr, uint32_t resolution)
{
  uint32_t index;
  
  /* Initialize GC0329 */
  switch (resolution)
  {
  case CAMERA_R160x120:
    {
      for(index=0; index<(sizeof(GC0329_QQVGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, GC0329_QQVGA[index][0], GC0329_QQVGA[index][1]);
        //CAMERA_Delay(2);
	 krhino_task_sleep(krhino_ms_to_ticks(2));
      } 
      break;
    }    
  case CAMERA_R320x240:
    {
      for(index=0; index<(sizeof(GC0329_QVGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, GC0329_QVGA[index][0], GC0329_QVGA[index][1]);
        //CAMERA_Delay(2);
	 krhino_task_sleep(krhino_ms_to_ticks(2));
      } 
      break;
    }
  case CAMERA_R480x272:
    {
      /* Not supported resolution */
      break;
    }
  case CAMERA_R640x480:
    {
      for(index=0; index<(sizeof(GC0329_VGA)/2); index++)
      {
        CAMERA_IO_Write(DeviceAddr, GC0329_VGA[index][0], GC0329_VGA[index][1]);
        //CAMERA_Delay(2);
	 krhino_task_sleep(krhino_ms_to_ticks(2));
      }
      break;
    }    
  default:
    {
      break;
    }
  }
}

void gc0329_Config(uint16_t DeviceAddr, uint32_t feature, uint32_t value, uint32_t brightness_value)
{
  uint8_t tslb, mtx1, mtx2, mtx3, mtx4, mtx5, mtx6;
  uint64_t value_tmp;
  uint32_t br_value;
  
  /* Convert the input value into gc0329 parameters */
  value_tmp = gc0329_ConvertValue(feature, value); 
  br_value = (uint32_t)gc0329_ConvertValue(CAMERA_CONTRAST_BRIGHTNESS, brightness_value);
 // return 0;  
  switch(feature)
  {
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_BRTN, br_value);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_CNST1, value_tmp);
      break;
    }
  case CAMERA_BLACK_WHITE:
  case CAMERA_COLOR_EFFECT:
    {     
      tslb = (uint8_t)(value_tmp >> 48);
      mtx1 = (uint8_t)(value_tmp >> 40);
      mtx2 = (uint8_t)(value_tmp >> 32);
      mtx3 = (uint8_t)(value_tmp >> 24);
      mtx4 = (uint8_t)(value_tmp >> 16);
      mtx5 = (uint8_t)(value_tmp >> 8);
      mtx6 = (uint8_t)(value_tmp);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_TSLB, tslb);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX1, mtx1);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX2, mtx2);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX3, mtx3);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX4, mtx4);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX5, mtx5);
      //CAMERA_IO_Write(DeviceAddr, GC0329_SENSOR_MTX6, mtx6);
      break;
    }     
  default:
    {
      break;
    }
  }
}

uint64_t gc0329_ConvertValue(uint32_t feature, uint32_t value)
{
  uint64_t ret = 0;
  return 0;
  switch(feature)
  {
  case CAMERA_BLACK_WHITE:
    {
      switch(value)
      {
      case CAMERA_BLACK_WHITE_BW:
        {
          ret =  GC0329_BLACK_WHITE_BW;
          break;
        }
      case CAMERA_BLACK_WHITE_NEGATIVE:
        {
          ret =  GC0329_BLACK_WHITE_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_BW_NEGATIVE:
        {
          ret =  GC0329_BLACK_WHITE_BW_NEGATIVE;
          break;
        }
      case CAMERA_BLACK_WHITE_NORMAL:
        {
          ret =  GC0329_BLACK_WHITE_NORMAL;
          break;
        }
      default:
        {
          ret =  GC0329_BLACK_WHITE_NORMAL;
          break;
        }
      }
      break;
    }
  case CAMERA_CONTRAST_BRIGHTNESS:
    {
      switch(value)
      {
      case CAMERA_BRIGHTNESS_LEVEL0:
        {
          ret =  GC0329_BRIGHTNESS_LEVEL0;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL1:
        {
          ret =  GC0329_BRIGHTNESS_LEVEL1;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL2:
        {
          ret =  GC0329_BRIGHTNESS_LEVEL2;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL3:
        {
          ret =  GC0329_BRIGHTNESS_LEVEL3;
          break;
        }
      case CAMERA_BRIGHTNESS_LEVEL4:
        {
          ret =  GC0329_BRIGHTNESS_LEVEL4;
          break;
        }        
      case CAMERA_CONTRAST_LEVEL0:
        {
          ret =  GC0329_CONTRAST_LEVEL0;
          break;
        }
      case CAMERA_CONTRAST_LEVEL1:
        {
          ret =  GC0329_CONTRAST_LEVEL1;
          break;
        }
      case CAMERA_CONTRAST_LEVEL2:
        {
          ret =  GC0329_CONTRAST_LEVEL2;
          break;
        }
      case CAMERA_CONTRAST_LEVEL3:
        {
          ret =  GC0329_CONTRAST_LEVEL3;
          break;
        }
      case CAMERA_CONTRAST_LEVEL4:
        {
          ret =  GC0329_CONTRAST_LEVEL4;
          break;
        }
      default:
        {
          ret =  GC0329_CONTRAST_LEVEL0;
          break;
        }
      }
      break;
    }
  case CAMERA_COLOR_EFFECT:
    {
      switch(value)
      {
      case CAMERA_COLOR_EFFECT_ANTIQUE:
        {
          ret =  GC0329_COLOR_EFFECT_ANTIQUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_BLUE:
        {
          ret =  GC0329_COLOR_EFFECT_BLUE;
          break;
        }
      case CAMERA_COLOR_EFFECT_GREEN:
        {
          ret =  GC0329_COLOR_EFFECT_GREEN;
          break;
        }
      case CAMERA_COLOR_EFFECT_RED:
        {
          ret =  GC0329_COLOR_EFFECT_RED;
          break;
        }
      case CAMERA_COLOR_EFFECT_NONE:
      default:
        {
          ret =  GC0329_COLOR_EFFECT_NONE;
          break;
        }
      }
      break;
    default:
      {
        ret = 0;
        break;
      }    
    }
  }
  
  return ret;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
