#pragma config(Sensor, dgtl1,  FrontPistons,   sensorDigitalOut) // pragmas for my commands.
#pragma config(Sensor, dgtl2,  BackPistons,    sensorDigitalOut) // If you're using this, change your #pragma's here.
/*                                                                          */
/*                              Holotank.c                                  */
/*                                                                          */
/*                                                                          */
/*        Heya! Thanks for stopping by. This is  Dylan from team 7862       */
/*      here. This file (Holotank.c) was for an expiremental drivetrain     */
/*      that, through use of pneumatics, could switch between four          */
/*      different drive styles:                                             */
/*          - Tank/Arcade                                                   */
/*          - X-Drive                                                       */
/*          - Dragon Drive                                                  */
/*          - Reverse Dragon Drive                                          */
/*        Essentially, the conclusion I came to was that the drive was      */
/*      not viable for late-season competition use, but for early           */
/*      season it was useful for deciding which drive type would work       */
/*      best in the long-term. Since I'm writing this in early In The       */
/*      Zone, I have no clue which will be better, but I suppose we'll      */
/*      all see together ~                                                  */
/*        However, since I'm not going to be using this late-season, I      */
/*      Figured I'd release it to the public. I'm going to continue         */
/*      supporting this (until I don't) but for the time being it's a       */
/*      place where I can practice coding and try out things I haven't      */
/*      used before. So be warned, this is probably nowhere close to        */
/*      the best formatted code, but it should at least work.               */
/*        Also, one last thing- if a function says "W.I.P." by the name,    */
/*      take a hint. Said function is being worked on and therefore         */
/*      experimental, and should not be used unless you're OK with          */
/*      possible destruction of parts. I've nothing left to say, so go!     */
/*      fight! WIN!                                                         */
/*                                                                          */
/*                        Good Luck in VRC In The Zone, Dylan               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*        ps. I know you're supposed to do a bunch of liscensing            */
/*            and stuff when releasing public code, but how about           */
/*            nah we're all chill and share stuff like friends :D           */


#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "FunctionLib.c"

void pre_auton()
{
  bStopTasksBetweenModes = false;

   // Initialize smart motor library
  SmartMotorsInit();

    // run background tasks
  SmartMotorRun();

}

task autonomous()
{
  AutonomousCodePlaceholderForTesting();
}

task usercontrol()
{
  while (true)
  {
    DriveShift();
    TankSpeedShift();
  }
}
