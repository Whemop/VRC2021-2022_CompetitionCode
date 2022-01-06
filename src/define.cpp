#include "main.h"

/*
Define motors and sensor in this document
Don't forget to add the extern in the main.h file
*/

//prosv5 upload --slot [number]

#define Left_Arm_Port 2
#define Right_Arm_Port 12
#define Right_Drive_Port 13
#define Left_Drive_Port 20
#define Rear_Left_Arm_Port 3
#define Rear_Right_Arm_Port 10
#define Front_Loader_Port 6
/* Recommend Removal if not used
#define Ang_Pot_Port 'A'
#define lEncP1 'C'
#define lEncP2 'D'
#define rEncP1 'E'
#define rEncP2 'F'
#define Inertial_Port 8
*/
//

pros::Controller master (CONTROLLER_MASTER);
//pros::Imu inert (Inertial_Port);
//pros::Motor Left_Back_Drive (Left_Back_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
//pros::Motor Right_Front_Drive (Right_Front_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor Left_Drive (Left_Drive_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor Right_Drive (Right_Drive_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
pros::Motor Grabber (Front_Loader_Port,MOTOR_GEARSET_18,MOTOR_ENCODER_DEGREES);
pros::Motor Left_Arm (Left_Arm_Port,MOTOR_GEARSET_36,false,MOTOR_ENCODER_DEGREES);
pros::Motor Right_Arm (Right_Arm_Port,MOTOR_GEARSET_36,true,MOTOR_ENCODER_DEGREES);
pros::Motor Rear_Left_Arm (Rear_Left_Arm_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
pros::Motor Rear_Right_Arm (Rear_Right_Arm_Port,MOTOR_GEARSET_18,true,MOTOR_ENCODER_DEGREES);
//pros::Motor Arm (Arm_Port,MOTOR_GEARSET_18,false,MOTOR_ENCODER_DEGREES);
//pros::ADIAnalogIn Ang_Pot (Ang_Pot_Port);
//pros::ADIEncoder rEnc (rEncP1,rEncP2,true);
//pros::ADIEncoder lEnc (lEncP1,lEncP2,false);
