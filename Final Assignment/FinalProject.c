#pragma config(StandardModel, "RVW CLAWBOT")
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Group 3: Project Submission

Name + Seneca Student ID + Seneca Email: Sahil Patel (159-065-176) spatel392@myseneca.ca
Date of completion: Dec/4th/2021
Date Due: Dec/8th/2021
Prof Name: Jacky Lau
Class Section: NAA
----------------------------------------------------------------------------------------------------*/
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN CODE |+++++++++++++++++++++++++++++++++++++++++++++++
#define CIR 28.8 // circumference
#define ARC_DEGREE 0.24 // angle per degree for turning
#define ENCODER_PULSE 360 // pulse per revolution
#define THRESHOLD 1000
#define MOVE_SPEED 50

void moveFront(float distance) {
	float rev = distance / CIR; // revolution required
	int pulse = ENCODER_PULSE * rev; // encoder pulse required

	//SensorValue[leftEncoder] = 0; // reset encoder value
	float encodervalOg = SensorValue[leftEncoder];

	while ((SensorValue[leftEncoder] - encodervalOg) < pulse) // move while pulse not reached
	{
		motor[rightMotor] = MOVE_SPEED;
		motor[leftMotor] = MOVE_SPEED;
	}
}
void moveBack(float distance) {
	float rev = distance / CIR; // revolution required
	int pulse = ENCODER_PULSE * rev; // encoder pulse required

	//SensorValue[leftEncoder] = 0; // reset encoder value
	float encodervalOg = SensorValue[leftEncoder];

	while (SensorValue[leftEncoder] > (encodervalOg -pulse)) // move while pulse not reached
	{
		motor[rightMotor] = -MOVE_SPEED;
		motor[leftMotor] = -MOVE_SPEED;
	}
}
void turnLeft(float angle) {
	float distance = angle * ARC_DEGREE; // arc distance required
	float rev = distance / CIR; // revolution required
	int pulse = ENCODER_PULSE * rev; // encoder pulse required

	SensorValue[rightEncoder] = 0; // reset encoder value

	while (SensorValue[rightEncoder] < pulse) // move while pulse not reached
	{		
		motor[rightMotor] = MOVE_SPEED; // speed might affect dynamics if changed
		motor[leftMotor] = -MOVE_SPEED;
	}
}

void turnRight(float angle) {
	float distance = angle * ARC_DEGREE; // arc distance required
	float rev = distance / CIR; // revolution required
	int pulse = ENCODER_PULSE * rev; // encoder pulse required

	SensorValue[leftEncoder] = 0; // reset encoder value

	while (SensorValue[leftEncoder] < pulse) // move while pulse not reached
	{		
		motor[rightMotor] = -MOVE_SPEED; // speed might affect dynamics if changed
		motor[leftMotor] = MOVE_SPEED;
	}
}

void armUp() {
	stopAllMotors();
	while (SensorValue[armIME] > -1000) {
		motor[armMotor] = 100;
	}
	motor[armMotor] = 0;
}
void armDown() {
	stopAllMotors();
	while (SensorValue[armIME] < 60) {
		motor[armMotor] = -100;
	}
	motor[armMotor] = 0;
}

int calibrationSequence() {
	int startPosition = 0;
	armUp();// move arm up so we  have   clerance for movement
	moveFront(15);
	turnLeft(75);
	if (SensorValue[sonarSensor] < 93) {
		turnRight(75);
		startPosition = 1;
	}
	else if (startPosition == 0) {
		turnRight(75);
		turnRight(75);
		if (SensorValue[sonarSensor] < 60)
			startPosition = 3;
		turnLeft(75);
	}
	if (startPosition == 0) {
		startPosition = 2;
	}
	return startPosition;
}
void followLineEncoder(float distance) {
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	int threshold = 1500;    /* found by taking a reading on both DARK and LIGHT    */
							 /* surfaces, adding them together, then dividing by 2. */
	while (SensorValue[rightEncoder] < distance) {
		// RIGHT sensor sees dark:
	if (SensorValue(leftLineFollower) > threshold)
		{
			// counter-steer left:
			motor[leftMotor] = 0;
			motor[rightMotor] = MOVE_SPEED;
		}

		// CENTER sensor sees dark:
		if (SensorValue(centerLineFollower) > threshold)
		{
			// go straight
			motor[leftMotor] = MOVE_SPEED;
			motor[rightMotor] = MOVE_SPEED;
		}
		// LEFT sensor sees dark:
		if (SensorValue(rightLineFollower) > threshold)
		{
			// counter-steer right:
			motor[leftMotor] = MOVE_SPEED;
			motor[rightMotor] = 0;
		}
		//if((SensorValue(centerLineFollower) == 0)&&(SensorValue(centerLineFollower) == 0)&&(SensorValue(centerLineFollower) == 0)){
		//	turnLeft(5);
		//}
	}
}

