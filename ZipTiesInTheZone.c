#pragma config(UserModel, "39zconfig.c")
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#include <Vex_Competition_Includes.c>
#include <CKVexMotorSet.h>
#include <CKVexIME.h>

tMotor liftMotors[] = {lLift, rLift};
MotorSet lift;

tMotor leftDriveMotors[] = {lBack, lFront};
tMotor rightDriveMotors[] = {rBack, rFront};
MotorSet leftDrive;
MotorSet rightDrive;

tMotor mobileGoalMotors[] = {lMobGoal, rMobGoal};
MotorSet mobileGoal;

int liftTargetPercent = 0;

void initIME(){
	nMotorEncoder[rBack] = 0;
	nMotorEncoder[lBack] = 0;
}

void initGyro(){
	SensorType[gyro] = sensorNone; //Fixes common RobotC error with initializing Gyroscope
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2000);
	SensorValue[gyro] = 0; //Default Gyro heading is 0
}

//Drives a given number of inches
void driveADistance(float inchesToDrive)
{
	float ticksToDrive = 360 * inchesToDrive / (4 * PI);
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	int rightEncoderCount = 0, leftEncoderCount = 0;
	bool rightIsDone = false, leftIsDone = false;
	float Kp = 0.5;
	SensorValue[gyro] = 0;
	int gyroReading = SensorValue[gyro];
	while (!rightIsDone || !leftIsDone)
	{
		rightIsDone = rightEncoderCount>=ticksToDrive;
		leftIsDone = leftEncoderCount>=ticksToDrive;
		gyroReading = SensorValue[gyro];
		rightEncoderCount += SensorValue[rightEncoder];
		SensorValue[rightEncoder] = 0;
		leftEncoderCount = SensorValue[leftEncoder];
		SensorValue[leftEncoder] = 0;
		float error = gyroReading;
		setPower(rightDrive, rightIsDone ? 0 : 75 - Kp*error);
		setPower(leftDrive, leftIsDone ? 0 : 75 + Kp*error);
	}
}
void turnRight(float degreesToTurn)
{
	int deciDegreesToTurn = degreesToTurn * 10;
	SensorValue[gyro] = 0;
	int gyroReading = -SensorValue[gyro];
	while (gyroReading < deciDegreesToTurn)
	{
		gyroReading = -SensorValue[gyro];
		setPower(rightDrive, -0.5);
		setPower(leftDrive, 0.5);
	}
	setPower(rightDrive, 0);
	setPower(leftDrive, 0);
}

void turnLeft(float degreesToTurn)
{
	int deciDegreesToTurn = degreesToTurn * 10;
	SensorValue[gyro] = 0;
	int gyroReading = SensorValue[gyro];
	while (gyroReading < deciDegreesToTurn)
	{
		gyroReading = SensorValue[gyro];
		setPower(rightDrive, 0.5);
		setPower(leftDrive, -0.5);
	}
	setPower(leftDrive, 0);
	setPower(rightDrive, 0);
}


task liftControl()
{
	float leftPot = SensorValue(leftLiftPot);
	float rightPot = SensorValue(rightLiftPot);
	float leftPotTarget = 3610;
	float rightPotTarget = 3673;
	float leftError = 0;
	float rightError = 0;
	float kPl = 0.00029;
	float kPr = 0.00024;
	while (true)
	{
		leftPot = SensorValue(leftLiftPot);
		rightPot = SensorValue(rightLiftPot);
		leftPotTarget = 3610 - (18.05*liftTargetPercent);
		rightPotTarget = 3673 - (18.79*liftTargetPercent);
		leftError = leftPot - leftPotTarget;
		rightError = rightPot - rightPotTarget;
		motor[lLift] = leftError*kPl*(3610-leftPotTarget);
		motor[rLift] = leftError*kPr*(3673-rightPotTarget);
		//delay(30);
	}
}

void initLCD()
{
	bLCDBacklight = true;
	clearLCDLine(0);
	clearLCDLine(1);
}

void pre_auton()
{
	bStopTasksBetweenModes = true;
	initLCD();
	initIME();
	initGyro();
	MotorSetInit (lift, liftMotors, 2);
	MotorSetInit (leftDrive, leftDriveMotors, 2);
	MotorSetInit (rightDrive, rightDriveMotors, 2);
	MotorSetInit (mobileGoal, mobileGoalMotors, 2);
	displayLCDString(0,0,"INITIALIZING");

}

task lcdManager()
{
	string lcdBatteryVoltages;
	while(true)
	{
		sprintf(lcdBatteryVoltages, "M: %.2f P: %.2f", MainBatteryVoltage(), SensorValue(pPowerExp)/182.4);
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,lcdBatteryVoltages);
		delay(300);
	}
}

void oldAutoRoutine()
{
	setPower(leftDrive, 1);
	setPower(rightDrive, -1);
	delay (3200);
	setPower(leftDrive, 0);
	setPower(rightDrive, 0);
	// old ^
	setPower(lift, 1);
	delay(650);
	setPower(lift, 0);
	motor[chainBar] = 127;
	delay(1375);
	motor[chainBar] = 0;
	delay(300);
	setPower(lift, -1);
	delay(400);
	setPower(lift, 0);
	motor[claw] = -127;
	delay(400);
	setPower(lift, 1);
	delay(400);
	motor[claw] = 0;
	setPower(lift, 0);
	setPower(mobileGoal, 1);
	delay(500);
	setPower(mobileGoal, 0);
}

task autonomous()
{

}

task usercontrol()
{
	while (true)
	{
		//startTask(liftControl);
		setPower(lift, vexRT[Btn6U] ? 1 : vexRT[Btn6D] ? -1 : 0);
		//liftTargetPercent = liftTargetPercent + 2*(vexRT[Btn5U] ? 1 : (vexRT[Btn5D] ? -1 : 0));
		liftTargetPercent = bound(liftTargetPercent, 0, 100);
		setPower(leftDrive, vexRT[Ch3]/127.);
		setPower(rightDrive, -vexRT[Ch2]/127.);
		setPower(mobileGoal, vexRT[Btn8U] ? 1 : vexRT[Btn8D] ? -1 : 0);
		motor[chainBar] = vexRT[Btn7D] ? 127 : vexRT[Btn7U] ? -127 : 0;
		motor[claw] = vexRT[Btn5D] ? 127 : vexRT[Btn5U] ? -127 : 0;
		delay(50);
	}
}
