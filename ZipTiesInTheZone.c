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

//void initGyro(){
//	SensorType[gyro] = sensorNone; //Fixes common RobotC error with initializing Gyroscope
//	wait1Msec(1000);
//	SensorType[gyro] = sensorGyro;
//	wait1Msec(2000);
//	SensorValue[gyro] = 0; //Default Gyro heading is 0
//}
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
void pre_auton()
{
	bStopTasksBetweenModes = true;
	//bLCDBacklight = true;
	//clearLCDLine(0);
	//clearLCDLine(1);
	initIME();
	//initGyro();
	MotorSetInit (lift, liftMotors, 2);
	MotorSetInit (leftDrive, leftDriveMotors, 2);
	MotorSetInit (rightDrive, rightDriveMotors, 2);
	MotorSetInit (mobileGoal, mobileGoalMotors, 2);
	//InitHolonomicBase(driveTrain, driveMotors, 4);
	//initializeHolonomicAuto(driveMotors, wheelAngles);
	//displayLCDString(0,0,"INITIALIZING");
}

//task lcdManager()
//{
//	string lcdBatteryVoltages;
//	while(true)
//	{
//		sprintf(lcdBatteryVoltages, "M: %.2f P: %.2f", MainBatteryVoltage(), SensorValue(pPowerExp)/182.4);
//		clearLCDLine(0);
//		clearLCDLine(1);
//		displayLCDString(0,0,lcdBatteryVoltages);
//		delay(300);
//	}
//}

//void setArmPercentage (float percentage)
//{
//	leftPotVal = SensorValue(leftPot);
//	rightPotVal = SensorValue(rightPot);
//	int leftPotTarget = 3935*percentage/100 + 45;
//	int rightPotTarget = -3590*percentage/100 + 3935;
//}

task autonomous()
{

}

task usercontrol()
{
	while (true)
	{
		//startTask(liftControl);
		setPower(lift, vexRT[Btn5U] ? 1 : vexRT[Btn5D] ? -1 : 0);
		//liftTargetPercent = liftTargetPercent + 2*(vexRT[Btn5U] ? 1 : (vexRT[Btn5D] ? -1 : 0));
		liftTargetPercent = bound(liftTargetPercent, 0, 100);
		setPower(leftDrive, vexRT[Ch3Xmtr2]/127.);
		setPower(rightDrive, -vexRT[Ch2Xmtr2]/127.);
		setPower(mobileGoal, vexRT[Btn8UXmtr2] ? 1 : vexRT[Btn8DXmtr2] ? -1 : 0);
		motor[chainBar] = vexRT[Btn6U] ? 127 : vexRT[Btn6D] ? -127 : 0;
		motor[claw] = vexRT[Btn7U] ? 127 : vexRT[Btn7D] ? -127 : 0;
		delay(50);
	}
}
