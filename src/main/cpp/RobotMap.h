


#pragma once

#define USES_NAVX_GYRO 1  // set to 1 if navX_MXP gyro is used, otherwise set to 0 if ADXRS450 is used

#include "ctre/Phoenix.h"
#include "WPILib.h"
#include "AHRS.h"
#include "ADXRS450_Gyro.h"


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {

public:
// Declares smart pointers to form objects (instances) of libraries classes (see WIPLib, CTRLib,navXMXP C++ Lib)
// and provides access to class objects in Subsystems, e.g. robotDrive = RobotMap::driveTrainArcade;
// (here robotDrive is a private version of driveTrainArcade) see Subsystem DriverTrain.cpp

#if USES_NAVX_GYRO  // set to 1 if navX_MXP gyro is used, otherwise set to 0 if ADXRS450 is used
	static std::shared_ptr<AHRS> navXGyro;

#else
	static std::shared_ptr<frc::ADXRS450_Gyro> analogGyro;

#endif

	static std::shared_ptr<WPI_TalonSRX> driveTrainFrontLeft;
	static std::shared_ptr<WPI_TalonSRX> driveTrainRearLeft;
	static std::shared_ptr<SpeedControllerGroup> m_left;
	static std::shared_ptr<WPI_TalonSRX> driveTrainFrontRight;
	static std::shared_ptr<WPI_TalonSRX> driveTrainRearRight;
	static std::shared_ptr<SpeedControllerGroup> m_right;
	static std::shared_ptr<DifferentialDrive> diffDrive;
	static std::shared_ptr<Encoder> rightWheelEncoderDevice;
	static std::shared_ptr<DoubleSolenoid> pneumaticShiftCyl;
 
	

//	static std::shared_ptr<MecanumDrive> m_mecanumDrive;
	
	
	static void init();

private:

	//	Mappings of IO channels relating the channel numbers to constructor arguments
	//  of the motor controllers, actuators and sensors.
	//    	TalonSRX CAN IO - Drive Motor Controllers
		static constexpr int FRONTLEFT = 3;  // check motor positions on two-speed transmission
		static constexpr int REARLEFT = 1;   // identify the front and back motor on each side with
		static constexpr int FRONTRIGHT = 4;  // the CAN IO numbers
		static constexpr int REARRIGHT = 2;

	//  	Pneumatic Actuator PCM IO Channels
		static constexpr int TRANS_FWD_CH_0 = 0; // IO channels for the transmission pnuematic shifter
		static constexpr int TRANS_REV_CH_1 = 1;

	// if using multiple modules, define both the port number and the module

	// 		DIO IO
		static constexpr int RT_TRANS_ENCODER_CH_A = 0;  // digital IO for right wheel encoder
		static constexpr int RT_TRANS_ENCODER_CH_B = 1;

};

