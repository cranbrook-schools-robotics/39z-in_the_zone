#pragma config(UserModel, "39zconfig.c") //Cortex Configs
//#include "Vex_Competition_Includes.c" //Uses Vex stuff
#include <CKVexMotorSet.h>
task main()
{
float potVal1 = SensorValue(leftLiftPot);
float potVal2 = SensorValue(rightLiftPot);
clearDebugStream();
while(true)
{
	potVal1 = SensorValue(leftLiftPot);
	potVal2 = SensorValue(rightLiftPot);
	writeDebugStreamLine("Left Pot: %2f; Right Pot: %2f", potVal1, potVal2);
	delay(500);
}

}
