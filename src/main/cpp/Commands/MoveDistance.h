/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <Commands/Subsystem.h>
#include "../Robot.h"
#include "SmartDashboard/SmartDashboard.h"
#include "math.h"

class MoveDistance : public frc::Command {

 private:
  double m_distance;
  double m_speed;
  double m_timeout;
  double m_save_gyro_Kp;
  double m_set_gyro_Kp;
  double sgn(double);
 public:
  MoveDistance(double, double, double);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
