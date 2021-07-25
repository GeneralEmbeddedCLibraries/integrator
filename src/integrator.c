// Copyright (c) 2021 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      integrator.c
*@brief     Integrator for general purpose usage
*@author    Ziga Miklosic
*@date      27.02.2021
*@version   V1.0.1
*
*@section Description
*
*	Interator module for general C application use. There are two
*	types of implementation: simple and trapezoid.
*
*	In case of low sampling frequency and high precission integration is
*	needed then it is recommended to use trapezoid one.
*
*@section Code_example
*@code
*
*	// Declare simple integral instance
*	static p_integrator_simple_t g_integrator_simple = NULL;
*
*	// Init integrator
*	if ( eINTEGRATOR_OK != integrator_simple_init( &g_integrator_simple, APP_STEWARD_LOOP_PERIOD_S, 0.0 ))
*   {
*    	// Initialization failed...
*    	// Further action here...
*   }
*
*	// Update - integrate wanted signal
*	@period_time
*	{
*		integral_of_signal = integrator_simple_update( g_integrator_simple, signal );
*	}
*
*@endcode
*
*/
////////////////////////////////////////////////////////////////////////////////
/*!
* @addtogroup INTEGRATOR
* @{ <!-- BEGIN GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "integrator.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 * 	Simple integration
 */
typedef struct integrator_simple_s
{
	float32_t 	y;			/**<Current value of integration */
	float32_t 	dt;			/**<Period of integration - time difference between two integrations*/
	bool		is_init;	/**<Initialization success flag */
} integrator_simple_t;

/**
 * 	Trapezoid integration
 */
typedef struct integrator_trapezoid_s
{
	float32_t 	y;			/**<Current value of integration */
	float32_t 	x_prev;		/**<Previous value of input*/
	float32_t 	dt;			/**<Period of integration - time difference between two integrations*/
	bool		is_init;	/**<Initialization success flag */
} integrator_trapezoid_t;


////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup INTEGRATOR_API
* @{ <!-- BEGIN GROUP -->
*
* 	Following function are part or integrator API.
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Initialize simple integrator
*
* @param[out]  	p_int		- Pointer to integral instance
* @param[in]  	dt			- Update (period) time
* @param[in]  	init_value	- Initial value of integral
* @return       status		- Either OK or Error
*/
////////////////////////////////////////////////////////////////////////////////
integrator_status_t integrator_simple_init(p_integrator_simple_t * p_int, const float32_t dt, const float32_t init_value)
{
	integrator_status_t status = eINTEGRATOR_OK;

	if ( NULL != p_int )
	{
		// Allocate space
		*p_int = malloc( sizeof( integrator_simple_t ));

		// Check for success allocation
		if ( NULL != *p_int )
		{
			// Store for later use
			(*p_int)->dt = dt;
			(*p_int)->y = init_value;

			// Init success
			(*p_int)->is_init = true;
		}
		else
		{
			status = eINTEGRATOR_ERROR;
		}
	}
	else
	{
		status = eINTEGRATOR_ERROR;
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Get initialization flag of integrator
*
* @param[out]  	int_inst	- Pointer to integral instance
* @return       is_init		- Initialization success flag
*/
////////////////////////////////////////////////////////////////////////////////
bool integrator_simple_is_init(p_integrator_simple_t int_inst)
{
	bool is_init = false;

	if ( NULL != int_inst )
	{
		is_init = int_inst->is_init;
	}

	return is_init;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Update simple integrator
*
* @param[out]  	int_inst	- Pointer to integral instance
* @param[in]  	x			- Input signal
* @return       y			- Output (integrated) signal
*/
////////////////////////////////////////////////////////////////////////////////
float32_t integrator_simple_update(p_integrator_simple_t int_inst, const float32_t x)
{
	float32_t y = 0.0f;

	// Check for instance and initialization
	if ( NULL != int_inst )
	{
		if ( true == int_inst->is_init )
		{
			// Integrate
			y = int_inst->y + ( x * int_inst->dt );

			// Store value
			int_inst->y = y;
		}
	}

	return y;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Reset simple integrator to specified value
*
* @param[out]  	int_inst	- Pointer to integral instance
* @param[in]  	rst_value	- Value to reset integrator
* @return       status		- Either OK or ERROR
*/
////////////////////////////////////////////////////////////////////////////////
integrator_status_t	integrator_simple_reset(p_integrator_simple_t int_inst, const float32_t rst_value)
{
	integrator_status_t status = eINTEGRATOR_OK;

	// Check for instance and initialization
	if ( NULL != int_inst )
	{
		if ( true == int_inst->is_init )
		{
			int_inst->y=rst_value;
		}
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Initialize trapezoid integrator
*
* @param[out]  	p_int		- Pointer to integral instance
* @param[in]  	dt			- Update (period) time
* @param[in]  	init_value	- Initial value of integral
* @return       status		- Either OK or Error
*/
////////////////////////////////////////////////////////////////////////////////
integrator_status_t integrator_trapezoid_init(p_integrator_trapezoid_t * p_int, const float32_t dt, const float32_t init_value)
{
	integrator_status_t status = eINTEGRATOR_OK;

	if ( NULL != p_int )
	{
		// Allocate space
		*p_int = malloc( sizeof( integrator_trapezoid_t ));

		// Check for success allocation
		if ( NULL != *p_int )
		{
			// Store for later use
			(*p_int)->dt = dt;
			(*p_int)->y = init_value;
			(*p_int)->x_prev = 0.0f;

			// Init success
			(*p_int)->is_init = true;
		}
		else
		{
			status = eINTEGRATOR_ERROR;
		}
	}
	else
	{
		status = eINTEGRATOR_ERROR;
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Get initialization flag of integrator
*
* @param[out]  	int_inst	- Pointer to integral instance
* @return       is_init		- Initialization success flag
*/
////////////////////////////////////////////////////////////////////////////////
bool integrator_trapezoid_is_init(p_integrator_trapezoid_t int_inst)
{
	bool is_init = false;

	if ( NULL != int_inst )
	{
		is_init = int_inst->is_init;
	}

	return is_init;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Update simple integrator
*
* @param[out]  	int_inst	- Pointer to integral instance
* @param[in]  	x			- Input signal
* @return       y			- Output (integrated) signal
*/
////////////////////////////////////////////////////////////////////////////////
float32_t integrator_trapezoid_update(p_integrator_trapezoid_t int_inst, const float32_t x)
{
	float32_t y = 0.0f;

	// Check for instance and initialization
	if ( NULL != int_inst )
	{
		if ( true == int_inst->is_init )
		{
			// Integrate
			y = int_inst->y + (( x * int_inst->dt ) + (( x - int_inst->x_prev ) * ( int_inst->dt / 2.0f )));

			// Store value
			int_inst->y = y;
			int_inst->x_prev = x;
		}
	}

	return y;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    Reset trapezoid integrator to specified value
*
* @param[out]  	int_inst	- Pointer to integral instance
* @param[in]  	rst_value	- Value to reset integrator
* @return       status		- Either OK or ERROR
*/
////////////////////////////////////////////////////////////////////////////////
integrator_status_t	integrator_trapezoid_reset(p_integrator_trapezoid_t int_inst, const float32_t rst_value)
{
	integrator_status_t status = eINTEGRATOR_OK;

	// Check for instance and initialization
	if ( NULL != int_inst )
	{
		if ( true == int_inst->is_init )
		{
			int_inst->y=rst_value;
			int_inst->x_prev = 0;
		}
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
