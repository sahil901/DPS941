#pragma config(StandardModel, "RVW CLAWBOT")

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
LAB 1: Mobility Challenge

Name: Sahil Patel
Seneca Student ID: 159-065-176
Seneca Email: spatel392@myseneca.ca
Date of completion: Sept/17th/2021
Date Due: Sept/26th/2021
Prof Name: Jacky Lau
Class Section: NAA
----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

// main code of the program
task main()
{
	// Robot will wait for 2 seconds before executing program
  wait1Msec(2000);

	// Move forward at full power for 4 seconds
	motor[rightMotor] = 127;		    // Right motor is run at full (127) power forward
	motor[leftMotor]  = 127;		   // Left motor is run at full (127) power forward
	wait1Msec(4000);			        // Robot runs previous code for 4000 milliseconds before moving on

	// Turn to the left for 900 milliseconds
	motor[rightMotor] = 70;		    // Right motor is run at full (70) power
	motor[leftMotor]  = -70;		 // Left motor is run at full (-70) power
	wait1Msec(900);			        // Robot runs previous code for 900 milliseconds before moving on

	// Move forward at full power for 1.8 seconds
	motor[rightMotor] = 127;		  // Right motor is run at full (127) power forward
	motor[leftMotor]  = 127;		 // Left motor is run at full (127) power forward
	wait1Msec(1800);			      // Robot runs previous code for 1800 milliseconds before moving on

	// Turn to the right for 900 milliseconds
	motor[rightMotor] = -70;		 // Right motor is run at full (-70) power
	motor[leftMotor]  = 70;		  // Left motor is run at full (-70) power
	wait1Msec(900);			       // Robot runs previous code for 900 milliseconds before moving on

	// Move forward at full power for 1.5 seconds
	motor[rightMotor] = 127;		  // Right motor is run at full (127) power forward
	motor[leftMotor]  = 127;		  // Left motor is run at full (127) power forward
	wait1Msec(1500);			        // Robot runs previous code for 1500 milliseconds before moving on

  // Turn to the right for 850 milliseconds
	motor[rightMotor] = -70;		 // Right motor is run at full (-70) power
	motor[leftMotor]  = 70;		  // Left motor is run at full (-70) power
	wait1Msec(850);			       // Robot runs previous code for 850 milliseconds before moving on

	// Move forward at full power for 3.25 seconds
	motor[rightMotor] = 127;		  // Motor on port2 is run at full (127) power forward
	motor[leftMotor]  = 127;		 // Motor on port3 is run at full (127) power forward
	wait1Msec(3250);			      // Robot runs previous code for 3250 milliseconds before moving on

	// Turn to the right for 800 milliseconds
	motor[rightMotor] = -70;		 // Right motor is run at full (-70) power
	motor[leftMotor]  = 70;		  // Left motor is run at full (-70) power
	wait1Msec(800);			       // Robot runs previous code for 800 milliseconds before moving on

	// Move forward at full power for 5 seconds
	motor[rightMotor] = 127;		  // Right motor is run at full (127) power forward
	motor[leftMotor]  = 127;		 // Left motor is run at full (127) power forward
	wait1Msec(5000);			      // Robot runs previous code for 5000 milliseconds before moving on

	// Turn to the left for 4.2 seconds (does a spin essentially)
	motor[rightMotor] = 70;		   // Right motor is run at full (70) power
	motor[leftMotor]  = -70;		// Left motor is run at full (-70) power
	wait1Msec(4200);			     // Robot runs previous code for 4200 milliseconds before moving on

	// Move forward at full power for 750 milliseconds
	motor[rightMotor] = 127;		  // Right motor is run at full (127) power forward
	motor[leftMotor]  = 127;		 // Left motor is run at full (127) power forward
	wait1Msec(750);			        // Robot runs previous code for 750 milliseconds before moving on

}												        // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
