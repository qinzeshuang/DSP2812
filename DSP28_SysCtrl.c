/*************************************************
Copyright (C), 1988-2013, MagicFill Tech. Co., Ltd.

File name:    DSP28_SysCtrl.c // 文件名
Author: Magicfillcs    Version: 1.0     Date: 2013.12.30 // 作者、版本及完成日期
Description: 
    1.对2812的系统控制模块进行初始化

    // 用于详细说明此程序文件完成的主要功能，与其他模块
    // 或函数的接口，输出值、取值范围、含义及参数间的控
    // 制、顺序、独立或依赖等关系

Others:     // 其它内容的说明
    1.IDE: CCS 3.3


Function List: // 主要函数列表，每条记录应包括函数名及功能简要说明

    1. void InitSysCtrl(void); DSP2812的系统控制模块初始化程序
    2. void KickDog(void)； 看门狗喂狗程序
    

History: // 修改历史记录列表，每条修改记录应包括修改日期、修改
         // 者及修改内容简述
    1. Date:
    Author:
    Modification:
    2. ...
*************************************************/



#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitSysCtrl()
*
*功    能：该函数对2812的系统控制寄存器进行初始化
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitSysCtrl(void)
{
   Uint16 i;
   EALLOW;

// 对于TMX产品，为了能够使得片内RAM模块M0/M1/L0/L1LH0能够获得最好的性能，控制寄存器的位
// 必须使能，这些位在设备硬件仿真寄存器内。TMX是TI的试验型产品
   DevEmuRegs.M0RAMDFT = 0x0300;
   DevEmuRegs.M1RAMDFT = 0x0300;
   DevEmuRegs.L0RAMDFT = 0x0300;
   DevEmuRegs.L1RAMDFT = 0x0300;
   DevEmuRegs.H0RAMDFT = 0x0300;
   
           
// 禁止看门狗模块
   SysCtrlRegs.WDCR= 0x0068;

// 初始化PLL模块
   SysCtrlRegs.PLLCR = 0xA;  //如果外部晶振为30M，则SYSCLKOUT=30*10/2=150MHz
// 延时，使得PLL模块能够完成初始化操作
   for(i= 0; i< 5000; i++){}
       
// 高速时钟预定标器和低速时钟预定标器，产生高速外设时钟HSPCLK和低速外设时钟LSPCLK
   SysCtrlRegs.HISPCP.all = 0x0001; // HSPCLK=150/2=75MHz
   SysCtrlRegs.LOSPCP.all = 0x0002;	// LSPCLK=150/4=37.5MHz

// 对工程中使用到的外设进行时钟使能
// SysCtrlRegs.PCLKCR.bit.EVAENCLK=1;        // EVA模块时钟功能
// SysCtrlRegs.PCLKCR.bit.EVBENCLK=1;        // EVB模块时钟功能
// SysCtrlRegs.PCLKCR.bit.SCIENCLKA=1;
// SysCtrlRegs.PCLKCR.bit.SCIENCLKB=1;


/*************************
  [User][Date:2013.12.26]    AD采样需打开 ADC和EVA
*************************/
        SysCtrlRegs.PCLKCR.bit.ADCENCLK = 1 ;    // ADC模块时钟功能
        SysCtrlRegs.PCLKCR.bit.EVAENCLK = 1 ; 	 // EVA模块时钟功能
//       SysCtrlRegs.PCLKCR.bit.EVBENCLK = 1 ;    // EVB模块时钟功能

//*************************


				
   EDIS;
	
}

/****************************************************************************
*
*名    称：KickDog()
*
*功    能：喂狗函数，当使用看门狗的时候，为了防止看门狗溢出，需要不断的给看门
*          狗"喂食"，给看门狗密钥寄存器周期性的写入0x55+0xAA序列，清除看门狗
*          计数器寄存器的值
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

/*
void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}
*/	
	
//===========================================================================
// No more.
//===========================================================================
