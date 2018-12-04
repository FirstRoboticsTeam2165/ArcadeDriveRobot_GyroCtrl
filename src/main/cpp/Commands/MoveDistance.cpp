/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/***************************************************************************** 
*  MoveDistance is set up to move robot a maximum distance of 400 inches 
*  forward and backward.
*  Maximum distance is changed in RightWheelEncoder Command.
*
*******************************************************************************/


#include "MoveDistance.h"

MoveDistance::MoveDistance(double distance, double speed, double timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::driveTrain.get());
  Requires(Robot::rightWheelEncoder.get());

  	m_distance = distance;  // set distance in inches
	  m_speed = fabs(speed);
	  m_timeout = timeout;
	  m_save_gyro_Kp = 0.0; // save drive train Kp 
    m_set_gyro_Kp = 0.05;  // set new drive train Kp to drive straight 
}

// Called just before this Command runs the first time
void MoveDistance::Initialize() {

  m_save_gyro_Kp = Robot::driveTrain->GetPID_Parm_Kp(); // save drive train gyroPID parm
  Robot::driveTrain->SetPID_Parm_Kp(m_set_gyro_Kp);

  Robot::rightWheelEncoder->ResetWheelEncoder();
  Robot::rightWheelEncoder->SetPID_InputRange(m_distance + sgn(m_distance)*50L); // 50 inches > travel distance
  Robot::rightWheelEncoder->SetDistanceSetPt(m_distance); // distance to travel
  Robot::rightWheelEncoder->SetPID_OutputRange(m_speed); // set max speed
  Robot::rightWheelEncoder->EnablePID();

  Robot::driveTrain->EnableGyroPID(); 
  Robot::driveTrain->ZeroAngle();
  Robot::driveTrain->ApplyWheelBrakes();

  SetTimeout(m_timeout);
}

// Called repeatedly when this Command is scheduled to run
void MoveDistance::Execute() {
  double encoderDist = Robot::rightWheelEncoder->GetEncoderDistance();
  double fabs_encoderDist = fabs(encoderDist);

  SmartDashboard::PutNumber("encoderDist_MoveDist",encoderDist ); 

  if((fabs_encoderDist <= 12.0) || (fabs_encoderDist >= (fabs(m_distance) -12.0))){
    Robot::rightWheelEncoder->SetPID_OutputRange(0.8*m_speed);
}
  else{
    Robot::rightWheelEncoder->SetPID_OutputRange(m_speed);
  }
  double m_pidout = Robot::rightWheelEncoder->PidOut();
  Robot::driveTrain->GyroArcadeDrive(-m_pidout); // negative input to move forward
}
// Make this return true when this Command no longer needs to run execute()
bool MoveDistance::IsFinished() { 
  if(IsTimedOut() || Robot::rightWheelEncoder->AtSetPt()) {
    Robot::driveTrain->NoGyroArcadeDrive(0.0, 0.0);
    return true;
  }
  return false; 
  }

// Called once after isFinished returns true
void MoveDistance::End() {
Robot::driveTrain->SetPID_Parm_Kp(m_save_gyro_Kp);
Robot::driveTrain->ZeroAngle();
Robot::rightWheelEncoder->DisablePID();
// Remember wheel brakes are set when leaving these command.
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveDistance::Interrupted() {
  End();
}

double MoveDistance::sgn(double x) {
if(x > 0.0L) return 1;
if(x < 0.0L) return -1;
return 0.0;
}