void turngyropos(float angle){
	float initalgyrosen= SensorValue[gyro];

	if((initalgyrosen)	> angle){

		while (SensorValue[gyro] > (angle)) // move while pulse not reached
		{
			motor[rightMotor] = (MOVE_SPEED-20); // speed might affect dynamics if changed
			motor[leftMotor] = -(MOVE_SPEED-20);
		}
	}else{
		//gyrocheck = initalgyrosen + 1800;
		while (SensorValue[gyro] < (angle)) // move while pulse not reached
		{

			motor[rightMotor] = -(MOVE_SPEED-20); // speed might affect dynamics if changed
			motor[leftMotor] = (MOVE_SPEED-20);
		}
	}
}
void turn180() {
	float initalgyrosen= SensorValue[gyro];
	float gyrocheck = initalgyrosen + 1800;
	if((gyrocheck)	> 3600){
		gyrocheck=gyrocheck - 3600;
		while (SensorValue[gyro] > (gyrocheck)) // move while pulse not reached
		{
			motor[rightMotor] = (MOVE_SPEED-20); // speed might affect dynamics if changed
			motor[leftMotor] = -(MOVE_SPEED-20);
		}
	}else{
		//gyrocheck = initalgyrosen + 1800;
		while (SensorValue[gyro] < (gyrocheck)) // move while pulse not reached
		{
			motor[rightMotor] = -(MOVE_SPEED-20); // speed might affect dynamics if changed
			motor[leftMotor] = (MOVE_SPEED-20);
		}
	}
}

bool followLineEncoderRoad1_3() {
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	bool obstaclefound = false;
	bool cupfound = false;
	float returnSequence = 0;
	float roadencode = 2000;
	int threshold = 1500;    /* found by taking a reading on both DARK and LIGHT    */
							 /* surfaces, adding them together, then dividing by 2. */

	while ((SensorValue[rightEncoder] < roadencode) && !obstaclefound && !cupfound) {
		// RIGHT sensor sees dark:
		if (SensorValue(rightLineFollower) > threshold)
		{
			// counter-steer right:
			motor[leftMotor] = MOVE_SPEED;
			motor[rightMotor] = 0;
		}
		// CENTER sensor sees dark:
		if (SensorValue(centerLineFollower) > threshold)
		{
			// go straight
			motor[leftMotor] = MOVE_SPEED;
			motor[rightMotor] = MOVE_SPEED;
		}
		// LEFT sensor sees dark:
		if (SensorValue(leftLineFollower) > threshold)
		{
			// counter-steer left:
			motor[leftMotor] = 0;
			motor[rightMotor] = MOVE_SPEED;
		}
		if ((SensorValue[sonarSensor] < 15)) {
			if (SensorValue[rightEncoder] < 1500) {
				obstaclefound = true;
				returnSequence = (SensorValue[rightEncoder]) / 2;
				SensorValue[gyro] = 0;
				stopAllMotors();
				while (SensorValue[gyro] < 1800) // move while pulse not reached
				{
					motor[rightMotor] = -MOVE_SPEED; // speed might affect dynamics if changed
					motor[leftMotor] = MOVE_SPEED;
				}
			}
			else {
				cupfound = true;
			}


		}
	}
	if (obstaclefound) {
		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
		while (SensorValue[rightEncoder] < returnSequence) {
			// RIGHT sensor sees dark:
			if (SensorValue(rightLineFollower) > threshold)
			{
				// counter-steer right:
				motor[leftMotor] = MOVE_SPEED;
				motor[rightMotor] = 0;
			}
			// CENTER sensor sees dark:
			if (SensorValue(centerLineFollower) > threshold)
			{
				// go straight
				motor[leftMotor] = MOVE_SPEED;
				motor[rightMotor] = MOVE_SPEED;
			}
			// LEFT sensor sees dark:
			if (SensorValue(leftLineFollower) > threshold)
			{
				// counter-steer left:
				motor[leftMotor] = 0;
				motor[rightMotor] = MOVE_SPEED;
			}
		}
	}
	return obstaclefound;
}
bool roadfunction2() {
	stopAllMotors();
	float rev = 50 / CIR; // revolution required
	int pulse = ENCODER_PULSE * rev; // encoder pulse required
	bool obstaclefound = false;
	//SensorValue[leftEncoder] = 0; // reset encoder value
	float encodervalOg = SensorValue[leftEncoder];
	float returnSequence = 0;
	float returnSeqSensorval = 0;
	int threshold = 1500;
	while (((SensorValue[leftEncoder] - encodervalOg) < pulse) && !obstaclefound)// move while pulse not reached
	{
		if (SensorValue[sonarSensor] < 20) {
			returnSequence = (SensorValue[leftEncoder]) - encodervalOg;
			obstaclefound = true;
			returnSeqSensorval = SensorValue[leftEncoder] + returnSequence;
		}
		else {
			motor[rightMotor] = MOVE_SPEED;
			motor[leftMotor] = MOVE_SPEED;
		}
	}

	if (obstaclefound) {
		stopAllMotors();
		turn180();
		SensorValue[leftEncoder]=0;
		SensorValue[rightEncoder]=0;
		while (SensorValue[leftEncoder] < returnSequence) {
			motor[rightMotor] = MOVE_SPEED;
			motor[leftMotor] = MOVE_SPEED;
		}
		turnRight(90);
	}else{
		turnRight(10);
		turngyropos(20);
		SensorValue[leftEncoder]=0;
		SensorValue[rightEncoder]=0;
		while (SensorValue[rightEncoder] < 1000) {
			// RIGHT sensor sees dark:
			if (SensorValue(rightLineFollower) > threshold)
			{
				// counter-steer right:
				motor[leftMotor] = MOVE_SPEED;
				motor[rightMotor] = 0;
			}
			// CENTER sensor sees dark:
			if (SensorValue(centerLineFollower) > threshold)
			{
				// go straight
				motor[leftMotor] = MOVE_SPEED;
				motor[rightMotor] = MOVE_SPEED;
			}
			// LEFT sensor sees dark:
			if (SensorValue(leftLineFollower) > threshold)
			{
				// counter-steer left:
				motor[leftMotor] = 0;
				motor[rightMotor] = MOVE_SPEED;
			}
		}
		moveFront(25);
	}
	return obstaclefound;
}







