#pragma config(StandardModel, "RVW CLAWBOT")
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
LAB 2: Line Following

Name: Sahil Patel
Seneca Student ID: 159-065-176
Seneca Email: spatel392@myseneca.ca
Date of completion: Oct/6th/2021
Date Due: Oct/10th/2021
Prof Name: Jacky Lau
Class Section: NAA
----------------------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

// main code of the program
task main()
{
	// Robot will wait for 0.5 seconds before executing program
  wait1Msec(500);

  // Move forward at defined motor power for 4 seconds
  motor[rightMotor] = 50; 	// Right motor is running at 50 power forward
  motor[leftMotor] = 50; 		// Left motor is running at 50 power forward
  wait1Msec(4000);          // Robot runs previous code for 4000 milliseconds before moving on

  // Turn to the left for basically 90 degress
  motor[leftMotor] = 0; 		// Left motor is not running
  motor[rightMotor] = 127;  // Right motor is run at full (127) power
  wait1Msec(910);          	// Robot runs previous code for 910 milliseconds (resulting in a near 90° left turn)

  // value of the threshold
  int darknessofLine = 1500;

  // Clear Encoder Values by resetting them to 0
  SensorValue(rightEncoder) = 0;
  SensorValue(leftEncoder) = 0;

  //Line Track for 5 rotations...
  // changed the value to 3600
  while(SensorValue(rightEncoder) < 3600)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    displayLCDCenteredString(0, "Light Sensor:");           //  Display   |
    displayLCDPos(1,6);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(leftLineFollower));    //  Readings  |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // if the sensor sees light then it will steer to the left
    if(SensorValue(leftLineFollower) < darknessofLine)
    {
      motor[leftMotor]  = 63; 	// Left motor is run at 63 power
      motor[rightMotor] = 0; 	  // Right motor is not running
    }

    // otherwise the sensor sees dark then it will steer to the right
    else
    {
      motor[leftMotor]  = 0;  	// Left motor is not running
      motor[rightMotor] = 63; 	// Right motor is run at 63 power
    }
  }

}//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
