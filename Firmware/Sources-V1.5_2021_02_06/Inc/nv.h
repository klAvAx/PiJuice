/*
 * nv.h
 *
 *  Created on: 12.12.2016.
 *      Author: milan
 */

#ifndef NV_H_
#define NV_H_

#include "stdint.h"
#include "eeprom.h"

#define NV_INVALID_VARIABLE        ((uint16_t)0x000f)
#define NV_READ_VARIABLE_SUCCESS   ((uint16_t)0)
#define NV_VARIABLE_NON_STORED       ((uint16_t)0xffffffff)

#define NV_IS_DATA_INITIALIZED	(nvInitFlag != 0Xffff)
#define NV_IS_VARIABLE_VALID(var)	(((~var)&0xFF) == (var>>8))

#define NV_VAR_LIST \
 NV_STATIC_START_ID, /* static variables are not deleted when reset to default*/ \
 NV_STATIC_ADDR_RESERVED0, \
 VDG_ILOAD_CALIB_KTA_NV_ADDR, /* current measurement calibration vta coeff*/ \
 VDG_ILOAD_CALIB_KTB_NV_ADDR, /* current measurement calibration vtb coeff*/ \
 RES_ILOAD_CALIB_ZERO_NV_ADDR, \
 NV_STATIC_ADDR_RESERVED1, \
 NV_STATIC_ADDR_RESERVED2, \
 NV_STATIC_ADDR_RESERVED3, \
 NV_STATIC_ADDR_RESERVED4, \
 NV_STATIC_ADDR_RESERVED5, \
 NV_STATIC_ADDR_RESERVED6, \
 NV_STATIC_ADDR_RESERVED7, \
 NV_STATIC_ADDR_RESERVED8, \
 NV_STATIC_ADDR_RESERVED9, \
 NV_STATIC_ADDR_RESERVED10, \
 NV_STATIC_ADDR_RESERVED11, \
 NV_STATIC_ADDR_RESERVED12, \
 NV_START_ID,  /* starting id of variables */ \
 NV_ADDR_RESERVED0, \
 BAT_PROFILE_NV_ADDR, \
 BAT_CAPACITY_NV_ADDR, \
 CHARGE_CURRENT_NV_ADDR, \
 CHARGE_TERM_CURRENT_NV_ADDR, \
 BAT_REG_VOLTAGE_NV_ADDR, \
 BAT_CUTOFF_VOLTAGE_NV_ADDR, \
 BAT_TEMP_COLD_NV_ADDR, \
 BAT_TEMP_COOL_NV_ADDR, \
 BAT_TEMP_WARM_NV_ADDR, \
 BAT_TEMP_HOT_NV_ADDR, \
 BAT_NTC_B_NV_ADDR, \
 BAT_NTC_RESISTANCE_NV_ADDR, \
 BAT_NTC_CRC_NV_ADDR, \
 FUEL_GAUGE_CONFIG_NV_ADDR, \
 CHARGING_CONFIG_NV_ADDR, /* NV_ADDR_RESERVED1 */ \
 CHARGER_INPUTS_CONFIG_NV_ADDR, /* NV_ADDR_RESERVED2 */ \
 WATCHDOG_CONFIGL_NV_ADDR, /*NV_ADDR_RESERVED4*/\
 NV_ADDR_RESERVED5, \
 BUTTON_PRESS_FUNC_SW1, \
 BUTTON_PRESS_CONFIG_SW1, \
 BUTTON_RELEASE_FUNC_SW1, \
 BUTTON_RELEASE_CONFIG_SW1, \
 BUTTON_SINGLE_PRESS_FUNC_SW1, \
 BUTTON_SINGLE_PRESS_CONFIG_SW1, \
 BUTTON_DOUBLE_PRESS_FUNC_SW1, \
 BUTTON_DOUBLE_PRESS_CONFIG_SW1, \
 BUTTON_LONG_PRESS1_FUNC_SW1, \
 BUTTON_LONG_PRESS1_CONFIG_SW1, \
 BUTTON_LONG_PRESS2_FUNC_SW1, \
 BUTTON_LONG_PRESS2_CONFIG_SW1, \
 WAKEUPONCHARGE_CONFIG_NV_ADDR, \
 BUTTON_PRESS_FUNC_SW2, \
 BUTTON_PRESS_CONFIG_SW2, \
 BUTTON_RELEASE_FUNC_SW2, \
 BUTTON_RELEASE_CONFIG_SW2, \
 BUTTON_SINGLE_PRESS_FUNC_SW2, \
 BUTTON_SINGLE_PRESS_CONFIG_SW2, \
 BUTTON_DOUBLE_PRESS_FUNC_SW2, \
 BUTTON_DOUBLE_PRESS_CONFIG_SW2, \
 BUTTON_LONG_PRESS1_FUNC_SW2, \
 BUTTON_LONG_PRESS1_CONFIG_SW2, \
 BUTTON_LONG_PRESS2_FUNC_SW2, \
 BUTTON_LONG_PRESS2_CONFIG_SW2, \
 NV_ADDR_RESERVED7, \
 BUTTON_PRESS_FUNC_SW3, \
 BUTTON_PRESS_CONFIG_SW3, \
 BUTTON_RELEASE_FUNC_SW3, \
 BUTTON_RELEASE_CONFIG_SW3, \
 BUTTON_SINGLE_PRESS_FUNC_SW3, \
 BUTTON_SINGLE_PRESS_CONFIG_SW3, \
 BUTTON_DOUBLE_PRESS_FUNC_SW3, \
 BUTTON_DOUBLE_PRESS_CONFIG_SW3, \
 BUTTON_LONG_PRESS1_FUNC_SW3, \
 BUTTON_LONG_PRESS1_CONFIG_SW3, \
 BUTTON_LONG_PRESS2_FUNC_SW3, \
 BUTTON_LONG_PRESS2_CONFIG_SW3, \
 NV_ADDR_RESERVED8, \
 NV_LED_FUNC_1, \
 NV_LED_PARAM_R_1, \
 NV_LED_PARAM_G_1, \
 NV_LED_PARAM_B_1, \
 NV_LED_FUNC_2, \
 NV_LED_PARAM_R_2, \
 NV_LED_PARAM_G_2, \
 NV_LED_PARAM_B_2, \
 NV_ADDR_RESERVED9, \
 NV_ADDR_RESERVED10, \
 POWER_REGULATOR_CONFIG_NV_ADDR, \
 NV_RUN_PIN_CONFIG, \
 NV_ADDR_RESERVED11, \
 OWN_ADDRESS1_NV_ADDR, \
 OWN_ADDRESS2_NV_ADDR, \
 ID_EEPROM_ADR_NV_ADDR, \
 NV_ADDR_RESERVED12, \
 IO_CONFIG1_NV_ADDR, \
 IO_CONFIG1_PARAM1_NV_ADDR, \
 IO_CONFIG1_PARAM2_NV_ADDR, \
 IO_CONFIG2_NV_ADDR, \
 IO_CONFIG2_PARAM1_NV_ADDR, \
 IO_CONFIG2_PARAM2_NV_ADDR, \
 NV_ADDR_RESERVED13, \
 BAT_CHEMISTRY_NV_ADDR, \
 BAT_OCV10L_NV_ADDR, \
 BAT_OCV10H_NV_ADDR, \
 BAT_OCV50L_NV_ADDR, \
 BAT_OCV50H_NV_ADDR, \
 BAT_OCV90L_NV_ADDR, \
 BAT_OCV90H_NV_ADDR, \
 BAT_R10L_NV_ADDR, \
 BAT_R10H_NV_ADDR, \
 BAT_R50L_NV_ADDR, \
 BAT_R50H_NV_ADDR, \
 BAT_R90L_NV_ADDR, \
 BAT_R90H_NV_ADDR, \
 WATCHDOG_CONFIGH_NV_ADDR, \
 ISENSE_RES_SPAN_L, \
 ISENSE_RES_SPAN_H


typedef enum
{
	NV_VAR_LIST,
	NV_VAR_NUM
} NvVarId_T;

/* Variables' number */
#define NB_OF_VAR             			NV_VAR_NUM//((uint8_t)0x04)

void NV_Init(void);
void NvSetDataInitialized(void);
void NvTask(void);
void NvSaveParameterReq(NvVarId_T id, uint16_t value);

void NV_FactoryReset(void);

uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);

bool NV_WriteVariable_U8(const uint16_t address, const uint8_t var);
bool NV_ReadVariable_U8(const uint16_t address, uint8_t * const p_var);

bool NV_WriteVariable_S8(const uint16_t address, const int8_t var);
bool NV_ReadVariable_S8(const uint16_t address, int8_t * const p_var);
void NV_WipeVariable(const uint16_t address);

uint16_t NvReadVariableU8(uint16_t VirtAddress, uint8_t *pVar);


#endif /* NV_H_ */
