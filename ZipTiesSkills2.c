#pragma config(UserModel, "C:/Users/rstudent/code/39z-in_the_zone/39ZSkillsbotConfig.c")
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include <CKTankDrive.h>
#include <LCDBattery.h>

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void fwd(int t, int speed)// forward with time
{
	motor[LeftFront]=speed;
	motor[LeftRear]=speed;
	motor[LeftMid]=speed;
	motor[RightFront]=speed;
	motor[RightMid]=speed;
	motor[RightRear]=speed;
	wait1Msec(t);// t is  msec
	motor[LeftFront]=-0;
	motor[LeftMid]=0;
	motor[LeftRear]=-0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}

void fwdR(int t, int speed)// forward with encoder
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	motor[LeftFront]=speed;
	motor[LeftRear]=speed;
	motor[LeftMid]=speed;
	motor[RightFront]=speed;
	motor[RightMid]=speed;
	motor[RightRear]=speed;
	while(SensorValue[rightEncoder]<t)
	{
	}
	motor[LeftFront]=-0;
	motor[LeftMid]=0;
	motor[LeftRear]=-0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}

void bwd(int t, int speed)//backward with speed
{
	motor[LeftFront]=-speed;
	motor[LeftRear]=-speed;
	motor[LeftMid]=-speed;
	motor[RightFront]=speed;
	motor[RightMid]=speed;
	motor[RightRear]=speed;
	wait1Msec(t);
	motor[LeftFront]=-0;
	motor[LeftMid]=0;
	motor[LeftRear]=-0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}

void bwdR(int t, int speed)//go backwards with encoder
{
	SensorValue[rightEncoder] = 0;// reset encoder
	SensorValue[leftEncoder] = 0;
	motor[LeftFront]=-speed;
	motor[LeftRear]=-speed;
	motor[LeftMid]=-speed;
	motor[RightFront]=-speed;
	motor[RightMid]=-speed;
	motor[RightRear]=-speed;
	while(SensorValue[rightEncoder]<t)
	{
	}
	motor[LeftFront]=0;
	motor[LeftMid]=0;
	motor[LeftRear]=0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}

void leftR(int t, int speed)// left with encoder
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	motor[LeftFront]=-speed;
	motor[LeftRear]=-speed;
	motor[LeftMid]=-speed;
	motor[RightFront]=speed;
	motor[RightMid]=speed;
	motor[RightRear]=speed;
	while(SensorValue[rightEncoder]<t)
	{
	}
	motor[LeftFront]=-0;
	motor[LeftMid]=0;
	motor[LeftRear]=-0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}

void rightR(int t, int speed)// right with encoder
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	motor[LeftFront]=speed;
	motor[LeftRear]=speed;
	motor[LeftMid]=speed;
	motor[RightFront]=-speed;
	motor[RightMid]=-speed;
	motor[RightRear]=-speed;
	while(SensorValue[leftEncoder]<t)
	{
	}
	motor[LeftFront]=-0;
	motor[LeftMid]=0;
	motor[LeftRear]=-0;
	motor[RightFront]=0;
	motor[RightMid]=0;
	motor[RightRear]=0;
}


void goalUp(int t)// raise goal lift
{
	motor[LeftGoal]=127;
	motor[RightGoal]=127;
	wait1Msec(t);
	motor[LeftGoal]=0;
	motor[RightGoal]=0;
}


void goalDown(int t)// lower goal lift
{
	motor[LeftGoal]=-127;
	motor[RightGoal]=-127;
	wait1Msec(t);
	motor[LeftGoal]=0;
	motor[RightGoal]=0;
}

void neargoal()
{
	goalDown(400);
	fwdR(600,50);
	goalUp(600);
	wait1Msec(200);
	leftR(270,50);
	fwdR(500,40);
	wait1Msec(200);
	leftR(175,40);
  fwdR(100,40);
  wait1Msec(200);
	rightR(300,60);
	fwdR(300,127);
	bwdR(175,67);
}

task autonomous()
{
	goalDown(400);
	fwdR(600,80);
	goalUp(600);
	wait1Msec(200);
	leftR(10,60);
	leftR(285,50);
	fwdR(660,60);
	wait1Msec(200);
	leftR(12,40);
  fwdR(325,127);
	bwdR(250,67);
  /*wait1Msec(200);
	rightR(270,60);
	fwdR(325,127);
	bwdR(197,67);
	delay(250);
// next, the red cone on left
	rightR(145,60);*/
	wait1Msec(300);
	rightR(90, 60);
	fwdR(70, 30);
	rightR(65, 60);
	fwdR(140, 95);
	rightR(160, 60);
	wait1Msec(200);
	goalDown(600);
	fwdR(540, 127);
	goalUp(600);
	wait1Msec(200);
	bwdR(500, 50);
	leftR(105, 50);
	bwdR(100, 60);
	leftR(60,60);
	fwdR(350, 127);
	bwdR(100,127);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		// Joysticks
		int threshold=10;
		int leftSpeed = vexRT[Ch3];  //get the Joystick inputs
		int rightSpeed = vexRT[Ch2];
		if(leftSpeed > threshold || leftSpeed < -threshold)  // check left side to deadband
		{
			motor[LeftFront]=leftSpeed;
			motor[LeftMid]=leftSpeed;
			motor[LeftRear]=leftSpeed;
		}
		else
		{
			motor[LeftFront]=0;
			motor[LeftMid]=0;
			motor[LeftRear]=0;

		}

		if(rightSpeed > threshold || rightSpeed < -threshold)// check right side to deadband
		{
			motor[RightFront]=rightSpeed;
			motor[RightMid]=rightSpeed;
			motor[RightRear]=rightSpeed;
		}
		else
		{
			motor[RightFront]=0;
			motor[RightMid]=0;
			motor[RightRear]=0;
		}

		// GOAL LIFT
		if(vexRT[Btn6U]==1)
		{
			motor[LeftGoal]=127;
			motor[RightGoal]=127;
		}
		else
		{
			if(vexRT[Btn6D]==1)
			{
				motor[LeftGoal]=-127;
				motor[RightGoal]=-127;
			}
			else
			{
				motor[LeftGoal]=0;
				motor[RightGoal]=0;

			}
		}


	}
}
