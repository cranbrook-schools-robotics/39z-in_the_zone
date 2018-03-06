#pragma config(UserModel, "39ZSkillsbotConfig.c")
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include <CKTankDrive.h>
#include <LCDBattery.h>

tMotor leftDriveMotors[] = {LeftFront, LeftMid, LeftRear};
//MotorSet leftSide;
tMotor rightDriveMotors[] = {RightFront, RightMid, RightRear};
//MotorSet rightSide;
TankDrive driveTrain;

tMotor mobileGoalMotors[] = {LeftGoal, RightGoal};
MotorSet mobileGoal;


void pre_auton()
{
	bStopTasksBetweenModes = true;
	//MotorSetInit(leftSide, leftDriveMotors, 3);
	//MotorSetInit(rightSide, rightDriveMotors, 3);
	MotorSetInit(mobileGoal, mobileGoalMotors, 2);
	TankDriveInit(driveTrain, leftDriveMotors, rightDriveMotors, 3, leftEncoder, rightEncoder, gyro, 4, 0.01);
	LCDInitialize();
}


void goalUp(int t)// raise goal lift
{
	setPower(mobileGoal, 1);
	wait1Msec(t);
	setPower(mobileGoal, 0);
}


void goalDown(int t)// lower goal lift
{
	setPower(mobileGoal, -1);
	wait1Msec(t);
	setPower(mobileGoal, 0);
}

task autonomous()
{
	goalDown(650);
	driveForward(driveTrain, 57, 0.6);
	goalUp(600);
	wait1Msec(200);
	turnLeft(driveTrain, 180, 0.4);
	driveT(driveTrain,true,1500,0.70);
	driveBackward(driveTrain,22,0.7);
	turnRight(driveTrain,90,.25);
	driveForward(driveTrain,30,0.6);
	turnRight(driveTrain,34,0.25);
	goalDown(600);
	driveForward(driveTrain,65,0.75);
	goalUp(600);
	driveBackward(driveTrain,53,0.7);
	turnLeft(driveTrain,90,0.4);
	driveForward(driveTrain,20,0.7);
	driveBackward(driveTrain,10,0.5);
	turnLeft(driveTrain,45,0.3);
	driveForward(driveTrain,30,0.7);
	turnLeft(driveTrain,45,0.3);
	goalDown(400);
	driveForward(driveTrain,50,0.7);
	goalUp(400);
	driveBackward(driveTrain,50,0.6);
	turnLeft(driveTrain,90,0.3);
	driveForward(driveTrain,20,0.7);
	driveBackward(driveTrain,10,0.7);
	turnRight(driveTrain,180,0.3);
	goalDown(400);
	driveForward(driveTrain,50,0.7);
	goalUp(400);
	driveBackward(driveTrain,60,0.5);
	turnRight(driveTrain,135,0.4);
	driveForward(driveTrain,10,0.75);
	turnLeft(driveTrain,90,0.35);
	driveForward(driveTrain,10,0.7);
	goalDown(400);
	driveBackward(driveTrain,10,0.7);
	turnRight(driveTrain,180,0.5);
	goalDown(400);
	driveForward(driveTrain,50,0.6);
	goalUp(400);
	driveBackward(driveTrain,50,0.45);
	turnLeft(driveTrain,135,0.4);
	driveForward(driveTrain,15,0.1);
	turnLeft(driveTrain,180,0.4);
	driveForward(driveTrain,50,0.7);
	goalDown(400);
	driveBackward(driveTrain,15,0.55);
	turnLeft(driveTrain,180,0.6);
	driveForward(driveTrain,40,0.7);
	turnRight(driveTrain,30,0.7);
	driveForward(driveTrain,72,0.7);
	turnLeft(driveTrain,90,0.5);
	driveForward(driveTrain,15,0.4);
	turnLeft(driveTrain,90,0.35);
	driveForward(driveTrain,20,0.7);
	goalDown(400);
	driveBackward(driveTrain,20,0.6);
	turnLeft(driveTrain,180,0.4);
	driveForward(driveTrain,65,0.7);
	goalUp(400);
	driveForward(driveTrain,20,0.5);
	turnLeft(driveTrain,20,0.3);
	driveForward(driveTrain,40,0.8);
	driveBackward(driveTrain,15,0.5);
	turnRight(driveTrain,90,0.4);
	driveForward(driveTrain,10,0.4);
	turnRight(driveTrain,45,0.42);
	goalDown(400);
	driveForward(driveTrain,65,0.4);
	goalUp(400);
	driveBackward(driveTrain,50,0.4);
	turnRight(driveTrain,135,0.5);
	driveForward(driveTrain,15,0.45);
	turnRight(driveTrain,90,0.4);
	driveForward(driveTrain,15,0.5);
	goalDown(400);
	driveBackward(driveTrain,15,0.6);
	turnLeft(driveTrain,90,0.45);
	driveForward(driveTrain,55,0.6);
	turnLeft(driveTrain,45,0.5);
	goalDown(400);
	driveForward(driveTrain,60,0.5);
	goalUp(400);
	driveBackward(driveTrain,50,0.4);
	turnLeft(driveTrain,140,0.35);
	driveForward(driveTrain,20,0.4);
	turnLeft(driveTrain,90,0.29);
	driveForward(driveTrain,20,0.5);
	goalDown(400);
	driveBackward(driveTrain,20,0.5);
}


task usercontrol()
{

	while (true)
	{
		startTask(ManageLCD);
		setDriveTank(driveTrain, 10);
		//setPower(leftSide, (abs(vexRT[Ch3]) > 10) ? vexRT[Ch3]/127.0 : 0);
		//setPower(rightSide, (abs(vexRT[Ch2]) > 10) ? vexRT[Ch2]/127.0 : 0);
		setPower(mobileGoal, vexRT[Btn6U] ? 1 : vexRT[Btn6D] ? -1 : 0);
		if (vexRT[Btn7L])
			startTask(autonomous);
		if (vexRT[Btn7R])
			stopTask(autonomous);
	}
}