//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{

	float distance2follow = 2400;
	int startPosition = calibrationSequence();
	followLineEncoder(900);


	moveFront(40);

	if (startPosition < 3) {
		turnRight(85);
		if (startPosition == 2) {
			distance2follow = distance2follow / 2;
		}
		followLineEncoder(distance2follow);
		turnLeft(35);
	}

	// roads
	bool road1 = followLineEncoderRoad1_3();
	bool road2 = false;
	bool road3 = false;
	int openRoad=0;
	if (road1) {
		moveFront(20);
		turnRight(90);
		followLineEncoder(1100);
		turnRight(90);
		road2 = roadfunction2();
	}
	if (road2 && road1) {
		followLineEncoder(250);
		moveFront(75);
		turnRight(90);
		road3 =followLineEncoderRoad1_3();
	}

	armDown();


	while(SensorValue[sonarSensor]>25){
				motor[leftMotor] = MOVE_SPEED-30;
				motor[rightMotor] = MOVE_SPEED-30;
	}

	bool recenter =false;
	if(!road1){
		openRoad=1;
		moveFront(6);
		turnRight(70);
		turnLeft(70);
		moveBack(25);
		moveFront(20);
		turnLeft(90);
		moveFront(10);
		followLineEncoder(1000);
		//cup2
		turnRight(90);
		if(SensorValue[sonarSensor]>20)	{
			moveFront(8);
			recenter =true;
		}
		if(recenter)
			moveBack(4);
		// cup2
		//Move to  front  switch to position	20 degrees up to pic line
		turngyropos(2900);
		followLineEncoder(780);
		moveFront(25);
		//cup3
		turnRight(90);
		turnRight(90);
		//cup3
		//recenter to  east//
		moveFront(15);
		turngyropos(900);
		followLineEncoder(1700);
		turngyropos(900);

		while(SensorValue[sonarSensor]>65){
			moveFront(1);
		}

	turngyropos(1800);
		moveFront(10);
		followLineEncoder(1850);
		if(SensorValue[sonarSensor]>150)
			moveFront(10);

	}else if(!road2){
		openRoad=2;
		//cup1
		moveFront(7);
		turnLeft(70);
		turnRight(70);
		//cup1
		//recentering
		moveBack(25);
		moveFront(20);
		turnRight(20);
		turngyropos(800);
		moveFront(20);

		followLineEncoder(600);
		//cup2
		turngyropos(800);

		moveFront(10);

		turnLeft(90);

		if(SensorValue[sonarSensor]>20)
			moveFront(7);

		turnLeft(70);
		turnRight(70);
		moveBack(5);
		turnLeft(90);
		//cup2
		//recenter
		turngyropos(2700);
		moveFront(10);
		followLineEncoder(1500);
		turngyropos(2800);
		moveFront(30);
		//cup3
		turnRight(90);
		moveFront(6);
		turnLeft(70);
		turnRight(70);
		moveBack(6);
		turnRight(90);
		//cup3
		//recenter
		turngyropos(900);
		moveFront(10);
		followLineEncoder(500);
		turngyropos(900);
		moveFront(20);
		turngyropos(1800);

		moveFront(40);
		turnLeft(90);
		if(SensorValue[sonarSensor]>30){
			while(SensorValue[sonarSensor]>30){
				moveFront(1);
			}
		}else if(SensorValue[sonarSensor]<30){
			while(SensorValue[sonarSensor]<30){
				moveBack(1);
			}
		}
		turngyropos(1800);
		moveFront(10);
		followLineEncoder(1000);
		turngyropos(1800);
		moveFront(20);
		while(SensorValue[sonarSensor]>150){
			moveFront(1);
		}
	}else if(!road3){
		openRoad=3;
		//cup1
		moveFront(6);
		turnRight(70);
		turnLeft(70);
		//cup1
		//recenter for line follow
		moveBack(30);
		moveFront(25);
		//compensating for turn
		turnRight(90);
		moveFront(10);
		followLineEncoder(1000);
		//cup 2
		//turning to positon 2 degress
		turngyropos(20);
		moveFront(5);

		turnLeft(70);
		turnRight(70);
		moveBack(2);
		//cup2
		//recenter
		turngyropos(900);
		moveFront(25);
		followLineEncoder(500);
		//cup3
		turngyropos(780);
		moveFront(37);
		turnLeft(90);
		moveFront(2);
		turnRight(75);
		turnLeft(75);
		moveBack(5);
		//cup3
		//reposition
		turngyropos(2700);
		moveFront(10);
		turnLeft(20);
		turngyropos(2700);
		moveFront(30);

		followLineEncoder(700);
		turnRight(10);
		followLineEncoder(900);
		turngyropos(2700);

		moveFront(25);

		turngyropos(1800);
		moveFront(50);
		turnLeft(90);
		if(SensorValue[sonarSensor]>35){
			while(SensorValue[sonarSensor]>35){
				moveFront(1);
			}
		}else if(SensorValue[sonarSensor]<35){
			while(SensorValue[sonarSensor]<35){
				moveBack(1);
			}
		}
		turngyropos(1800);
		followLineEncoder(1300);
		turngyropos(1800);
		while(SensorValue[sonarSensor]>150){
			moveFront(1);
		}

	}


	//final
	moveFront(20);
	if(openRoad==1){
		if((startPosition==2)||(startPosition==1)){
			turnRight(90);
			moveFront(10);
			if(startPosition==2){
				followLineEncoder(900);
				moveFront(10);
			}else{
				followLineEncoder(1900);
				moveFront(20);
			}
			turnLeft(90);
		}
		turngyropos(1800);

		moveFront(30);

		followLineEncoder(750);
		turngyropos(1800);
		turnRight(180);
		moveBack(45);
	}else if(openRoad ==2){
		if((startPosition==3)||(startPosition==1)){
			if(startPosition==3){
				turnLeft(90);
			}else{
				turnRight(90);
			}
			followLineEncoder(700);
			moveFront(40);
			turngyropos(1800);
		}
		moveFront(40);
		followLineEncoder(700);
		turngyropos(1800);
		turnRight(180);
		moveBack(35);

	}else if(openRoad ==3){
		if((startPosition==2)||(startPosition==3)){
			 turnLeft(90);
			 moveFront(30);
			if(startPosition==2){
				followLineEncoder(800);
				moveFront(10);
			}else{
				followLineEncoder(1900);
				moveFront(10);
			}
			turngyropos(1800);
		}
		moveFront(40);
		followLineEncoder(700);
		turngyropos(1800);
		turnRight(180);
		moveBack(35);
	}
}
//++++++++++++++++++++d++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
