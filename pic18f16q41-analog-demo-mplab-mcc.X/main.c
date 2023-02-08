/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

#define setADCCChannel(X) do { ADPCH = X; } while (0)
#define setupResistorLadder() do { OPA1CON1bits.NSS = 0b111; OPA1CON3bits.OPA1FMS = 0b10; } while (0)

static volatile bool resultsReady, gainChanged;
const char* gains[] = {"1", "1.07", "1.14", "1.33", "2", "2.67", "4", "8", "16"};

void adjustGain(void)
{
    //Set Print Flag
    gainChanged = true;
    
    //Stop Timer 0 (restarted in main)
    Timer0_Stop();
    
    if (OPA1CON0bits.UG)
    {
        //Unity Gain -> First Step of Resistor Ladder
        
        //Enable Resistor Ladder
        OPA1CON1bits.RESON = 1;
        
        //Connect to resistor ladder
        OPA1CON2bits.NCH = 0b001;
        
        //Disable Unity Gain
        OPA1CON0bits.UG = 0;
    }
    else if (OPA1CON1bits.GSEL == 0b111)
    {
        //Last Step of Resistor Ladder -> Unity Gain
        
        //Reset Ladder to step 0
        OPA1CON1bits.GSEL = 0;
        
        //Turn off Resistor Ladder
        OPA1CON1bits.RESON = 0;
        
        //Disconnect Resistor Ladder
        OPA1CON2bits.NCH = 0b000;
        
        //Enable Unity Gain
        OPA1CON0bits.UG = 1;
    }
    else
    {
        //Increment Resistor Ladder
        OPA1CON1bits.GSEL++;
    }
}

void printResults(void)
{
    //Set Print Flag
    resultsReady = true;
}

const char* getCurrentGain(void)
{
    uint8_t index = 0;
    
    if (!OPA1CON0bits.UG)
    {
       //Not in Unity Gain (Gain > 1)
       index = OPA1CON1bits.GSEL + 1; 
    }
    
    return gains[index];
}

int main(void)
{
    SYSTEM_Initialize();
        
    //Select OPAMP Output Pin for ADCC
    setADCCChannel(channel_ANC2);
    
    //Setup the resistor ladder for the OPAMP, but does not connect to it.
    setupResistorLadder();
    
    //Clear Print Flags
    resultsReady = false;
    gainChanged = false;

    //This function sets the flag to print results
    ADCC_SetADIInterruptHandler(&printResults);
    
    //This functions changes the gain of the OPAMP
    Timer2_OverflowCallbackRegister(&adjustGain);
    
    //Enable Interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    //Assumes 3.3V operation
    const float bitsPerVolt = 3.3 / 4096;
    
    float result = 0.0;
    
    while(1)
    {
        if (gainChanged)
        {
            //Clear the print flag
            gainChanged = false;

            //Print the new gain
            printf("New Gain: %s\n\r\n\r", getCurrentGain());
            
            //Reset Timer 0
            Timer0_Write(0);
            
            //Restart Timer 0
            Timer0_Start();
        }
        else if (resultsReady)
        {
            //Clear the print flag
            resultsReady = false;
            
            //Convert to a floating point
            result = ADCC_GetConversionResult() * bitsPerVolt;
            
            //Toggle the LED Indicator
            LED0_Toggle();
            
            //Print Results
            printf("Current Gain: %s\n\r", getCurrentGain());
            printf("Measured: %1.3fV\n\r\n\r", result);
        }
        
        //Finish Sending Data
        while (!UART1_IsTxDone());
        
        //If the gain was changed while printing, rerun the loop
        if (gainChanged)
            continue;
        
        //Sleep while idle
        Sleep();
        NOP();
    }    
}