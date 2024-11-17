/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application Car
 * Automatically generated by goil on Www Mmm dd hh:mm:ss yyyy
 * from root OIL file mycar.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include <stdbool.h>
#include <stdint.h>

#include "tpl_app_config.h"

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


#include "tpl_as_schedtable.h"
#include "tpl_as_st_kernel.h"
#include "tpl_as_action.h"
#include "tpl_as_isr_kernel.h"
#include "tpl_as_isr.h"
#include "tpl_as_counter.h"
#include "tpl_as_app_kernel.h"
#include "tpl_as_trusted_fct.h"
#include "tpl_as_trusted_fct_kernel.h"
#include "tpl_as_application.h"
/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * stdAppmode = 1
 */

CONST(tpl_application_mode, OS_CONST) stdAppmode = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  1 /* task Accelerate : stdAppmode */ ,
  1 /* task Steer : stdAppmode */ ,
  1 /* task Brake : stdAppmode */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task Accelerate identifier */
#define Accelerate_id 0
CONST(TaskType, AUTOMATIC) Accelerate = Accelerate_id;

/* Task Steer identifier */
#define Steer_id 1
CONST(TaskType, AUTOMATIC) Steer = Steer_id;

/* Task Brake identifier */
#define Brake_id 2
CONST(TaskType, AUTOMATIC) Brake = Brake_id;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * The scheduler resource descriptor.
 * One scheduler resource is defined per core.
 *
 * @see #RES_SCHEDULER
 */

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
VAR(tpl_resource, OS_VAR) res_sched_rez_desc = {
  RES_SCHEDULER_PRIORITY,   /*  ceiling priority                            */
  0,                        /*  owner_prev_priority                         */
  INVALID_PROC_ID,          /*  owner                                       */
#if WITH_OSAPPLICATION == YES
  INVALID_OSAPPLICATION_ID, /*  OS Application id                           */
#endif

  NULL                      /*  next_res                                    */
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
FUNC(tpl_bool, OS_CODE) tpl_call_counter_tick(void)
{

  if (tpl_kern.need_schedule)
  {
    tpl_schedule_from_running();
    LOCAL_SWITCH_CONTEXT(0)
  }

  return TRUE;
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*=============================================================================
 * Descriptor(s) of the idle task(s)
 */
/*-----------------------------------------------------------------------------
 * Task IDLE_TASK descriptor
 */
#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task IDLE_TASK function prototype
 */

FUNC(void, OS_APPL_CODE) idle_function(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task IDLE_TASK stack
 */
#define APP_Task_IDLE_TASK_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word IDLE_TASK_stack_zone[IDLE_STACK_SIZE/sizeof(tpl_stack_word)];
#define APP_Task_IDLE_TASK_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK IDLE_TASK_stack = {IDLE_TASK_stack_zone, IDLE_STACK_SIZE};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_STACK &IDLE_TASK_stack

/*
 * Task IDLE_TASK context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT IDLE_TASK_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_CONTEXT &IDLE_TASK_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task IDLE_TASK
 */
CONST(tpl_proc_static, OS_CONST) IDLE_TASK_task_stat_desc = {
  /* context                  */  IDLE_TASK_CONTEXT,
  /* stack                    */  IDLE_TASK_STACK,
  /* entry point (function)   */  idle_function,
  /* internal ressource       */  NULL,
  /* task id                  */  IDLE_TASK_ID,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  0,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task IDLE_TASK
 */
VAR(tpl_proc, OS_VAR) IDLE_TASK_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  ,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  0,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task Accelerate descriptor
 */
#define APP_Task_Accelerate_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Accelerate function prototype
 */

FUNC(void, OS_APPL_CODE) Accelerate_function(void);
#define APP_Task_Accelerate_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Accelerate stack
 */
#define APP_Task_Accelerate_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word Accelerate_stack_zone[32768/sizeof(tpl_stack_word)];
#define APP_Task_Accelerate_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK Accelerate_stack = {Accelerate_stack_zone, 32768};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define Accelerate_STACK &Accelerate_stack

/*
 * Task Accelerate context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT Accelerate_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define Accelerate_CONTEXT &Accelerate_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Accelerate
 */
CONST(tpl_proc_static, OS_CONST) Accelerate_task_stat_desc = {
  /* context                  */  Accelerate_CONTEXT,
  /* stack                    */  Accelerate_STACK,
  /* entry point (function)   */  Accelerate_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Accelerate_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Accelerate
 */
VAR(tpl_proc, OS_VAR) Accelerate_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  ,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task Steer descriptor
 */
#define APP_Task_Steer_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Steer function prototype
 */

FUNC(void, OS_APPL_CODE) Steer_function(void);
#define APP_Task_Steer_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Steer stack
 */
#define APP_Task_Steer_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word Steer_stack_zone[32768/sizeof(tpl_stack_word)];
#define APP_Task_Steer_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK Steer_stack = {Steer_stack_zone, 32768};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define Steer_STACK &Steer_stack

/*
 * Task Steer context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT Steer_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define Steer_CONTEXT &Steer_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Steer
 */
CONST(tpl_proc_static, OS_CONST) Steer_task_stat_desc = {
  /* context                  */  Steer_CONTEXT,
  /* stack                    */  Steer_STACK,
  /* entry point (function)   */  Steer_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Steer_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Steer
 */
VAR(tpl_proc, OS_VAR) Steer_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  ,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task Brake descriptor
 */
#define APP_Task_Brake_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task Brake function prototype
 */

FUNC(void, OS_APPL_CODE) Brake_function(void);
#define APP_Task_Brake_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task Brake stack
 */
#define APP_Task_Brake_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word Brake_stack_zone[32768/sizeof(tpl_stack_word)];
#define APP_Task_Brake_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_STACK Brake_stack = {Brake_stack_zone, 32768};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define Brake_STACK &Brake_stack

/*
 * Task Brake context
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
struct TPL_CONTEXT Brake_context;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define Brake_CONTEXT &Brake_context





/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task Brake
 */
CONST(tpl_proc_static, OS_CONST) Brake_task_stat_desc = {
  /* context                  */  Brake_CONTEXT,
  /* stack                    */  Brake_STACK,
  /* entry point (function)   */  Brake_function,
  /* internal ressource       */  NULL,
  /* task id                  */  Brake_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task Brake
 */
VAR(tpl_proc, OS_VAR) Brake_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  ,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  3,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Accelerate_task_stat_desc,
  &Steer_task_stat_desc,
  &Brake_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &Accelerate_task_desc,
  &Steer_task_desc,
  &Brake_task_desc,
  &IDLE_TASK_task_desc
};



#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */

/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[5];
VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[5] = {
  0,
  0,
  0,
  0
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  NULL,                      /* no running task static descriptor   */
  &IDLE_TASK_task_stat_desc, /* elected task to run is idle task    */
  NULL,                      /* no running task dynamic descriptor  */
  &IDLE_TASK_task_desc,      /* elected task to run is idle task    */
  INVALID_PROC_ID,           /* no running task so no ID            */
  INVALID_PROC_ID,           /* idle task has no ID                 */
  NO_NEED_SWITCH,            /* no context switch needed at start   */
  FALSE,                     /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  1,                         /* at early system startup, we run in  */
                             /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1] = {

  "Accelerate",
  "Steer",
  "Brake",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */