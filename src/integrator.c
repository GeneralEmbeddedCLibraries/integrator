////////////////////////////////////////////////////////////////////////////////
/**
*@file      integrator.c
*@brief     Integrator for general purpose usage
*@author    Ziga Miklosic
*@date      27.02.2021
*@version   V1.0.0
*
*@section Description
*
*
*@section Code_example
*@code
*
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
/*!
* @brief    Calculate slew rate factor base on update time.
*
* @param[in]  	dt			- Update (period) time
* @param[in]	slew_rate	- Wanted slew rate
* @return       k_rate		- Slew rate factor
*/
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
* @brief    Initialize rate limiter
*
* @note Rising/Falling slew rate is references to change on seconds.
*
* 		E.g.:
* 			- for 1V/s -> put rise/fall rate = 1.0
* 			- for 0.5V/s -> put rise/fall rate = 0.5
*
* @param[out]  	p_rl_inst	- Pointer to rate limiter instance
* @param[in]  	rise_rate	- Rising slew rate
* @param[in]  	fall_rate	- Falling slew rate
* @param[in]  	dt			- Update (period) time
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


bool integrator_simple_is_init(p_integrator_simple_t int_inst)
{
	bool is_init = false;

	if ( NULL != int_inst )
	{
		is_init = int_inst->is_init;
	}

	return is_init;
}


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


bool integrator_trapezoid_is_init(p_integrator_trapezoid_t int_inst)
{
	bool is_init = false;

	if ( NULL != int_inst )
	{
		is_init = int_inst->is_init;
	}

	return is_init;
}


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
