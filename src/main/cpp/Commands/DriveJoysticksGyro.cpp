#include "DriveJoysticksGyro.h"
#include "../OI.h"
#include "math.h"
#include "SmartDashboard/SmartDashboard.h"
#include "../RobotMap.h"  // needed for reference to macro in RobotMap.h

bool DriveJoysticksGyro::m_setGyroOff = false; // set true disables gyro control

DriveJoysticksGyro::DriveJoysticksGyro() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());


	Requires(Robot::driveTrain.get());

	curTransState = false;  // the use of curTransState and prevTransState ensures that
	prevTransState = false; // the transition from rotation to gyro control occurs on falling edge
							// of the rotation joystick value
	noGyroReset = false;
	//m_pidout = 0.0;

	setZ_Gain = 0.75;


}

// Called just before this Command runs the first time
void DriveJoysticksGyro::Initialize() {

	curTransState = false;
	prevTransState = false;
	noGyroReset = false;
	Robot::driveTrain->ZeroAngle();
	Robot::driveTrain->SetAngleSetPt(0.0);
	Robot::driveTrain->EnableGyroPID();
	Robot::driveTrain->ReleaseWheelBrakes();

}

// Called repeatedly when this Command is scheduled to run
void DriveJoysticksGyro::Execute()
{
//	SmartDashboard::PutNumber("gyro angle", Robot::driveTrain->GetGyroAngle());

//double m_joyY = pow(Robot::oi->getJoystick0()->GetY(),3);  // forward/reverse - cubic weighting
//	double m_joyX = Robot::oi->getJoystick0()->GetX();   // slide right/left
    double m_joyY =  Robot::oi->getJoystick0()->GetY();  // forward/reverse
	double m_joyZ = - Robot::oi->getJoystick0()->GetZ();  // rotate CW/CCW


	if(Robot::oi->getJoystick0_Button2()->Get()) {m_joyZ = 0.0;}  // drive straight with no rotation under gyro control

	curTransState = fabs(m_joyZ) >= STRAIGHT_TOL;  // value of (joyZ >= Tolerance) turns off gyro control

	if(Robot::oi->getJoystick0_Button1()->Get() || m_setGyroOff) {curTransState = true;}  // press trigger to disengage gyro

	if(curTransState)
	{  // if false drive with gyro control

// set up for arcade drive
		Robot::driveTrain->NoGyroArcadeDrive(m_joyY, setZ_Gain*m_joyZ);
//		Robot::driveTrain->NoGyroMecanumDrive(m_joyX, - m_joyY, setZ_Gain*m_joyZ);
	}
	else if ((!curTransState && prevTransState) || noGyroReset)
	{
// else if true, drive with rot set 0.0 and check to see if abs(gyro rate) is < a MAXGYRORATE

	Robot::driveTrain->NoGyroArcadeDrive(m_joyY, 0.0f); // drive with zero rotation until gyro rate condition is met
//	Robot::driveTrain->NoGyroMecanumDrive(m_joyX, - m_joyY, 0.0f);

		if(fabs(Robot::driveTrain->GetAngleRate()) < MAXGYRORATE) //if < max rate reset gyro
		{
			Robot::driveTrain->ZeroAngle();
			noGyroReset = false;
		}
		else
		{ // go around again to see if gyro rate is < max rate condition
			noGyroReset = true;
		}

	}
	else
	{ // if none of the above are true drive with gyro controlling the rotation axis

		Robot::driveTrain->GyroArcadeDrive(m_joyY);
//		Robot::driveTrain->GyroMecanumDrive(m_joyX, - m_joyY);
	}
	prevTransState = curTransState;

}

// Make this return true when this Command no longer needs to run execute()
bool DriveJoysticksGyro::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveJoysticksGyro::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveJoysticksGyro::Interrupted() {

}
