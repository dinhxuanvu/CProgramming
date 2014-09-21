/**************************************************************************
* Timers Instrumentation Macros Module
*
* The timing instrumentation macros can be globally enabled by setting
* the variable EN_TIME (ENable TIMErs) in the compiler command line, e.g.,
* use "gcc -DEN_TIME...." to enable the timers when needed.
* A compiler warning will be issued when the timers are enabled.
* All timer output should be directed to stderr.
**************************************************************************/
#ifndef _TIMERS_H_
#define _TIMERS_H_

#if defined(EN_TIME)
    #include <stdio.h>
    #include <time.h>
    #if defined(WARNING_MSG)
        #warning Timers enabled! Execution could be adversly effected.
    #endif
#endif

#if defined(EN_TIME)

/****************************************************************************
 * Declare the timer. Initialize the timer (particularly the accumulated
 * elapsed time and the timer state).
 ****************************************************************************/
#define DECLARE_TIMER(A)					       	    \
struct {								    \
    /* Start Time - set when the timer is started */                        \
    clock_t Start;                                                          \
    /* Stop Time - set when the timer is stopped */                         \
    clock_t Stop;                                                           \
    /* Elapsed Time - Accumulated when the timer is stopped */              \
    clock_t Elapsed;                                                        \
    /* Timer State - Set automatically: 0=stopped / 1=running */            \
    int State;                                                              \
} A = { /* Elapsed Time and State must be initialized to zero */            \
    /* Start	= */ 0,                                                     \
    /* Stop	= */ 0,                                                     \
    /* Elapsed = */ 0,                                                      \
    /* State	= */ 0,                                                     \
}; /* Timer has been declared and defined */

/****************************************************************************
 * Start the timer.	Print an error if it is already running, set the state
 * to running and then start the timer.
 *****************************************************************************/
#define START_TIMER(A) 							    \
{		       							    \
    /* It is an error if the timer is currently running */                  \
    if (1 == A.State)                                                       \
        fprintf(stderr, "Error, running timer "#A" started.\n");            \
    /* Set the state to running */                                          \
    A.State = 1;                                                            \
    /* Set the start time, done last to maximize accuracy */                \
    A.Start = clock();                                                      \
} /* START_TIMER() */

/****************************************************************************
 * Reset the timer. Clear the elapsed time.
 ****************************************************************************/
#define RESET_TIMER(A)						      	    \
{					      				    \
    /* Reset the elapsed time to zero */                                    \
    A.Elapsed = 0;                                                          \
} /* RESET_TIMER() */

/****************************************************************************
 * Stop the timer. Set the stop time, print an error message if the timer
 * is already stopped otherwise accumulate the elapsed time (works for
 * both one-time and repeating timing operations), set the state to stopped.
 ***************************************************************************/
#define STOP_TIMER(A)	                             			    \
{		   						            \
    /* Set the stop time, done first to maximize accuracy */                \
    A.Stop = clock();                                                       \
    /* It is an error if the timer is currently stopped */                  \
    if (0 == A.State)                                                       \
        fprintf(stderr, "Error, stopped timer "#A" stopped again.\n");      \
    else /* accumulate running total only if previously running */          \
        A.Elapsed += A.Stop - A.Start;                                      \
    /* Set the state to stopped */                                          \
    A.State = 0;                                                            \
} /* STOP_TIMER() */

/****************************************************************************
 * Print the timer.	Check the timer state and stop it if necessary, print 115
 * the elapsed time (in seconds).
 *****************************************************************************/
#define PRINT_TIMER(A)						            \
{				      					    \
    /* Stop the timer (silently) if it is currently running */	            \
    if (1 == A.State)							    \
        STOP_TIMER(A); /* no error possible in this case */	            \
    fprintf(stderr, "Elapsed CPU Time ("#A") = %g sec.\n", 	            \
    (double)A.Elapsed / (double)CLOCKS_PER_SEC);		       	    \
} /*PRINT_TIMER() */

#else /* not defined(EN_TIME) */

    /* Declare null macros for error-free compilation */
    #define DECLARE_TIMER(A) /* Null Macro */
    #define START_TIMER(A) /* Null Macro */
    #define RESET_TIMER(A) /* Null Macro */
    #define STOP_TIMER(A)  /* Null Macro */
    #define PRINT_TIMER(A) /* Null Macro */

#endif /* defined(EN_TIME) */

#endif /* _TIMERS_H_ */

