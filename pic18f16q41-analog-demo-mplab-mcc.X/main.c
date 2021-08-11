/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
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
    
    while(1)
    {
        if (resultsReady)
        {
            //Clear the print flag
            resultsReady = false;
            
            //Toggle the LED Indicator
            LED0_Toggle();
            
            //Print Results
            printf("Current Gain: %s\n\r", getCurrentGain());
            printf("Measurement: 0x%X\n\r\n\r", ADCC_GetConversionResult());
        }
        else if (gainChanged)
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
        
        //Finish Sending Data
        while (!UART1_IsTxDone());
        
        //Sleep while idle
        Sleep();
        NOP();
    }    
}