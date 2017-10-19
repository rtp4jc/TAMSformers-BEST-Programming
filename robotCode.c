#pragma config(Motor,  port2,           RightMotor,    tmotorServoContinuousRotation, openLoop, driveRight)
#pragma config(Motor,  port3,           LeftMotor,     tmotorServoContinuousRotation, openLoop, driveLeft)
#pragma config(Motor,  port4,           CanMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           MannequinServoLeft, tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           MannequinServoRight, tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           ShooterMotor,  tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Btn6U = pull in paint cans
Btn6D = push out paint cans
Btn7U = toggle to backward drive (default = forward)
Btn5U = toggle to arm up (default = arm down)
Btn8U = hold to fire the shooter
Ch2 & Ch3 (joystick) = right & left motor forward/backward
Btn8U = shooter
*/

task main() {
	// boolean variable to determine the condition of the button
	bool driveStateButtonHeld = false;

	// enum to control the state of the mechanical arm
	enum ArmState {
		DOWN = 0, // 0
		NEUTRAL = 1, // 1
		UP = 2 // 2
	};

	// enum to control the state of the tank drive
	enum DriveState {
		BACKWARD, // false
		FORWARD // true
	};

  
	// boolean variable to control the arm state initialized to an enumerated type
	bool driveState = FORWARD;

	// int variable to control the arm state initialized to an enumerated type
	ArmState armState = UP;

  
	while (true) {

		// controls the paint can apparatus
		if (vexRT[Btn6U]){
			motor[CanMotor] = 127; // pull in paint cans
		}
		else if (vexRT[Btn6D]){
			motor[CanMotor] = -127; // push cans back out
		}
		else {
			motor[CanMotor] = 0; // sets motor to neutral state
		}

		// controls the shooter
		if (vexRT[Btn8U]){
		  motor[ShooterMotor] = 127; // start the shooter motor
		}
		else {
		  motor[ShooterMotor] = 0; // stop the shooter when the button isn't held
		}

		// sets tank drive state
		if (vexRT[Btn7U] && !driveStateButtonHeld) {
			driveStateButtonHeld = true; // recognize the button is pressed
			driveState = !driveState; // flip the drive state
		}
		else if (!vexRT[Btn7U]) {
			driveStateButtonHeld = false; // recognize the button is not pressed
		}

		// control tank drive
		if (driveState) {
			// drive forward with full power on both motors
			motor[RightMotor] = vexRT[Ch2];
			motor[LeftMotor] = vexRT[Ch3];
		}
		else {
			// drive reverse with full power on both motors;
			motor[RightMotor] = -1 * vexRT[Ch3];
			motor[LeftMotor] = -1 * vexRT[Ch2];
		}

		// mannequin arm controls
		// non-inverted controls: 5U -> raises the arm to a neutral position
		// 										    5D -> lowers the arm

		// use when the arm is not in the down state
		if (vexRT[Btn5D] && armState != DOWN) {
			// both motors to full power, offset to account for reversed spin
			motor[MannequinServoRight] = 85;
			motor[MannequinServoLeft] = -85;
			armState = DOWN; // set the arm state to down
		}
		// use when the arm is not in the neutral state
		else if (vexRT[Btn5U] && armState != NEUTRAL) {
			// both motors to full power, offset to account for reversed spin
			motor[MannequinServoRight] = 0;
			motor[MannequinServoLeft] = 0;
			armState = NEUTRAL; // set the arm state to up
		}
		// use when the arm is not in the up state
		else if (vexRT[Btn7R] && armState != UP) {
	  	motor[MannequinServoRight] = -127;
	  	motor[MannequinServoLeft] = 127;

			armState = UP; // set the arm state to up
		}
	}
}
