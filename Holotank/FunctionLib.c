#pragma config(Sensor, dgtl1,  FrontPistons,   sensorDigitalOut) // pragmas for my commands.
#pragma config(Sensor, dgtl2,  BackPistons,    sensorDigitalOut) // If you're using this, change your #pragma's here.
/*                                                                          */
/*                          Function Library                                */
/*                                                                          */
/*      Message Last Edited - 5/24/2017  5:36PM CST                         */
/*                                                                          */
/*      Hey There! Thanks for reading this little notifier.                 */
/*        Here's the jist of what this is:                                  */
/*        Since we used "#pragma systemFile" below this, we've              */
/*      eliminated the error for unused functions. Because of this,         */
/*      (though unnessecary) it's a good idea to place our functions        */
/*      elsewhere for organization's sake.                                  */
/*        So, as the author, I've taken the liberty of choosing where       */
/*      to place the functions, and I've chosen to place them in this       */
/*      file for now ~                                                      */
/*                                    Cheers, Dylan                         */
/*                                                                          */
/*                                                                          */
/*                              Changelog                                   */
/*                                                                          */
/*                                                                          */
/*      5/24/2017  - Created Unreferenced Function Library                  */
/*      5/24/2017  - Changed to Function Library and moved some things      */
/*                   to this file from Holotank.c                           */
/*                                                                          */
/*                                                                          */
/*                           Table of Contents                              */
/*                                                                          */
/*      Section 1 - Cool things stolen from RobotC's Includes folder        */
/*      Section 2 - Things I've (the Author) written                        */
/*      Section 3 - Things You (the User) have written                      */
/*                                                                          */
/*                                                                          */


/*                             Library Start                                */
#pragma systemFile      // this is supposed to eliminate the warning for "unreferenced" functions

/*      Section 1 - Cool things stolen from RobotC's Includes folder        */


        // SOURCE: NatLang_CORTEX.c
// bIfiRobotDisabled - Variable that returns true if robot is disabled.
// compPreviousMode - Variable that checks the previous mode the robot was in. should be set to "compCurrentMode" before changing "compCurrentMode".
// compCurrentMode - Variable that checks the current mode the robot is in. Can be set to "compAuto" or "compTeleOp".
// displayLCDCenteredString("X", "X") - Command that displays LCD text.


#include "Variables.h" // Includes the variables used within these functions
#include "Definitions.h" // Includes the definitions used within these functions
#include "SmartMotorLib.c" // Includes jpearman's Smart Motor Library commands

/*      Section 2 - Things I've (the Author) written                         */

void DragonWheels(bool Speed)
{
  if (vexRT[Btn6U])
  {
    Swerve = true;
  }
  else
  {
    Swerve = false;
  }
  if(Speed == true)
  {
    if (DriveType == 2 && Swerve == true)
    {
      setMotor ( BL, vexRT[Ch1] );
      setMotor ( BR, vexRT[Ch1] );
    }
    else if (DriveType == 3 && Swerve == true)
    {
      setMotor ( FL, vexRT[Ch1] );
      setMotor ( FR, vexRT[Ch1] );
    }
  }
  else // Speed == false
  {
    if (DriveType == 2 && Swerve == true)
    {
      setMotor ( BL, (vexRT[Ch1]/7) );
      setMotor ( BR, (vexRT[Ch1]/7) );
    }
    else if (DriveType == 3 && Swerve == true)
    {
      setMotor ( FL, (vexRT[Ch1]/7) );
      setMotor ( FR, (vexRT[Ch1]/7) );
    }
  }
}

void DragonDrive() // NOTE THAT THIS IS W.I.P.
// start of function
{ // {1
                       // Checks for Dragon Drive type
  if(DriveType == 2) // Normal Dragon Drive
  { // {2
                                 // Checks for Tank vs. Arcade
    if(NonHolonomicSwitch == 0) // Tank Drive
    { // {3
                             // Checks for Speed Modifier
      if(TankSpeed == true) // Speed is set to Fast
      { // {4
                             // Checks for Swerve Button
        if (Swerve == true) // Swerve Button is Pressed
        { // {5
          DragonWheels(true);
          SetMotor (BR,  vexRT[Ch2]);
          SetMotor (BL, -vexRT[Ch3]);
        } // 5}
        else                 // Swerve Button is not Pressed
        { // {5
          SetMotor (FL, -vexRT[Ch3]);
          SetMotor (FR,  vexRT[Ch2]);
          SetMotor (BR,  vexRT[Ch2]);
          SetMotor (BL, -vexRT[Ch3]);
        } // 5}
      } // 4}
      else                   // Speed is set to Slow
      { // {4
                            // Checks for Swerve Button
        if(Swerve == true) // Swerve Button is Pressed
        { // {5
        DragonWheels(false);
        SetMotor (BR, (vexRT[Ch2]/7));
        SetMotor (BL, -(vexRT[Ch3]/7));
        } // 5}
        else                 // Swerve Button is not Pressed
        { // {5
        SetMotor (FL, -(vexRT[Ch3]/7));
        SetMotor (FR, (vexRT[Ch2]/7));
        SetMotor (BR, (vexRT[Ch2]/7));
        SetMotor (BL, -(vexRT[Ch3]/7));
        } // 5}
      } // 4}
    } // 3}
    else // Arcade Drive
    { // {3
                // lolnope
    } // 3}
  } // 2}
  else if (DriveType == 3) // Reverse Dragon Drive
  // Could be shortened to "else", but my OCD needs to guarantee we're actually in Reverse Dragon
  { // {2
                // much code
                // very gud
  } // 2}
} // 1}
// end of function

