/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>

class RightWheelEncoder : public frc::Subsystem, public PIDOutput, public PIDSource {
private:
// It's desirable that everything possible under private except
// for methods that implement subsystem capabilities

  std::shared_ptr<Encoder> rightEncoder;
  std::shared_ptr<PIDController> rightEncoderPID;

// PID parameters
  static double Kp2;
  static double Ki2;
  static double Kd2;

  double m_pidout;

public:
  RightWheelEncoder();
  void InitDefaultCommand() override;

// encoder methods
  void ResetWheelEncoder();
  double GetSpeed();
  double GetEncoderDistance();

// PID controller methods
  void PIDWrite(double) override;  // absolute virtual method in PIDOutput
  double PIDGet() override;  // absolute virtual method in PIDSource

  double PidOut(); // public access to PIDOut
  void EnablePID();
  void DisablePID();
  void SetDistanceSetPt(double);
  bool AtSetPt();
  void SetPID_OutputRange(double);
  void SetPID_InputRange(double);
  void ChangePID_Parm(double p, double i, double d);

};
