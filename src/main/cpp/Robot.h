

#pragma once

#include <TimedRobot.h>
#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "OI.h"

// Add #includes for Autonomous Commands here - e.g. #include "Commands/AutonomousNoOp.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/AutonomousNoOp.h"
#include "Commands/MoveDistance.h"

// Add #includes for Subsystems here - e.g. #includes "Subsystems/DriveTrain.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/RightWheelEncoder.h"
#include "Subsystems/pneumaticShift.h"


class Robot : public frc::TimedRobot {
public:
	std::unique_ptr<Command> autonomousCommand;  // declare unique ptr for autonomous routines
	static std::unique_ptr<OI> oi;

// Declare a Subsystem type shared_ptr for each Subsystem
//subsystem shared ptr provides access to methods in subsystems 
    static std::shared_ptr<DriveTrain> driveTrain; 
	static std::shared_ptr<RightWheelEncoder> rightWheelEncoder;
	static std::shared_ptr<PneumaticShift> pneumaticShift;

//  Virtual Classes to be defined
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

// method for using buttons on Driver Station to select autonomous instant
	void GetButtonAuto();
};

