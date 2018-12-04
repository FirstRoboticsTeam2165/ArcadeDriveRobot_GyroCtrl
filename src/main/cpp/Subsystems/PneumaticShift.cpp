/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PneumaticShift.h"
#include "../RobotMap.h"

PneumaticShift::PneumaticShift() : Subsystem("PneumaticShift") {

gearShift = RobotMap::pneumaticShiftCyl;
}

void PneumaticShift::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void PneumaticShift::HighGear() {
  gearShift->Set(frc::DoubleSolenoid::kForward); // Low gear ratio - faster robot
}

void PneumaticShift::LowGear() {
  gearShift->Set(frc::DoubleSolenoid::kReverse); // High gear ratio - slower robot
}
