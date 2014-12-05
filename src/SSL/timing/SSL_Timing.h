/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Timing.h
   @author  P. Batty
   @brief   Timing loop for the library

   This module implements timing features for the library

*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_TIMING_H_
#define SSL_TIMING_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Starts the timer package
  @return 1 on success else 0

  Starts the timer package, required before you can use and timing functions

\-----------------------------------------------------------------------------*/
int SSL_Timer_Init();


/*!--------------------------------------------------------------------------
  @brief    Gets the current time in seconds since the SSL timing library was initialised
  @return seconds since the SSL timing library was initialised

  Gets the time in seconds since the SSL timing library was initialised

\-----------------------------------------------------------------------------*/
int SSL_Get_Uptime();


/*!--------------------------------------------------------------------------
  @brief    Gets the current delta time / time since last update
  @return current delta time

  Gets the current delta time / time since last update

\-----------------------------------------------------------------------------*/
double SSL_Get_Delta();


/*!--------------------------------------------------------------------------
  @brief    Gets the current frames per second of the program
  @return current frames per second

  Gets the current frames per second of the program, updates every second

\-----------------------------------------------------------------------------*/
double SSL_Get_Fps();


/*!--------------------------------------------------------------------------
  @brief    Gets the current ticks per second of the program
  @return current ticks per second

  Gets the current ticks per second of the program, updates every second

\-----------------------------------------------------------------------------*/
double SSL_Get_Ticks();


/*!--------------------------------------------------------------------------
  @brief    Gets weather we should perform and update
  @return 1 if we should update the logic else 0

  Gets weather we should perform and update

\-----------------------------------------------------------------------------*/
int SSL_Get_CanTick();


/*!--------------------------------------------------------------------------
  @brief    Stops the timer package
  @return void

  Stops the timer package.

\-----------------------------------------------------------------------------*/
void SSL_Timer_Stop();


#endif
