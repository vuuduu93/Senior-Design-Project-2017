/*
 * File:   Source.c
 * Author: nicholasvu
 *
 * Created on January 18, 2017, 7:51 PM
 */



#include <p33FJ06GS101A.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <libpic30.h>
#include <I2CSlaveDrv.h>	//Include file for I2C1 Driver

#define LCD_data     LATB 
#define LCD_rs      _LATA1
#define LCD_rw      _LATA3
#define LCD_en      _LATA4
#define VREF        3.29 


//int i, j;
//int u16_adcVal;
//float f_adcVal;
//float tempc;
//float tempf;
//int UP = 1;
//int FlagCount = 0;
//
//
//void OSC_Config()
//{
//    _NOSC = 0b001;
//    CLKDIVbits.FRCDIV = 0b000;
//    CLKDIVbits.PLLPRE = 0b00001; 
//    PLLFBD = 0b001000100;  
//    CLKDIVbits.PLLPOST = 0b11; 
//    OSCTUN = 4;   
//    
//    __builtin_write_OSCCONH(0X01);
//    __builtin_write_OSCCONL(OSCCON | 0X01);
//    
//    
//    while(OSCCONbits.COSC !=1);
//    while (OSCCONbits.LOCK !=1);
//}   
//
//
//void LCD_short_busy() 
//{
//    for(i = 0; i < 1; i++);    //This portion of the code is very important
//    for(j = 0; j < 90; j++);  //If this loop is long, the motor will "hiccup"
//}
//
//
//void LCD_command(unsigned char var)
//{
//    LCD_data = var;
//    LCD_rs   = 0;
//    LCD_rw   = 0;
//    LCD_en   = 1;  
//    LCD_en   = 0;  
//    LCD_short_busy();
//    
//}
//
//
//void LCD_init()
//{
//    LCD_command(0x0038); 
//    LCD_command(0x000E);
//    LCD_command(0x0006);
//    LCD_command(0x00C0);
//    LCD_command(0x0001);
//    
//}
//
//void LCD_senddata(unsigned char var) 
//{
//    LCD_data = var;
//    LCD_rs   = 1;
//    LCD_rw   = 0;
//    LCD_en   = 1;  
//    LCD_en   = 0; 
//    LCD_short_busy();
//}
//
//void LCD_sendstring(char*var) 
//{
//    while(*var)
//        LCD_senddata(*var++);
//    
//  
//}
//
//void config_ADC (void)
//{
//    AD1CON1 = 0x0000;
//    AD1CON2 = 0; 
//    AD1CON3 = 0x0001; 
//    AD1CSSL = 0;
//    
//    IFS0bits.AD1IF = 0; 
//    AD1CON1bits.ADON = 1;
//} 
//
//
//int run_ADC (int ch) 
//{
//     AD1CHS0bits.CH0SA = ch;
//     AD1CON1bits.SAMP = 1; 
//     TMR3 = 0;
//     while (TMR3 < 1000);
//     AD1CON1bits.SAMP = 0; 
//     while (!AD1CON1bits.DONE); 
//     AD1CON1bits.DONE = 0; 
//     return ADC1BUF0; 
//        
//} 
//void config_IO (void)
//{ 
//    //Port A configuration for the ADC
//    TRISA =  0b00001; 
//    ANSELA = 0b00001; 
//    LATA =   0b00001;
//    PORTA =  0b00001;
//    
//    //Port B configuration for LCD and H-Bridge IC
//    ANSELB = 0;
//    TRISB = 0; 
//    PORTB = 0;
//    LATB = 0xFFFF; 
//    
//}
//
//void config_T2 (void)
//{ 
//    T2CON = 0; 
//    T2CONbits.TCKPS = 0b11;
//    PR2  = 7812;
//    TMR2 = 0;
//    _T2IP = 2;
//    _T2IE = 0; 
//    _T2IF = 0;
//    T2CONbits.TON = 1; 
//  
//}
//void config_T3 (void)
//{ 
//    T3CON = 0; 
//    T3CONbits.TCKPS = 0b11; 
//    PR3 = 62499; 
//    TMR3 = 0; 
//    T3CONbits.TON = 1; 
//    _T3IP = 2;
//    _T3IE = 0; 
//    _T3IF = 0;
//    } 
//
//void Run_T3 (int time) //My own configuration for running timer 3 using a pointer
//{  
//    int i = time;
//    
//    for ((i = 0); (i < time); i++)  
//    {
//    
//        T3CONbits.TCKPS  = 0b11;
//        PR3     = 62499;
//        T3CONbits.TON   = 0;
//        TMR3 = 0;
//        T3CONbits.TON   = 1;
//        while (!_T3IF);
//        _T3IF = 0;
//    }          
//}  
//
//
//
//void config_PWM () 
//{
//    
//    OC1CON1 = 0; 
//    OC1CON2 = 0;
//    OC1CON1bits.OCTSEL = 0b111;
//    OC1CON1bits.OCM = 7;
//    OC1R = PWM_Period / 2; 
//    OC1RS = PWM_Period;
//    OC1CON2bits.OCINV = 1; 
//    OC1CON2bits.SYNCSEL = 0x1F; 
//     _RP41R = 0b010000; // OC1 Output tied to RP41/RB9 (1,2EN Pin) (pg 180)
//   
//     
//} 
//
//void config_T1 (void) 
//{
//    
//    _T1IF   = 1;
//    _T1IP   = 1; 
//    _T1IE   = 1; 
//    PR1     = 62499;
//    T1CONbits.TCKPS = 0b11;
//    T1CONbits.TON  = 1;
//    
//}
//
//void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt (void)
//{
//    
//    if (tempf && FlagCount == 1)
//    {
//        FlagCount++;  
//    }
//    if (tempf && FlagCount == FlagCount+1)
//    {
//        UP = !UP;
//        FlagCount++;
//    }
//    if (!tempf)
//    {
//        FlagCount = 1;
//    }
//    
//    TMR1    = 0;   
//    _T1IF   = 0;
//
//}


