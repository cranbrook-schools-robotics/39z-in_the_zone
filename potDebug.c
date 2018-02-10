#pragma config(UserModel, "39zconfig.c") //Cortex Configs
//#include "Vex_Competition_Includes.c" //Uses Vex stuff
#include <CKVexMotorSet.h>
task main()
{
	//SensorValue(leftEncoder) = 0;
	//SensorValue(rightEncoder) = 0;
float potVal1 = SensorValue(gyro);
float potVal2 = SensorValue(rightLiftPot);
clearDebugStream();
while(true)
{
	potVal1 = SensorValue(gyro);
	potVal2 = SensorValue(rightLiftPot);
	writeDebugStreamLine("Left Pot: %2f; Right Pot: %2f", potVal1, potVal2);
	delay(1000);
}

}
