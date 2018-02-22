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
void driveT(bool forward, int time)
{
	setPower(rightDrive, forward ? 1 : -1);
	setPower(leftDrive, forward ? 1 : -1);
	delay(time);
	setPower(rightDrive, forward ? -0.15 : 0.15);
	setPower(leftDrive, forward ? -0.15 : 0.15);
	delay(40);
	setPower(rightDrive, 0);
	setPower(leftDrive, 0);
}
void driveForward(float inchesToDrive)
{
	float ticksToDrive = 360 * inchesToDrive / (8 * PI);
	SensorValue(leftEncoder) = 0;
	SensorValue(rightEncoder) = 0;
	int rightEncoderCount = 0, leftEncoderCount = 0;
	bool rightIsDone = false, leftIsDone = false;
	float Kp = 0.05;
	SensorValue(gyro) = 0;
	int gyroReading = SensorValue[gyro];
	while (!rightIsDone || !leftIsDone)
	{
		rightIsDone = rightEncoderCount>=ticksToDrive;
		leftIsDone = leftEncoderCount>=ticksToDrive;
		gyroReading = SensorValue[gyro];
		rightEncoderCount += SensorValue[rightEncoder];
		SensorValue(rightEncoder) = 0;
		leftEncoderCount += SensorValue[leftEncoder];
		SensorValue(leftEncoder) = 0;
		float error = gyroReading;
		setPower(rightDrive, rightIsDone ? 0 : bound(75 - Kp*error, 0, 1));
		setPower(leftDrive, leftIsDone ? 0 : bound(75 + Kp*error, 0, 1));
	}
	setPower(rightDrive, -0.15);
	setPower(leftDrive, -0.15);
	delay(40);
	setPower(rightDrive, 0);
	setPower(leftDrive, 0);
}

//Drives a given number of inches
void driveBackward(float inchesToDrive)
{
	float ticksToDrive = -360 * inchesToDrive / (8 * PI);
	SensorValue(leftEncoder) = 0;
	SensorValue(rightEncoder) = 0;
	int rightEncoderCount = 0, leftEncoderCount = 0;
	bool rightIsDone = false, leftIsDone = false;
	float Kp = 0.05;
	SensorValue(gyro) = 0;
	int gyroReading = SensorValue[gyro];
	while (!rightIsDone || !leftIsDone)
	{
		rightIsDone = rightEncoderCount<=ticksToDrive;
		leftIsDone = leftEncoderCount<=ticksToDrive;
		gyroReading = SensorValue[gyro];
		rightEncoderCount += SensorValue[rightEncoder];
		SensorValue(rightEncoder) = 0;
		leftEncoderCount += SensorValue[leftEncoder];
		SensorValue(leftEncoder) = 0;
		float error = gyroReading;
		setPower(rightDrive, rightIsDone ? 0 : bound(-75 - Kp*error, -1, 0));
		setPower(leftDrive, leftIsDone ? 0 : bound(-75 + Kp*error, -1, 0));
	}
	setPower(rightDrive, 0.15);
	setPower(leftDrive, 0.15);
	delay(40);
	setPower(rightDrive, 0);
	setPower(leftDrive, 0);
}

void turnRight(float degreesToTurn)
{
	int deciDegreesToTurn = degreesToTurn * 10;
	SensorValue[gyro] = 0;
	int gyroReading = -SensorValue[gyro];
	while (gyroReading != deciDegreesToTurn)
	{
		gyroReading = -SensorValue[gyro];
		if(gyroReading < deciDegreesToTurn){
			setPower(rightDrive, -0.33);
			setPower(leftDrive, 0.33);
		}
		if(gyroReading > deciDegreesToTurn){
			setPower(rightDrive, 0.33);
			setPower(leftDrive, -0.33);
		}
	}
	setPower(leftDrive, 0.05);
	setPower(rightDrive, -0.05);
	delay(40);
	setPower(leftDrive, 0);
	setPower(rightDrive, 0);
}

void turnLeft(float degreesToTurn)
{
	int deciDegreesToTurn = (degreesToTurn-6) * 10;
	SensorValue[gyro] = 0;
	int gyroReading = SensorValue[gyro];
	while (gyroReading != deciDegreesToTurn)
	{
		gyroReading = SensorValue[gyro];
		if (gyroReading < deciDegreesToTurn)
		{
			setPower(rightDrive, 0.33);
			setPower(leftDrive, -0.33);
		}
		if (gyroReading > deciDegreesToTurn)
		{
			setPower(rightDrive, -0.33);
			setPower(leftDrive, 0.33);
		}
	}
	setPower(leftDrive, -0.05);
	setPower(rightDrive, 0.05);
	delay(40);
	setPower(leftDrive, 0);
	setPower(rightDrive, 0);
}