void TankDrive()
{
  if(TankSpeed == true)
  {
  SetMotor (FL, -vexRT[Ch3]);
  SetMotor (FR, vexRT[Ch2]);
  SetMotor (BR, vexRT[Ch2]);
  SetMotor (BL, -vexRT[Ch3]);
  }
  else
  {
  SetMotor (FL, -(vexRT[Ch3]/7));
  SetMotor (FR, (vexRT[Ch2]/7));
  SetMotor (BR, (vexRT[Ch2]/7));
  SetMotor (BL, -(vexRT[Ch3]/7));
  }
}

void ArcadeDrive(int slowthreshold, int fastthreshold)
{
  if(vexRT[Ch1] < slowthreshold && vexRT[Ch1] > -slowthreshold && vexRT[Ch2] < slowthreshold && vexRT[Ch2] > -slowthreshold || vexRT[Ch4] > fastthreshold || vexRT[Ch4] < -fastthreshold || vexRT[Ch3] > fastthreshold || vexRT[Ch3] < -fastthreshold)
  {
  SetMotor (FL, -((vexRT[Ch3]*2) + (vexRT[Ch4]*2))/2);
  SetMotor (FR, ((vexRT[Ch3]*2) - (vexRT[Ch4]*2))/2);
  SetMotor (BR, ((vexRT[Ch3]*2) - (vexRT[Ch4]*2))/2);
  SetMotor (BL, -((vexRT[Ch3]*2) + (vexRT[Ch4]*2))/2);
  }
  else
  {
  SetMotor (FL, -((vexRT[Ch2]*2) + (vexRT[Ch1]*2))/7);
  SetMotor (FR, ((vexRT[Ch2]*2) - (vexRT[Ch1]*2))/7);
  SetMotor (BR, ((vexRT[Ch2]*2) - (vexRT[Ch1]*2))/7);
  SetMotor (BL, -((vexRT[Ch2]*2) + (vexRT[Ch1]*2))/7);
  }
}

void ArcadeTankSwitch()
{
  if (vexRT[Btn5U])
    NonHolonomicSwitch = true;
  else if (vexRT[Btn5D])
    NonHolonomicSwitch = false;

  if (NonHolonomicSwitch == 0) // If False, Tank
    TankDrive();
  else
    ArcadeDrive(GlobalSmallThresh, GlobalLargeThresh); // If True, Arcade
}
void DriveShift()
{
  if (DriveType == 0) // Tank
  {
    SensorValue(FrontPistons) = 1;
    SensorValue(BackPistons) = 0;
    ArcadeTankSwitch();
  }
  else if (DriveType == 1) // X-Drive
  {
    SensorValue(FrontPistons) = 0;
    SensorValue(BackPistons) = 1;
    // Y component, X component, Rotation
    setMotor ( FL, -C1LY - C1LX - C1RX );
    setMotor ( FR,  C1LY - C1LX - C1RX );
    setMotor ( BR,  C1LY + C1LX - C1RX );
    setMotor ( BL, -C1LY + C1LX - C1RX );
  }
  else if (DriveType == 2) // Dragon
  {
    SensorValue(FrontPistons) = 1;
    SensorValue(BackPistons) = 1;
    ArcadeTankSwitch();
  }
  else // Reverse Dragon
  {
    SensorValue(FrontPistons) = 0;
    SensorValue(BackPistons) = 0;
    ArcadeTankSwitch();
  }
}

void DriveButtons()
{
    if(vexRT[Btn8U])
    {
      TankSpeed = true;
      DriveType = 0;
    }
    else if(vexRT[Btn8L])
      DriveType = 2;
    else if(vexRT[Btn8R])
      DriveType = 3;
    else if (vexRT[Btn8D])
      DriveType = 1;
}

void TankSpeedShift()
{
	if(vexRT[Btn6D])
    TankSpeed = false;
  else
    TankSpeed = true;
}

/*      Section 3 - Things You (the User) have written                       */




/*                             Library End                                   */
