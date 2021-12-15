#include "main.h"
#include "autoSelect/selection.h"
/**
 * NOTE: To get code to properly upload to the robot, you must first save the
 * entire project (File>Save All). Then open a command line (cmd.exe or
 * terminal) and run "prosv5 make all" without the quotes. Then return to PROS
 * and use the upload tool (PROS>Upload). The build tool in the Atom/PROS editor
 * is broken and does not remove the old build files, then uploads the unchanged
 * files to the robot which changes nothing.
 * Also you cannot upload code to the controller, only directly to the robot.
 *
 * TODO:
 * (11/23/2021) Replace ? with actual motor port values [DONE]
 * (11/24/2021) Assign Controller Commands to all motors and verify [DONE]
 * (11/24/2021) Implememt framework for an on-demand option selector as a utility
 * tool during prematch routines [DONE]
 * (11/24/2021) Make Front Arm automacally move out of the way for option
 * selection, then return after selection is done (with a wait period so nobody
 * get their hands crushed) []
 * (11/24/2021) Add diagnostics data to screen during runtime for debug []
 * (12/14/2021) Add runtime code to keep both arm motors alligned []
 * (12/15/2021) Create an autonomous option that runs motor tests for debug []
 */

/**
 * Motor Definitions
 *
 * Use this area to define names to motor ports, keeping every definition
 * in one space makes motor managment sustainable on large scales.
 *
 * NOTE: Left and Right are defined from a perspective looking at the robot
 * from behind.
 */
