// ----------------------------------------------------------------------------
/*!
 * @file		osloop.c
 * @author    	John Steggall
 * @date       	19 March 2021
 * @brief       Handles the system operation and general order of things.
 * @details     Initialises the system beyond the cubemx hardware initialisers
 * 				and calls the service routines on the os loop timer period.
 * 				Each service routine is expected to handle it's own periodic
 * 				update if the call frequency is too high.
 *
 * @note        None.
 *
 * @warning     No service routine should block or the whole thing falls apart!
 */
// ----------------------------------------------------------------------------
// Include section - add all #includes here:

#include "main.h"
#include "system_conf.h"

#include "adc.h"
#include "iodrv.h"
#include "analog.h"
#include "i2cdrv.h"
#include "led.h"
#include "hostcomms.h"


// ----------------------------------------------------------------------------
// Defines section - add all #defines here:


#define OSLOOP_LOOP_TRACKER_COUNT		16u

// ----------------------------------------------------------------------------
// Function prototypes for functions that only have scope in this module:

void OSLOOP_Service(void);


// ----------------------------------------------------------------------------
// Variables that only have scope in this module:

static volatile uint32_t m_osloopTimeTrack[OSLOOP_LOOP_TRACKER_COUNT];
static uint32_t m_osloopTimeTrackIdx = 0u;


// ----------------------------------------------------------------------------
// Variables that have scope from outside this module:

extern TIM_HandleTypeDef htim6;


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// INTERRUPT HANDLERS
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ****************************************************************************
/*!
 * OSLOOP_TIMER_IRQHandler handles the IRQ generated by the timer. Actually, will
 * just be on update and triggers the osloop.
 */
// ****************************************************************************
void OSLOOP_TIMER_IRQHandler(void)
{
	OSLOOP_Service();

	TIMER_OSLOOP->SR &= ~(TIM_IT_UPDATE);
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// FUNCTIONS WITH GLOBAL SCOPE
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ****************************************************************************
/*!
 * OSLOOP_Init calls the modules init routines
 * @param	none
 * @retval	none
 */
// ****************************************************************************
void OSLOOP_Init(void)
{
	const uint32_t sysTime = HAL_GetTick();

	ADC_Init(sysTime);
	IODRV_Init(sysTime);
	ANALOG_Init(sysTime);
	I2CDRV_Init(sysTime);
	HOSTCOMMS_Init(sysTime);

	LED_Init(sysTime);

	/* Start the os timer */
	TIMER_OSLOOP->CR1 |= TIM_CR1_CEN;
	TIMER_OSLOOP->DIER |= TIM_IT_UPDATE;
}


// ****************************************************************************
/*!
 * OSLOOP_Service calls the module service routines. None must block!!!
 *
 * @param	none
 * @retval	none
 */
// ****************************************************************************
void OSLOOP_Service(void)
{
	const uint32_t sysTime = HAL_GetTick();
	const uint32_t timeIn = TIMER_OSLOOP->CNT;

	ADC_Service(sysTime);
	IODRV_Service(sysTime);
	ANALOG_Service(sysTime);

	I2CDRV_Service(sysTime);
	HOSTCOMMS_Service(sysTime);

	LED_Service(sysTime);

	m_osloopTimeTrack[m_osloopTimeTrackIdx] = (TIMER_OSLOOP->CNT - timeIn);
	m_osloopTimeTrackIdx++;

	if (OSLOOP_LOOP_TRACKER_COUNT == m_osloopTimeTrackIdx)
	{
		m_osloopTimeTrackIdx = 0u;
	}
}


// ****************************************************************************
/*!
 * OSLOOP_Shutdown calls the module shutdown routines in preperation for the
 * low power stop mode.
 *
 * @param	none
 * @retval	none
 */
// ****************************************************************************
void OSLOOP_Shutdown(void)
{
	// Stop the interrupt occuring
	TIMER_OSLOOP->DIER &= ~(TIM_IT_UPDATE);

	// Shutdown all modules for low power
	ADC_Shutdown();
	IODRV_Shutdown();
	ANALOG_Shutdown();
	I2CDRV_Shutdown();

	LED_Shutdown();
}


// ****************************************************************************
/*!
 * OSLOOP_Restart reinitilises the modules after a wake from low power stop
 *
 * @param	none
 * @retval	none
 */
// ****************************************************************************
void OSLOOP_Restart(void)
{
	const uint32_t sysTime = HAL_GetTick();

	ADC_Init(sysTime);
	IODRV_Init(sysTime);
	ANALOG_Init(sysTime);
	I2CDRV_Init(sysTime);

	LED_Init(sysTime);

	/* Start the os timer */
	TIMER_OSLOOP->CR1 |= TIM_CR1_CEN;
	TIMER_OSLOOP->DIER |= TIM_IT_UPDATE;
}


// ****************************************************************************
/*!
 * OSLOOP_AtomicAccess is a really awful way of ensuring that variables are not
 * half baked on access or change if evaluated twice. Don't use this unless you
 * are desperate.
 *
 * @param	bool		true = access to a variable is required
 * 						false = access to a variable is no longer required
 * @retval	none
 */
// ****************************************************************************
void OSLOOP_AtomicAccess(bool access)
{
	if (true == access)
	{
		TIMER_OSLOOP->DIER &= ~(TIM_IT_UPDATE);
	}
	else
	{
		TIMER_OSLOOP->DIER |= TIM_IT_UPDATE;
	}
}

