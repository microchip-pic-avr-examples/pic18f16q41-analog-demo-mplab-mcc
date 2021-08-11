/**
  OPA1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    opa1.h

  @Summary
    This is the generated header file for the OPA1 driver 

  @Description
    This header file provides APIs for driver for OPA1
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

#ifndef OPA1_H
#define OPA1_H

/**
  Section: Included Files
*/
#include <stdint.h>
#include <stdbool.h>

// Enumeration of R2/R1 resistor ratio
typedef enum
{
    OPA1_R2byR1_is_0dp07,
    OPA1_R2byR1_is_0dp14,
    OPA1_R2byR1_is_0dp33,
    OPA1_R2byR1_is_1,
    OPA1_R2byR1_is_1dp67,
    OPA1_R2byR1_is_3,
    OPA1_R2byR1_is_7,
    OPA1_R2byR1_is_15   
} OPA1_resistor_select;

// Enumeration of available Positive Channels
typedef enum
{
    OPA1_posChannel_Vss,
    OPA1_posChannel_GSEL,
    OPA1_posChannel_OPA1IN,
    OPA1_posChannel_Vdd_by_2,
    OPA1_posChannel_DAC1,
    OPA1_posChannel_DAC2
} OPA1_posChannel_select;

// Enumeration of available Positive Sources
typedef enum
{
    OPA1_RB5_IN0_pos = 0x0,   
    OPA1_RC3_IN1_pos = 0x1,   
    OPA1_RA2_IN2_pos = 0x2,   
    OPA1_RA0_IN3_pos = 0x3   
} OPA1_posSource_select;

// Enumeration of available Negative Channels
typedef enum
{
    OPA1_negChannel_No_Connection = 0x0,
    OPA1_negChannel_GSEL = 0x1,
    OPA1_negChannel_OPA1IN = 0x2,
    OPA1_negChannel_DAC1 = 0x4,
    OPA1_negChannel_DAC2 = 0x5
} OPA1_negChannel_select;

// Enumeration of available Negative Sources
typedef enum
{
    OPA1_RB4_IN0_neg = 0x0,   
    OPA1_RC3_IN1_neg = 0x1,   
    OPA1_RA2_IN2_neg = 0x2,   
    OPA1_RA0_IN3_neg = 0x3,   
    OPA1_Vss = 0x7   
} OPA1_negSource_select;

/**
 * @brief Initializes the OPA1 module
 *        This routine must be called before any other OPA1 routine
 * @return None
 * @param None
 */
void OPA1_Initialize(void);

/**
 * @brief Enables the OPA1 Charge Pump
 * @return None
 * @param None
 */
inline void OPA1_EnableChargePump(void);

/**
 * @brief Disables the OPA1 Charge Pump
 * @return None
 * @param None
 */
inline void OPA1_DisableChargePump(void);

/**
 * @brief Enables OPA1 to operate with unity gain 
 * @return None
 * @param None
 */
inline void OPA1_EnableSoftwareUnityGain(void);

/**
 * @brief Disables unity gain in OPA1 
 * @return None
 * @param None
 */
inline void OPA1_DisableSoftwareUnityGain(void);

/**
 * @brief Sets the positive channel as per user selection
 * @return None 
 * @param [in] Desired positive channel
          For available positive channels refer OPA1_posChannel_select enum from opa1.h file
 */
inline void OPA1_SetPositiveChannel(OPA1_posChannel_select posChannel);

/**
 * @brief Sets the positive source as per user selection
 * @return None 
 * @param [in] Desired positive source
          For available positive sources refer OPA1_posSource_select enum from opa1.h file
 */
inline void OPA1_SetPositiveSource(OPA1_posSource_select posSource);

/**
 * @brief Sets the negative channel as per user selection
 * @return None 
 * @param [in] Desired negative channel
          For available negative channels refer OPA1_negChannel_select enum from opa1.h file
 */
inline void OPA1_SetNegativeChannel(OPA1_negChannel_select negChannel);

/**
 * @brief Sets the negative source as per user selection
 * @return None 
 * @param [in] Desired negative source
          For available negative sources refer OPA1_negSource_select enum from opa1.h file
 */
inline void OPA1_SetNegativeSource(OPA1_negSource_select negSource);

/**
 * @brief Sets the R1 and R2 values of internal resistor ladder as per user selection
 * @return None 
 * @param [in] Desired resistor selection
               For available resistor values refer OPA1_resistor_sel enum from opa1.h file
 */
void OPA1_SetResistorLadder(OPA1_resistor_select resistorSelection);

/**
 * @brief Enables hardware override by setting the override enable bit
 * @return None 
 * @param None
 */
inline void OPA1_EnableHardwareOverride(void);

/**
 * @brief Selects the Hardware Override Source and polarity
          The OPA1_EnableHardwareOverride() routine must be called before this routine
 * @return None 
 * @param [in] Desired hardware override source and source polarity
 */
void OPA1_SetHardwareOverrideSource(uint8_t overrideSource, uint8_t polarity);

/**
 * @brief Disables the hardware override by clearing the override enable bit
 * @return None 
 * @param None
 */
inline void OPA1_DisableHardwareOverride(void);

/**
 * @brief Selects the Software Override Mode
          The OPA1_DisableHardwareOverride() routine must be called before this routine
 * @return None 
 * @param [in] Desired software override mode
 */
inline void OPA1_SetSoftwareOverride(uint8_t softwareControl);

/**
 * @brief Sets the input offset calibration 
 * @return None 
 * @param [in] Desired input offset
 */
inline void OPA1_SetInputOffset(uint8_t offset);

#endif //OPA1_H