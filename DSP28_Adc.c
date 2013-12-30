/*************************************************
Copyright (C), 1988-2013, MagicFill Tech. Co., Ltd.

File name:    DSP28_Adc.c // 文件名
Author: Magicfillcs    Version: 1.0     Date: 2013.12.30 // 作者、版本及完成日期
Description: 
    1.对2812的AD模块进行初始化

    // 用于详细说明此程序文件完成的主要功能，与其他模块
    // 或函数的接口，输出值、取值范围、含义及参数间的控
    // 制、顺序、独立或依赖等关系

Others:     // 其它内容的说明
    1.IDE: CCS 3.3


Function List: // 主要函数列表，每条记录应包括函数名及功能简要说明

    1. InitAdc(); DSP2812的AD模块初始化程序

History: // 修改历史记录列表，每条修改记录应包括修改日期、修改
         // 者及修改内容简述
    1. Date:
    Author:
    Modification:
    2. ...
*************************************************/




/****************************************************************************
*
*文件名：DSP28_Adc.c
*
*功  能：对2812的AD模块进行初始化
*
*作  者: likyo from hellodsp
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitAdc()
*
*功    能：AD初始化程序
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

    unsigned int i;
	
	AdcRegs.ADCTRL1.bit.RESET=1;		//[User]复位
	NOP;
	AdcRegs.ADCTRL1.bit.RESET=0;
	
	AdcRegs.ADCTRL1.bit.SUSMOD=3;	//仿真暂停时，序列发生器和其他数字电路逻辑立即停止
	
	AdcRegs.ADCTRL1.bit.ACQ_PS=0;	//采样窗口大小，SOC脉冲宽度为1个ADCLK 
/****************************************
[User][Date:2013.12.26]

SOC脉冲宽度1等于 ACQ_PS的值 + 1
****************************************/

	
	AdcRegs.ADCTRL1.bit.CPS=0;      	//核时钟预定标器，等于0，未将时钟进行2分频
	
	AdcRegs.ADCTRL1.bit.CONT_RUN=0;   	//运行于启动/停止模式

/****************************************
[User][Date:2013.12.26]

级联方式，SEQ1和SEQ2级联起来，作为一个16状态序列发生器SEQ
****************************************/	
    AdcRegs.ADCTRL1.bit.SEQ_CASC=1;    //级联方式



/****************************************
[User][Date:2013.12.26]

参考ADCTRL3寄存器中对各bit的定义
****************************************/	
	AdcRegs.ADCTRL3.bit.ADCBGRFDN=3;
	for(i=0;i<10000;i++)	NOP;
	AdcRegs.ADCTRL3.bit.ADCPWDN=1;
	for(i=0;i<5000;i++)	NOP;
	


	AdcRegs.ADCTRL3.bit.ADCCLKPS=15;     //ADCLK=HSPCLK/30
	
	AdcRegs.ADCTRL3.bit.SMODE_SEL=0;     //采用顺序采样模式
	
	AdcRegs.MAX_CONV.bit.MAX_CONV=15;    //总共采样16路
	//////[User][###不懂###] 


	AdcRegs.CHSELSEQ1.bit.CONV00=0;
	AdcRegs.CHSELSEQ1.bit.CONV01=1;
	AdcRegs.CHSELSEQ1.bit.CONV02=2;
	AdcRegs.CHSELSEQ1.bit.CONV03=3;
	
	AdcRegs.CHSELSEQ2.bit.CONV04=4;
	AdcRegs.CHSELSEQ2.bit.CONV05=5;
	AdcRegs.CHSELSEQ2.bit.CONV06=6;
	AdcRegs.CHSELSEQ2.bit.CONV07=7;
	
	AdcRegs.CHSELSEQ3.bit.CONV08=8;
	AdcRegs.CHSELSEQ3.bit.CONV09=9;
	AdcRegs.CHSELSEQ3.bit.CONV10=10;
	AdcRegs.CHSELSEQ3.bit.CONV11=11;
	
	AdcRegs.CHSELSEQ4.bit.CONV12=12;
	AdcRegs.CHSELSEQ4.bit.CONV13=13;
	AdcRegs.CHSELSEQ4.bit.CONV14=14;
	AdcRegs.CHSELSEQ4.bit.CONV15=15;
	
	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR=1;
	//清除SEQ1中的中断标志位INT_SEQ1
	
	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ2_CLR=1;	
	//清除SEQ2中的中断标志位INT_SEQ2
	
	AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ=0;
	AdcRegs.ADCTRL2.bit.RST_SEQ1=0;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1=1;
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1=0;
	AdcRegs.ADCTRL2.bit.EVA_SOC_SEQ1=0;
	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1=0;
	AdcRegs.ADCTRL2.bit.RST_SEQ2=0;
	AdcRegs.ADCTRL2.bit.SOC_SEQ2=0;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2=0;
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2=0;
	AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ2=0;
	AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;
	
	
}	




//===========================================================================
// No more.
//===========================================================================
