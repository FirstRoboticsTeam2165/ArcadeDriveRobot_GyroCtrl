/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

/* 10/5/2018 
*
*  This project was derived from a 2018 project using Mecanum Robot Drive.
*  Location: workspace2018_2/Robot_Framework_Ref2_2018
*  Re-located and re-named as: 2019_Test_Arcade/ArcadeDrive_2018
*  Edited code in Eclipse from Mecanum Drive to Arcade Drive
*  Upgraded to VScode IDE and re-located to: 2019_Test_Arcade_VScode/Arcade_2018
*  Obtained a sucessful build 10/5/18 
*  See 2019 FIRST Robotics Notebook page 11-12 for additional details
*
*  This project uses:
*  	- a single joystick, Logitech Extreme 3D PRO, is used with gyro control to drive in a
*  		straight line.
*  	- a arcade drive train with four motors
*  	- an option to select one of two gyros by setting #define in RobotMap.h to
*  		USES_NAVX_GYRO 1 if navX_MXP gyro is used or setting it to USES_NAVX_GYRO 0 if
*  		ADXRS450 gyro is used.
*  del 10/5/18
*	- command has been included to drive a specified distance (by encoder) in a 
*	    straight line controlled by gyro. The teleop version of this command is
*		initiated by button 5 on joystick.
*	- a two speed transmission is controlled by pneumatic accuators.  Button 3 shifts to high
*		speed, and Button 4 shifts to Low speed.
*	- a simple autonomous routine is selected by setting DB/Button 0 = 1 on the DriverStation.	   - 
*	- code for usb camera added in Robot.cpp
*
*  del 12/3/18
*********************************************************************************************************
*/
#include "Robot.h"

// 	static smart pointers to provide access to the various Commands,
//  e.g., see: Requires(Robot::driveTrain.get()); and Robot::driveTrain->GetFL_MotorCurrent();
	std::shared_ptr<DriveTrain> Robot::driveTrain = nullptr;
	std::shared_ptr<RightWheelEncoder> Robot::rightWheelEncoder = nullptr;
	std::shared_ptr<PneumaticShift> Robot::pneumaticShift = nullptr;
	std::unique_ptr<OI> Robot::oi;


void Robot::RobotInit() {
	RobotMap::init();
//  Set up usb and axis cameras
//	CameraServer::GetInstance()->StartAutomaticCapture();  // usb camera plugged into roboRIO
//	CameraServer::GetInstance()->AddAxisCamera("axis-camera.local"); // axis camera plugged into radio
	cs::UsbCamera m_camera = CameraServer::GetInstance()->StartAutomaticCapture();  // usb camera plugged into roboRIO
	m_camera.SetExposureManual(50);
	m_camera.SetResolution(320,240);
	
// Create an instance of Subsystem - will get an error until the Subsystem classes are created in a Subsystems file
//  reset(p) deletes previous ptr (if there is one) and acquires new ptr to object, e.g., a pointer to DriverTrain()
//  reset is a member function of shared_ptr therefore accessing it is done by the . access operator, not ->
//  both, e.g., driverTrain and reset are of the same type.  The same relation is true for the get function
//  since it is also a member of shared_ptr, i.e., shared_ptr::get()
//  This form of initialization is okay: std::shared_ptr<DriverTrain> driverTrain(new DriverTrain); , but
//  using reset() deletes ptr and object then resets a new ptr to an object.
//	Note: std::shared_ptr<DriverTrain>driverTrain = std::make_shared<DriverTrain>(); is a C++11 version -
// 	it compiles and could be used.

//  static smart pointers to objects of classes defined here
	driveTrain.reset(new DriveTrain());
	rightWheelEncoder.reset(new RightWheelEncoder());
	pneumaticShift.reset(new PneumaticShift());
	oi.reset(new OI());

// instantiate the command used for the autonomous period
	autonomousCommand.reset(new AutonomousCommand()); // where AutonomousCommand() is a Command class
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {  // supply methods and set variables to initiate autonomous period
//  Set Autonomous Rountine with Drive Station DB/Buttons


	GetButtonAuto();
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();  // set autonomous into Scheduler to run autonomous period
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run(); // Set teleop into Scheduler to run teleopPeriod
}

void Robot::TestPeriodic() {  // used LiveWindows when in Driver Station Test Mode
	//lw->Run();
}


//  Method to get DB/Buttons from Driver Station to run specific autonomous routines
void Robot::GetButtonAuto() {// method to select autonomous function
	int bval = 0;
	bool buttonstate = false;

	buttonstate = SmartDashboard::GetBoolean("DB/Button 0",false);
	if(buttonstate == true) bval |= 1;

	buttonstate = SmartDashboard::GetBoolean("DB/Button 1",false);
	if(buttonstate == true) bval |= 2;

	buttonstate = SmartDashboard::GetBoolean("DB/Button 2",false);
	if(buttonstate == true) bval |= 4;

	buttonstate = SmartDashboard::GetBoolean("DB/Button 3",false);
	if(buttonstate == true) bval |= 8;

	switch(bval)
	{
		case 0:
		{
			autonomousCommand.reset(new  AutonomousNoOp() );
		}
		break;
		case 1:
		{
			autonomousCommand.reset(new MoveDistance(96.0, 0.6, 10.0));
		}
		break;

//Add other autonomous commands as needed here

		default:
		{
			autonomousCommand.reset(new AutonomousNoOp());
		}
		break;
	}
	return;
}


START_ROBOT_CLASS(Robot);