unsigned char RAMBuffer[128];	//RAM area which will work as EEPROM for Master I2C device
unsigned char *RAMPtr;			//Pointer to RAM memory locations
struct FlagType Flag;

/*****************************************************************
		Init I2C1 Bus
*****************************************************************/
void i2c1_init(void)
{
	#if !defined(USE_I2C_Clock_Stretch)
		I2C1CON = 0x8000;	//Enable I2C1 module
	#else
		I2C1CON = 0x9040;	//Enable I2C1 module, enable clock stretching
	#endif
	

	I2C1ADD = 0x50;			// 7-bit I2C slave address must be initialised here. 
	
	IFS1=0;
	RAMPtr = &RAMBuffer[0];	//set the RAM pointer and points to beginning of RAMBuffer
	Flag.AddrFlag = 0;	//Initlize AddFlag
	Flag.DataFlag = 0;	//Initlize DataFlag
	_SI2C1IE = 1;
}

/*
Function Name: SI2C1Interrupt
Description : This is the ISR for I2C1 Slave interrupt.
Arguments	 : None
*/
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void)
{
	unsigned char Temp;	//used for dummy read
    
	if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 0))	//Address matched
		{
			Temp = I2C1RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 1))	//check for data	
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;	
				Flag.DataFlag = 1;	//next byte is data
				RAMPtr = RAMPtr + I2C1RCV;
				#if defined(USE_I2C_Clock_Stretch)
					I2C1CONbits.SCLREL = 1;	//Release SCL1 line
				#endif
			}
			else if(Flag.DataFlag)
			{
				*RAMPtr = (unsigned char)I2C1RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
				RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
				#if defined(USE_I2C_Clock_Stretch)
					I2C1CONbits.SCLREL = 1;	//Release SCL1 line
				#endif
			}
		}
	else if((I2C1STATbits.R_W == 1)&&(I2C1STATbits.D_A == 0))
	{
		Temp = I2C1RCV;
		I2C1TRN = *RAMPtr;	//Read data from RAM & send data to I2C master device
		I2C1CONbits.SCLREL = 1;	//Release SCL1 line
		while(I2C1STATbits.TBF);//Wait till all 
		RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
	}
	_SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}	

//**i2C Slave Drive Sample Code** ***For reference only***//
// Confiuration Register Settings
// Internal FRC Oscillator
_FOSCSEL(FNOSC_FRC);		// FRC Oscillator 
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_NONE); 
								// Clock Switching is enabled and Fail Safe Clock Monitor is disabled
								// OSC2 Pin Function: OSC2 is Clock Output
								// Primary Oscillator Mode: Disabled


_FWDT(FWDTEN_OFF);              // Watchdog Timer Enabled/disabled by user software


//**i2C Slave Drive Sample Main Code** ***For reference only***//

int main(void)
{
	unsigned int i;
	// Configure Oscillator to operate the device at 40Mhz
	// Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
	// Fosc= 7.37*43/(2*2)=80Mhz for 7.37 input clock
	PLLFBD=41;					// M=43
	CLKDIVbits.PLLPOST=0;		// N1=2
	CLKDIVbits.PLLPRE=0;		// N2=2
	OSCTUN=0;					// Tune FRC oscillator, if FRC is used

	// Disable Watch Dog Timer
	RCONbits.SWDTEN=0;

	// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x01);		// Initiate Clock Switch to
										// FRC with PLL (NOSC=0b001)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b001);	// Wait for Clock switch to occur

	// Wait for PLL to lock
	while(OSCCONbits.LOCK!=1);
	//Now PLL is ready
	for(i = 0;i<256;i++)
	{
		RAMBuffer[i] = i;	//Initlize RAMBuffer with some value
							//in case MasterI2C device wants to read
							//before it writes to it.
	}
	i2c1_init();
	while(1)
	{
		//Do your application task	
	}
}


//int main(void)
//{
////	char S[80];
////    char Z[80];
////    double d_c;
////    OSC_Config(); 
////    config_T1(); 
////    config_T2(); 
////    config_T3(); 
////    config_IO(); 
////    config_ADC(); 
////    LCD_init();
////    config_PWM();
//    
//	
//}