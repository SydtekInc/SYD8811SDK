/********************************************************************************
	* @file     calender.h
	* @author   Mingming Liu
	* @version  V1.0.0
	* @date     12-08-2016
	* @Emial   ming.liu@syd-tek.com
	* @brief    head file for calender.c
	******************************************************************************/

#ifndef _CALENDER_H
#define _CALENDER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
	
/*********************************************************************
 * MACROS
 */
#define BUILD_UINT16(loByte, hiByte) \
          ((uint16_t)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))
	
#define	IsLeapYear(yr)	(!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))

/*********************************************************************
 * TYPEDEFS
 */

// number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 2000 UTC
typedef uint32_t UTCTime;

// To be used with
typedef struct
{
  uint8_t seconds;  // 0-59
  uint8_t minutes;  // 0-59
  uint8_t hour;     // 0-23
  uint8_t day;      // 0-30
  uint8_t month;    // 0-11
  uint16_t year;    // 2000+
} UTCTimeStruct;

// To be used with
typedef struct
{
	uint8_t  RSVD0;
	uint8_t  RSVD1;
	uint8_t  year_low;   //	*(pData+2)
	uint8_t  month;      //	*(pData+3)
	uint8_t  day;        //	*(pData+4)
	uint8_t  hour;       //	*(pData+5)
	uint8_t  minutes;    //	*(pData+6)
	uint8_t  seconds;    //	*(pData+7)
	uint8_t  week;		 //	*(pData+8)
} Time_clock_Struct;

/*********************************************************************
 * FUNCTIONS
 */

  /*
   * Updates the clock and Timers from the MAC 320us timer tick.
   */
  extern void TimeUpdate( void );

  /*
   * Set the new time.  This will only set the seconds portion
   * of time and doesn't change the factional second counter.
   *     newTime - number of seconds since 0 hrs, 0 minutes,
   *               0 seconds, on the 1st of January 2000 UTC
   */
  extern void Set_Clock( UTCTime newTime );

  /*
   * Gets the current time.  This will only return the seconds
   * portion of time and doesn't include the factional second counter.
   *     returns: number of seconds since 0 hrs, 0 minutes,
   *              0 seconds, on the 1st of January 2000 UTC
   */
  extern UTCTime Get_Clock( void );

  /*
   * Converts UTCTime to UTCTimeStruct
   *
   * secTime - number of seconds since 0 hrs, 0 minutes,
   *          0 seconds, on the 1st of January 2000 UTC
   * tm - pointer to breakdown struct
   */
  extern void ConvertUTCTime( UTCTimeStruct *tm, UTCTime secTime );

  /*
   * Converts UTCTimeStruct to UTCTime (seconds since 00:00:00 01/01/2000)
   *
   * tm - pointer to UTC time struct
   */
  extern UTCTime ConvertUTCSecs( UTCTimeStruct *tm );

  /*
   * Update/Adjust the clock and timers
   * Msec - elapsed time in milli seconds 
   */
  extern void AdjustTimer( uint32_t Msec );
	
	extern uint8_t * timeAppClockGet( uint8_t *pData );
	
	extern void timeAppClockSet( uint8_t *pData );
	
	extern void timer_calender_handle(void);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif
#endif

