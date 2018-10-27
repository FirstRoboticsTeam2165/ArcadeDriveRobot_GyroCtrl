// This autonomous class does nothing, but it should not affect the build.

#include "AutonomousNoOp.h"

AutonomousNoOp::AutonomousNoOp(): Command() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void AutonomousNoOp::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutonomousNoOp::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousNoOp::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutonomousNoOp::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousNoOp::Interrupted() {

}
