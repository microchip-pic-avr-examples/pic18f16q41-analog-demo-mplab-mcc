 /**
   CLC2 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    clc2.h

   @Summary
     This is the generated header file for the CLC2 driver.
 
   @Description
     This header file provides APIs for driver for CLC2 driver.
     Generation Information :
         Driver Version    :  1.0.0
     The generated drivers are tested against the following:
         Compiler          :  XC8 v2.20
         MPLAB             :  MPLABX v5.40
 */

/*
� [2021] Microchip Technology Inc. and its subsidiaries.

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

#ifndef CLC2_H
 #define CLC2_H
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
  Section: CLC2 APIs
*/

/**
  @Summary
    Initializes the CLC2

  @Description
    This routine configures the CLC2 specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment

  @Example
    <code>
    CLC2_Initialize();
    </code>
*/
void CLC2_Initialize(void);

/**
  @Summary
    Returns output pin status of the CLC module.

  @Description
    This routine returns output pin status of the CLC module.

  @Param
    None.

  @Returns
    Output pin status
 
  @Example 
    <code>
    bool outputStatus;
    outputStatus = CLC2_OutputStatusGet();
    </code>
*/

bool CLC2_OutputStatusGet(void);

#endif  // CLC2_H
/**
 End of File
*/

