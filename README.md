# Integrator
Integrator implementation in C for general DSP purposes. Two types of integrators are implemented, simple and trapezoid integration technique.

Both integrators has been evaluated in python and tested on STM32 platform. For more details
go look at this [repository](https://github.com/ZiGaMi/filters) under **simulations/integrator.py**.

Integrator memory space is dynamically allocated and success of allocation is taken into consideration before using that instance.

#### Dependencies
Definition of float32_t must be provided by user. In current implementation it is defined in "*project_config.h*". Just add following statement to your code where it suits the best.

```C
// Define float
typedef float float32_t;
```

 #### API

 ##### Simple integration API
 - integrator_status_t **integrator_simple_init**(p_integrator_simple_t * p_int, const float32_t dt, const float32_t init_value); 
 - bool	**integrator_simple_is_init**(p_integrator_simple_t int_inst);
 - float32_t **integrator_simple_update**(p_integrator_simple_t int_inst, const float32_t x);
 - integrator_status_t	**integrator_simple_reset**(p_integrator_simple_t int_inst, const float32_t rst_value);

##### Trapezoid integration API
 - integrator_status_t **integrator_trapezoid_init**(p_integrator_trapezoid_t * p_int, const float32_t dt, const float32_t init_value);
 - bool **integrator_trapezoid_is_init**(p_integrator_trapezoid_t int_inst);
 - float32_t **integrator_trapezoid_update**(p_integrator_trapezoid_t int_inst, const float32_t x);
 - integrator_status_t	**integrator_trapezoid_reset**(p_integrator_trapezoid_t int_inst, const float32_t rst_value);


##### Example of usage

```C

    // 1. Declare simple integral instance
    static p_integrator_simple_t g_integrator_simple = NULL;

    // 2. Init integrator
    if ( eINTEGRATOR_OK != integrator_simple_init( &g_integrator_simple, 0.010f, 0.0f ))
    {
        // Initialization failed...
        // Further action here...
    }

    // 3. Update - integrate wanted signal
    @period_time
    {
    integral_of_signal = integrator_simple_update( g_integrator_simple, signal );
    }

```