const uint8_t LEFT_DRIVE_PORT = 20;
const uint8_t RIGHT_DRIVE_PORT = 11;
const uint8_t LEFT_ARM_PORT = 2;
const uint8_t RIGHT_ARM_PORT = 12;
const uint8_t FRONT_LOADER_PORT = 6;
const uint8_t REAR_LEFT_ARM_PORT = 3;
const uint8_t REAR_RIGHT_ARM_PORT = 10;
const uint8_t RING_LOADER_PORT = 1;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//Local motor name to global motor name assignment
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_wheel(LEFT_DRIVE_PORT);
	pros::Motor right_wheel(RIGHT_DRIVE_PORT, true); //true reverses motor
	pros::Motor arm_left(LEFT_ARM_PORT, MOTOR_GEARSET_36, true);
	pros::Motor arm_right(RIGHT_ARM_PORT, MOTOR_GEARSET_36);
	pros::Motor rear_arm_left(REAR_LEFT_ARM_PORT);
	pros::Motor rear_arm_right(REAR_RIGHT_ARM_PORT, true);
	pros::Motor front_loader(FRONT_LOADER_PORT);
	pros::Motor rear_loader(RING_LOADER_PORT, true);
	//pros::Motor debug(PORT);

	//Motor brake mode assignment
	rear_arm_left.set_brake_mode(MOTOR_BRAKE_HOLD);
	rear_arm_right.set_brake_mode(MOTOR_BRAKE_HOLD);
	front_loader.set_brake_mode(MOTOR_BRAKE_HOLD);
	//debug.set_brake_mode(MODE);

	//Autonomous Selector by Marsgate on GitHub
	//Red Left
	if(selector::auton == 1){
		front_loader.move_relative(-1000, 100);
		//.move_relative is writen with a target position and velocity, the target
		//position is stored in Encoder Units, which can be found on the Vex
		//Robotics Spec page for the v5 Motors.
	}

	//Red Right
	if(selector::auton == 2){
		left_wheel.move_velocity(100);
		right_wheel.move_velocity(100);
		pros::delay(2000);
		left_wheel.move_velocity(0);
		right_wheel.move_velocity(0);
		front_loader.move_velocity(-100);
		pros::delay(1500);
		left_wheel.move_velocity(-100);
		right_wheel.move_velocity(-100);
		front_loader.move_velocity(0);
		pros::delay(2000);
		left_wheel.move_velocity(0);
		right_wheel.move_velocity(0);
	}

	//Red Do Nothing
	if(selector::auton == 3){
		//Leave empty
	}

	//Blue Left
	if(selector::auton == -1){
		front_loader.move_relative(-1000, 100);
	}

	//Blue Right
	if(selector::auton == -2){
		left_wheel.move_velocity(100);
		right_wheel.move_velocity(100);
		pros::delay(2000);
		left_wheel.move_velocity(0);
		right_wheel.move_velocity(0);
		front_loader.move_velocity(-100);
		pros::delay(1500);
		left_wheel.move_velocity(-100);
		right_wheel.move_velocity(-100);
		front_loader.move_velocity(0);
		pros::delay(2000);
		left_wheel.move_velocity(0);
		right_wheel.move_velocity(0);
	}

	//Blue Do Nothing
	if(selector::auton == -3){
		//leave empty
	}

	//Skills
	if(selector::auton == 0){

	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//Local motor name to global motor name assignment
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_wheel(LEFT_DRIVE_PORT);
	pros::Motor right_wheel(RIGHT_DRIVE_PORT, true); //true reverses motor
	pros::Motor arm_left(LEFT_ARM_PORT, MOTOR_GEARSET_36, true);
	pros::Motor arm_right(RIGHT_ARM_PORT, MOTOR_GEARSET_36);
	pros::Motor rear_arm_left(REAR_LEFT_ARM_PORT);
	pros::Motor rear_arm_right(REAR_RIGHT_ARM_PORT, true);
	pros::Motor front_loader(FRONT_LOADER_PORT);
	pros::Motor rear_loader(RING_LOADER_PORT, true);
	//pros::Motor debug(PORT);

	//Motor brake mode assignment
	arm_left.set_brake_mode(MOTOR_BRAKE_HOLD);
	arm_right.set_brake_mode(MOTOR_BRAKE_HOLD);
	rear_arm_left.set_brake_mode(MOTOR_BRAKE_HOLD);
	rear_arm_right.set_brake_mode(MOTOR_BRAKE_HOLD);
	front_loader.set_brake_mode(MOTOR_BRAKE_HOLD);
	left_wheel.set_brake_mode(MOTOR_BRAKE_HOLD);
	right_wheel.set_brake_mode(MOTOR_BRAKE_HOLD);
	//debug.set_brake_mode(MODE);

	//Runtime loop
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 								(pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 								(pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		//Invert drive directions while A is pressed
		if (master.get_digital(DIGITAL_A)) {
		  //Left and right inverted Motor control
		  int power = master.get_analog(ANALOG_LEFT_Y);
		  int turn = master.get_analog(ANALOG_RIGHT_X);
		  int left = power + turn;
		  int right = power - turn;
		  left_wheel.move(-1 * left);
		  right_wheel.move(-1 * right);
		}
		else {
			//Left and right Motor control
			int power = master.get_analog(ANALOG_LEFT_Y);
			int turn = master.get_analog(ANALOG_RIGHT_X);
			int left = power + turn;
			int right = power - turn;
			left_wheel.move(left);
			right_wheel.move(right);
		}

		//Arm left and Right Motor control
		if (master.get_digital(DIGITAL_R1)) {
			arm_left.move_velocity(100);
			arm_right.move_velocity(100);
			//.move_velocity uses RPM as unit, so in this case 100 = 100rpm, or the
			//max speed of a red motor cartridge
		}
		else if (master.get_digital(DIGITAL_R2)) {
			arm_left.move_velocity(-100);
			arm_right.move_velocity(-100);
		}
		else {
			arm_left.move_velocity(0);
			arm_right.move_velocity(0);
		}

		//Rear Arm Left and Right Motor control
		if (master.get_digital(DIGITAL_L2)) {
			rear_arm_left.move_absolute(-700, 200);
			rear_arm_right.move_absolute(-700, 200);
			//as above, 200 = 200rpm, the max speed of a green motor cartridge
		}
		else {
			rear_arm_left.move_absolute(0, 200);
			rear_arm_right.move_absolute(0, 200);
		}

		//Grabber Motor Control
		if (master.get_digital(DIGITAL_L1)) {
			front_loader.move_absolute(-2000, 200);
			// move_absolute works with a position and a velocity, unlike move_relative
			// however, move_absolute sets the zero point to the position the motor was
			// started in when the program is run.
		}
		else {
			front_loader.move_absolute(0, 200);
		}

		//Ring intake Motor Controller
		if (master.get_digital(DIGITAL_UP)) {
			rear_loader.move_velocity(200);
		}
		else if (master.get_digital(DIGITAL_DOWN)) {
			rear_loader.move_velocity(-200);
		}
		else {
			rear_loader.move_velocity(0);
		}

		//debug.move(master.get_analog(INPUT));
		pros::delay(2);
	}
}
