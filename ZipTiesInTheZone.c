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
		setPower(lift, vexRT[Btn5U] ? 1 : vexRT[Btn5D] ? -1 : 0);
		setPower(leftDrive, vexRT[Ch3Xmtr2]/127.);
		setPower(rightDrive, -vexRT[Ch2Xmtr2]/127.);
		setPower(mobileGoal, vexRT[Btn8UXmtr2] ? 1 : vexRT[Btn8DXmtr2] ? -1 : 0);
		motor[chainBar] = vexRT[Btn6U] ? 127 : vexRT[Btn6D] ? -127 : 0;
		motor[claw] = vexRT[Btn7U] ? 127 : vexRT[Btn7D] ? -127 : 0;
	}
}
