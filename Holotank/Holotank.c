#pragma config(Sensor, dgtl1,  FrontPistons,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  BackPistons,    sensorDigitalOut)
//*	ROBOTC, WHY ARE YOU DUMB AND REQUIRE THIS TO BE AT THE TOP *//
//* IT MAKES MY FORMATTING LOOK BAD	*//
// also trust me this looks nice in RobotC's interface, I'll fix it later

/*																																					*/
/*															Holotank.c																	*/
/*																																					*/
/*																																					*/
/*				Heya! Thanks for stopping by. This is	Dylan from team 7862				*/
/*			here. This file (Holotank.c) was for an expiremental drivetrain			*/
/*			that, through use of pneumatics, could switch between four					*/
/*			different drive styles:																							*/
/*					- Tank/Arcade																										*/
/*					- X-Drive																												*/
/*					- Dragon Drive																									*/
/*					- Reverse Dragon Drive																					*/
/*				Essentially, the conclusion I came to was that the drive was			*/
/*			not viable for late-season competition use, but for early						*/
/*			season it was useful for deciding which drive type would work 			*/
/*			best in the long-term. Since I'm writing this in early In The				*/
/*			Zone, I have no clue which will be better, but I suppose we'll			*/
/*			all see together ~																									*/
/*				However, since I'm not going to be using this late-season, I			*/
/*			Figured I'd release it to the public. I'm going to continue 				*/
/*			supporting this (until I don't) but for the time being it's a 			*/
/*			place where I can practice coding and try out things I haven't 			*/
/*			used before. So be warned, this is probably nowhere close to				*/
/*			the best formatted code, but it should at least work.								*/
/*				Also, one last thing- if a function says "W.I.P." by the name,		*/
/*			take a hint. Said function is being worked on and therefore					*/
/*			experimental, and should not be used unless you're OK with					*/
/*			possible destruction of parts. I've nothing left to say, so go!			*/
/*			fight! WIN!																													*/
/*																																					*/
/*												Good Luck in VRC In The Zone, Dylan								*/
/*																																					*/
/*																																					*/
/*																																					*/
/*				ps. I know you're supposed to do a bunch of liscensing						*/
/*						and stuff when releasing public code, but how about						*/
/*						nah we're all chill and share stuff like friends :D						*/

#pragma systemFile      // this eliminates the warning for "unreferenced" functions (even though it's not a System File)

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "SmartMotorLib.c" // Includes jpearman's Smart Motor Library commands

#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]
#define C1RX vexRT[Ch1]

#define FL port2
#define FR port3
#define BL port4
#define BR port5

int DriveType = 0; // 0 = Tank/Arcade, 1 = X-Drive, 2 = Dragon, 3 = Reverse Dragon
bool NonHolonomicSwitch = false; // 0 = Tank, 1 = Arcade
int GlobalSmallThresh = 10;
int GlobalLargeThresh = 85;
bool TankSpeed = true; // True = High Speed, False = Low Speed
bool Swerve = false; // True = Dragon Wheel Swerve w/ Ch1, False = Normal Drive

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
				else 								// Swerve Button is not Pressed
				{ // {5
					SetMotor (FL, -vexRT[Ch3]);
					SetMotor (FR,  vexRT[Ch2]);
					SetMotor (BR,  vexRT[Ch2]);
					SetMotor (BL, -vexRT[Ch3]);
				} // 5}
			} // 4}
			else 									// Speed is set to Slow
			{ // {4
														// Checks for Swerve Button
				if(Swerve == true) // Swerve Button is Pressed
				{ // {5
				DragonWheels(false);
				SetMotor (BR, (vexRT[Ch2]/7));
				SetMotor (BL, -(vexRT[Ch3]/7));
				} // 5}
				else 						 	 // Swerve Button is not Pressed
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
		DragonDrive();
	}
	else // Reverse Dragon
	{
		SensorValue(FrontPistons) = 0;
		SensorValue(BackPistons) = 0;
		DragonDrive();
	}
}


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

		if(vexRT[Btn6D])
			TankSpeed = false;
		else
			TankSpeed = true;

		DriveShift();
	}
}

/*																																					*/
/*			Unreferenced Funciton Library																				*/
/*																																					*/
/*			Message Last Edited - 5/24/2017	9:46AM CST													*/
/*																																					*/
/*			Hey There! Thanks for reading this little notifier.									*/
/* 				Here's the jist of what this is:																	*/
/*				Since we used "#pragma systemFile" at the top of this file, 			*/
/*			we eliminated the error for unused functions.	Because of this, 			*/
/*			(though unnessecary) it's a good idea to place our unreferenced 		*/
/*			functions elsewhere for organization's sake. 												*/
/*				So, as the author, I've taken the liberty of choosing where 			*/
/*			to place those functions, and I've chosen to place them at the			*/
/*			bottom of this file for now ~																				*/
/*																		Cheers, Dylan													*/
/*																																					*/
/*																																					*/
/*															Changelog																		*/
/*																																					*/
/*																																					*/
/*			5/24/2017	- Created Unreferenced Function Library										*/
/*																																					*/
/*																																					*/
/*													 Table of Contents															*/
/*																																					*/
/*			Section 1 - Cool things stolen from RobotC's Includes folder				*/
/*			Section 2 - Things I've (the Author) written												*/
/*			Section 3 - Things You (the User) have written											*/
/*																																					*/
/*																																					*/

/* 														Library Start

				Section 1 - Cool things stolen from RobotC's Includes folder


				SOURCE: NatLang_CORTEX.c
task monitorCompetitionFlags()
{
	while(true)
	{
		if(bIfiRobotDisabled) //We're disabled, we should restart "task main" and disable Auto/Tele Flags
		{
			if(compCurrentMode != compDisable)
			{
				compPreviousMode = compCurrentMode;
				compCurrentMode = compDisable;
				bAutonomousOneTimeFlag = false;
				toggleMainTask();
				displayLCDCenteredString(0, "Disabled");
			}
		}
		else //We're enabled, let's check the Autonomous Flag.
		{
			if(bIfiAutonomousMode) //Autonomous Mode, let's set the auto flag.
			{
				if(compCurrentMode != compAuto)
				{
					compPreviousMode = compCurrentMode;
					compCurrentMode = compAuto;
					toggleMainTask();
					displayLCDCenteredString(0, "Autonomous");
				}
			}
			else //TeleOp Mode, let's set the tele flag.
			{
				if(compCurrentMode != compTeleOp)
				{
					compPreviousMode = compCurrentMode;
					compCurrentMode = compTeleOp;
					toggleMainTask();
					displayLCDCenteredString(0, "TeleOp");
				}
			}
		}
		sleep(25);
	}
}

				Section 2 - Things I've (the Author) written




				Section 3 - Things You (the User) have written




															 Library End 																	*/
