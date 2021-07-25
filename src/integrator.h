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
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup INTEGRATOR_API
* @{ <!-- BEGIN GROUP -->
*
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __INTEGRATOR_H
#define __INTEGRATOR_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "project_config.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 * 	Status
 */
typedef enum
{
	eINTEGRATOR_OK = 0,		/**<Normal operation */
	eINTEGRATOR_ERROR,		/**<General error */
} integrator_status_t;

/**
 * 	Pointer to integrator instance
 */
typedef struct integrator_simple_s 		* p_integrator_simple_t;
typedef struct integrator_trapezoid_s 	* p_integrator_trapezoid_t;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////
integrator_status_t integrator_simple_init			(p_integrator_simple_t * p_int, const float32_t dt, const float32_t init_value);
bool				integrator_simple_is_init		(p_integrator_simple_t int_inst);
float32_t			integrator_simple_update		(p_integrator_simple_t int_inst, const float32_t x);
integrator_status_t	integrator_simple_reset			(p_integrator_simple_t int_inst, const float32_t rst_value);

integrator_status_t integrator_trapezoid_init		(p_integrator_trapezoid_t * p_int, const float32_t dt, const float32_t init_value);
bool				integrator_trapezoid_is_init	(p_integrator_trapezoid_t int_inst);
float32_t			integrator_trapezoid_update		(p_integrator_trapezoid_t int_inst, const float32_t x);
integrator_status_t	integrator_trapezoid_reset		(p_integrator_trapezoid_t int_inst, const float32_t rst_value);

#endif // __INTEGRATOR_H

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
