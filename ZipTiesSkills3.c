#pragma config(UserModel, "C:/Users/rstudent/code/39z-in_the_zone/39ZSkillsbotConfig.c")
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include <CKTankDrive.h>
#include <LCDBattery.h>

tMotor leftDriveMotors[] = {LeftFront, LeftMid, LeftRear};
MotorSet leftSide;
tMotor rightDriveMotors[] = {RightFront, RightMid, RightRear};
MotorSet rightSide;
TankDrive driveTrain;

tMotor mobileGoalMotors[] = {LeftGoal, RightGoal};
MotorSet mobileGoal;


void pre_auton()
{
	bStopTasksBetweenModes = true;
	MotorSetInit(leftSide, leftDriveMotors, 3);
	MotorSetInit(rightSide, rightDriveMotors, 3);
	MotorSetInit(mobileGoal, mobileGoalMotors, 2);
	TankDriveInit(driveTrain, leftSide, rightSide, leftEncoder, rightEncoder, gyro, 4, 0.05);
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

void neargoal()
{
	goalDown(400);
	driveForward(driveTrain, 42, 0.39);
	goalUp(600);
	wait1Msec(200);
	turnLeft(driveTrain, 180, 0.39);
	driveForward(driveTrain, 35, 0.39);
	wait1Msec(200);
	turnLeft(driveTrain, 116.7, 0.315);
	driveForward(driveTrain, 7, 0.315);
	wait1Msec(200);
	turnRight(driveTrain, 200, 0.47);
	driveForward(driveTrain, 21, 0.47);
	driveBackward(driveTrain, 12.2, 0.527);
}

task autonomous()
{
	goalDown(400);
	driveForward(driveTrain, 42, 0.63);
	goalUp(600);
	wait1Msec(200);
	turnLeft(driveTrain, 6.7, 0.47);
	turnLeft(driveTrain, 190, 0.39);
	driveForward(driveTrain, 46, 0.47);
	wait1Msec(200);
	turnLeft(driveTrain, 8, 0.315);
	driveForward(driveTrain, 22.7, 0.9);
	driveBackward(driveTrain, 17.5, 0.53);
	/*wait1Msec(200);
	rightR(270,60);
	fwdR(325,127);
	bwdR(197,67);
	delay(250);
	// next, the red cone on left
	rightR(145,60);*/
	wait1Msec(300);
	//rightR(90, 60);
	//fwdR(70, 30);
	//rightR(65, 60);
	//fwdR(140, 95);
	//rightR(160, 60);
	wait1Msec(200);
	goalDown(600);
	//fwdR(540, 127);
	goalUp(600);
	wait1Msec(200);
	//bwdR(500, 50);
	//leftR(105, 50);
	//bwdR(100, 60);
	//leftR(60,60);
	//fwdR(350, 127);
	//bwdR(100,127);

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
	}
}
