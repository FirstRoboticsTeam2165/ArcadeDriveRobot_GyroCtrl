#include "ReleaseWheelBrakes.h"

ReleaseWheelBrakes::ReleaseWheelBrakes(double timeInSeconds) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	m_time = timeInSeconds;
}

// Called just before this Command runs the first time
void ReleaseWheelBrakes::Initialize() {
	SetTimeout(m_time);
}

// Called repeatedly when this Command is scheduled to run
void ReleaseWheelBrakes::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ReleaseWheelBrakes::IsFinished() {
	if(IsTimedOut()) {
		Robot::driveTrain->ReleaseWheelBrakes();
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ReleaseWheelBrakes::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReleaseWheelBrakes::Interrupted() {
	End();
}
