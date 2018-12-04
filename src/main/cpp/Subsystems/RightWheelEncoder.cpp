/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RightWheelEncoder.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include <math.h>

// initialize PID parameters
  double RightWheelEncoder::Kp2{0.6};
  double RightWheelEncoder::Ki2{0.0};
  double RightWheelEncoder::Kd2{0.001};

RightWheelEncoder::RightWheelEncoder() : Subsystem("RightWheelEncoder") {

  // encoder initialization
    rightEncoder = RobotMap::rightWheelEncoderDevice;

  // to calculate Distance/Pulse (for wheel) = (pi*wheel dia)/(encoder rev/shaft rev)/
  // (encoder pulses/encoder rev)
  // transmission encoder - 250 pulse/rev, encoder rev/axial rev =6, wheel dia 6"
    rightEncoder->SetDistancePerPulse(0.01252); // only use pulses/rev,
  //                                             exclude sample mode 4X in calculation
    rightEncoder->SetSamplesToAverage(5);
    rightEncoder->Reset();
    
  // PID initialization
  
    rightEncoderPID.reset(new frc::PIDController(Kp2, Ki2, Kd2, this, this, 0.01));
    rightEncoderPID->SetContinuous(false);
    SetPID_InputRange(400.0);  //set greater than expected range
    SetPID_OutputRange(0.50);  // limits PID output to motor controller
    rightEncoderPID->Disable();  //initially disabled - must enable to work
    rightEncoderPID->SetPIDSourceType(PIDSourceType::kDisplacement);

    m_pidout = 0.0;
}

void RightWheelEncoder::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
 
// Put methods for controlling this subsystem
// here. Call these from Commands.

// Encoder methods

void RightWheelEncoder::ResetWheelEncoder() {
    rightEncoder->Reset();
}
 
 double RightWheelEncoder::GetEncoderDistance() {
    double distance = rightEncoder->GetDistance();
    frc::SmartDashboard::PutNumber("Right Encoder Dist", distance); //should be positive
    //                                                          when moving forward
    return distance;
 }

 double RightWheelEncoder::GetSpeed() {
   double speed = rightEncoder->GetRate();
   frc::SmartDashboard::PutNumber(" Right Wheel Speed", speed);
   return speed;
 }

 // PID methods

 void RightWheelEncoder::EnablePID() {
   rightEncoderPID->Enable();
 }

 void RightWheelEncoder::DisablePID() {
   rightEncoderPID->Disable();
 }

 void RightWheelEncoder::SetDistanceSetPt(double distance) {
   rightEncoderPID->SetSetpoint(distance); // units - inches
 }

 bool RightWheelEncoder::AtSetPt() {
   return (fabs(GetEncoderDistance() - rightEncoderPID->GetSetpoint()) < 1.0);
 }

void RightWheelEncoder::PIDWrite(double output)  { // get PID controller output
  m_pidout = output;
  frc::SmartDashboard::PutNumber("Right PID Output", m_pidout); // should be 
  //                                                postive moving forward
}

double RightWheelEncoder::PIDGet() {
  double m_distance = GetEncoderDistance(); 
    frc::SmartDashboard::PutNumber("Right PID Input", m_distance);
    return m_distance; 
}

double RightWheelEncoder::PidOut() { // public access to controller output
  return m_pidout; // value from PIDWrite above
}

void RightWheelEncoder::SetPID_OutputRange(double range) {
  double m_outRange = fabs(range);
  rightEncoderPID->SetOutputRange(-m_outRange, m_outRange);
}

void RightWheelEncoder::SetPID_InputRange(double range) {
  double m_inRange = fabs(range);
  rightEncoderPID->SetInputRange(-m_inRange, m_inRange);
}

void RightWheelEncoder::ChangePID_Parm(double p, double i, double d) {
  Kp2 = p, Ki2 = i, Kd2 = d;
}