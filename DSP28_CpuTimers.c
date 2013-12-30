/*************************************************
Copyright (C), 1988-2013, MagicFill Tech. Co., Ltd.

File name:    DSP28_CpuTimers.c // 文件名
Author: Magicfillcs    Version: 1.0     Date: 2013.12.30 // 作者、版本及完成日期
Description: 
    1.初始化32位CPU定时器

    // 用于详细说明此程序文件完成的主要功能，与其他模块
    // 或函数的接口，输出值、取值范围、含义及参数间的控
    // 制、顺序、独立或依赖等关系

Others:     // 其它内容的说明
    1.IDE: CCS 3.3


Function List: // 主要函数列表，每条记录应包括函数名及功能简要说明

    1. void InitCpuTimers(void); 
    //CPU定时器初始化程序
    2. void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
    // Freq    为系统时钟频率，单位MHz,主要看SYSCLKOUT的值,一般是150MHz
    // Period  为希望实现的CPU周期，单位是us(1s=1 000 000 us)
    // 使用示例：ConfigCpuTimer(&CpuTimer0,150,1000000); 定时1s 

History: // 修改历史记录列表，每条修改记录应包括修改日期、修改
         // 者及修改内容简述
    1. Date:
    Author:
    Modification:
    2. ...
*************************************************/


#include "DSP28_Device.h"

struct CPUTIMER_VARS CpuTimer0; //对用户开放的CPU定时器只有CpuTimer0 
struct CPUTIMER_VARS CpuTimer1; //CpuTimer1和CpuTimer2被保留用作实时操作系统OS（例如DSP BIOS）
struct CPUTIMER_VARS CpuTimer2; //

/****************************************************************************
*
*名    称：InitCpuTimers()
*
*功    能：初始化CpuTimer0。
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitCpuTimers(void)
{
	CpuTimer0.RegsAddr = &CpuTimer0Regs; //使得CpuTimer0.RegsAddr 指向定时器寄存器
	
	CpuTimer0Regs.PRD.all  = 0xFFFFFFFF; //初始化CpuTimer0的周期寄存器

	CpuTimer0Regs.TPR.all  = 0;          //初始化定时器预定标计数器
	CpuTimer0Regs.TPRH.all = 0;
	
	CpuTimer0Regs.TCR.bit.TSS = 1;       //停止定时器       

	CpuTimer0Regs.TCR.bit.TRB = 1;       //将周期寄存器PRD中的值装入计数器寄存器TIM中           
	
	CpuTimer0.InterruptCount = 0;        //初始化定时器中断计数器
}	
	
/****************************************************************************
*
*名    称：ConfigCpuTimer()
*
*功    能：此函数将使用Freq和Period两个参数来对CPU定时器进行配置。Freq以MHz
*          为单位，Period以us作为单位。
*
*入口参数：*Timer（指定的定时器），Freq，Period
*
*出口参数：无
*
****************************************************************************/

void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
	Uint32  temp;
	
	Timer->CPUFreqInMHz = Freq;
	Timer->PeriodInUSec = Period;
	temp = (long) (Freq * Period);
	Timer->RegsAddr->PRD.all = temp;  //给定时器周期寄存器赋值

	Timer->RegsAddr->TPR.all  = 0;    //给定时器预定标寄存器赋值
	Timer->RegsAddr->TPRH.all  = 0;
	
	// 初始化定时器控制寄存器:
	Timer->RegsAddr->TCR.bit.TIF=1;   //清除中断标志位
	Timer->RegsAddr->TCR.bit.TSS = 1; //停止定时器 
	Timer->RegsAddr->TCR.bit.TRB = 1; //定时器重装，将定时器周期寄存器的值装入定时器计数器寄存器
	Timer->RegsAddr->TCR.bit.SOFT = 1;
	Timer->RegsAddr->TCR.bit.FREE = 1;     
	Timer->RegsAddr->TCR.bit.TIE = 1; //使能定时器中断
	
	Timer->InterruptCount = 0;        //初始化定时器中断计数器
}

//===========================================================================
// No more.
//===========================================================================
