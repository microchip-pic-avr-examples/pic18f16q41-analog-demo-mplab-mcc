/**
  OPA1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    opa1.c

  @Summary
    This is the generated driver implementation file for the OPA1 driver

  @Description
    This header file provides implementations for driver APIs for OPA1
    Generation Information :
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.31
        MPLAB             :  MPLAB X v5.45

*/

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

/**
   Section: Included Files
*/

#include <xc.h>
#include "../opa1.h"

/**
  Section: OPA1 Module APIs
*/

void OPA1_Initialize(void)
{
    //GSEL R1 = 15R and R2 = 1R, R2/R1 = 0.07; RESON Disabled; NSS OPA1IN0-; 
    OPA1CON1 = 0x0;

    //NCH No Connection; PCH OPA1IN+; 
    OPA1CON2 = 0x2;

    //FMS No Connection; PSS OPA1IN2+; 
    OPA1CON3 = 0x2;

    //OREN Software Override; HWCH User Defined Feedback; ORPOL Non Inverted; HWCL User Defined Feedback; 
    OPA1HWC = 0x0;

    //ORS LFINTOSC; 
    OPA1ORS = 0x0;

    //EN Enabled; CPON Enabled; UG OPA Output; SOC User Defined Feedback; 
    OPA1CON0 = 0xA8;
}

inline void OPA1_EnableChargePump(void)
{
    OPA1CON0bits.CPON = 1;
}
 
inline void OPA1_DisableChargePump(void)
{
    OPA1CON0bits.CPON = 0;
}

inline void OPA1_EnableSoftwareUnityGain(void)
{
    OPA1CON0bits.UG = 1;
}

inline void OPA1_DisableSoftwareUnityGain(void)
{
    OPA1CON0bits.UG = 0;
}

inline void OPA1_SetPositiveChannel(OPA1_posChannel_select posChannel)
{
    OPA1CON2bits.PCH = posChannel;
}

inline void OPA1_SetPositiveSource(OPA1_posSource_select posSource)
{
    OPA1CON3bits.PSS = posSource;
}

inline void OPA1_SetNegativeChannel(OPA1_negChannel_select negChannel)
{
    OPA1CON2bits.NCH = negChannel;
}

inline void OPA1_SetNegativeSource(OPA1_negSource_select negSource)
{
    OPA1CON1bits.NSS = negSource;
}

void OPA1_SetResistorLadder(OPA1_resistor_select resistorSelection)
{
    OPA1CON1bits.RESON = 1;
    OPA1CON1bits.GSEL = resistorSelection;
}

inline void OPA1_EnableHardwareOverride(void)
{
   OPA1HWCbits.OREN = 1;
}

void OPA1_SetHardwareOverrideSource(uint8_t overrideSource, uint8_t polarity)
{
    OPA1ORS = overrideSource;
    OPA1HWCbits.ORPOL = polarity;
}

inline void OPA1_DisableHardwareOverride(void)
{
    OPA1HWCbits.OREN = 0;
}

inline void OPA1_SetSoftwareOverride(uint8_t softwareControl)
{
    OPA1CON0bits.SOC = softwareControl;
}

inline void OPA1_SetInputOffset(uint8_t offset)
{
    OPA1OFFSET = offset;
}