task liftControl()
{
	float leftPot = SensorValue(leftLiftPot);
	float rightPot = SensorValue(rightLiftPot);
	float leftPotTarget = 525;
	float rightPotTarget = 3290;
	float leftError = 0;
	float rightError = 0;
	float kPl = 0.00025;
	float kPr = 0.00025;
	while (true)
	{
		leftPot = SensorValue(leftLiftPot);
		rightPot = SensorValue(rightLiftPot);
		leftPotTarget = 525 + (15.6*liftTargetPercent);
		rightPotTarget = 3290 - (16.0*liftTargetPercent);
		leftError = leftPot - leftPotTarget;
		rightError = rightPot - rightPotTarget;
		motor[lLift] = leftError*kPl*(525+leftPotTarget);
		motor[rLift] = leftError*kPr*(3290-rightPotTarget);
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
		sprintf(lcdBatteryVoltages, "M: %.2f P: %.2f", MainBatteryVoltage(), SensorValue(pPowerExp)/283.2);
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,lcdBatteryVoltages);
		delay(300);
	}
}

void oldAutoRoutine()
{
	driveT(true, 3200);
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

void defenseAuto()
{
	driveForward(100);
	turnLeft(75);
	driveForward(30);
}

void offenseMatchAuto()
{
	driveForward(88);
	setPower(mobileGoal, 1);
	delay(2000);
	setPower(mobileGoal, 0);
	motor[claw] = -127;
	delay(750);
	motor[claw] = 0;
	driveBackward(41);
	turnLeft(180);
	setPower(lift, 1);
	delay(1000);
	setPower(lift, 0);
	driveForward(40);
	driveT(true, 750);
	setPower(mobileGoal, -1);
	delay(500);
	driveBackward(12);
	setPower(mobileGoal, 0);


}

void progSkills()
{
	offenseMatchAuto();
	setPower(mobileGoal, -1);
	delay(1500);
	setPower(mobileGoal, 1);
	delay(250);
	setPower(mobileGoal, 0);
	driveT(false, 750);
	turnLeft(135);
	driveForward(36);
	turnLeft(90);
	driveForward(12);
	setPower(mobileGoal, 1);
	delay(700);
	setPower(mobileGoal, 0);
	driveBackward(12);
	turnLeft(135);
	driveT(true, 1500);

}

void autoTest()
{
	//driveForward(12);
	//turnLeft(90);
	//driveForward(24);
	//turnRight(90);
	//turnLeft(90);
	//driveBackward(12);

}
void moveForwardAuto()
{
	driveForward(84);
	setPower(mobileGoal, 1);
	delay(1000);
	setPower(mobileGoal, 0);
	motor[claw] = -127;
	delay(750);
	motor[claw] = 0;
	driveBackward(60);
	turnRight(180);
	//driveForward(14);
	setPower(mobileGoal, -1);
	delay(1500);
	setPower(mobileGoal, 0);
	driveBackward(20);

}
void moveForwardAutoT()
{
	driveT(true, 3250);
	setPower(mobileGoal, 1);
	delay(1000);
	setPower(mobileGoal, 0);
	motor[claw] = -127;
	delay(750);
	motor[claw] = 0;
	driveT(false, 2200);
	turnRight(180);
	//driveForward(14);
	setPower(mobileGoal, -1);
	delay(1500);
	setPower(mobileGoal, 0);
	driveT(false, 750);


}

task autonomous()
{
	//oldAutoRoutine();
	//defenseAuto();
	//moveForwardAuto();
	moveForwardAutoT();
	//offenseMatchAuto();
	//progSkills();
	//autoTest();
}

task usercontrol()
{
	while (true)
	{
		bool isLeftUp = SensorValue(leftButton) == 1;
		bool isRightUp = SensorValue(rightButton) == 1;
		//startTask(liftControl);
		startTask(lcdManager);
		setPower(lift, (isLeftUp&&isRightUp&&vexRT[Btn6U]) ? 0.3 : vexRT[Btn6U] ? 1 : vexRT[Btn6D] ? -1 : 0);
		//liftTargetPercent = liftTargetPercent + 2*(vexRT[Btn5U] ? 1 : (vexRT[Btn5D] ? -1 : 0));
		//liftTargetPercent = bound(liftTargetPercent, 0, 100);
		setPower(leftDrive, vexRT[Ch3]/127.);
		setPower(rightDrive, vexRT[Ch2]/127.);
		setPower(mobileGoal, vexRT[Btn8U] ? 1 : vexRT[Btn8D] ? -1 : 0);
		motor[chainBar] = vexRT[Btn7D] ? 127 : vexRT[Btn7U] ? -127 : 0;
		motor[claw] = vexRT[Btn5D] ? 127 : vexRT[Btn5U] ? -127 : 0;
		delay(50);
	}
}
