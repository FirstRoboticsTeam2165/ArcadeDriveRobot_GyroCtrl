

#include "RobotMap.h"
#include "WPILib.h"
#include "AHRS.h"
#include "ADXRS450_Gyro.h"


#if USES_NAVX_GYRO
std::shared_ptr<AHRS> RobotMap::navXGyro;
#else
std::shared_ptr<frc::ADXRS450_Gyro> RobotMap::analogGyro;
#endif

std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainFrontLeft;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainRearLeft;
std::shared_ptr<SpeedControllerGroup> RobotMap::m_left;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainFrontRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveTrainRearRight;
std::shared_ptr<SpeedControllerGroup> RobotMap::m_right;
std::shared_ptr<DifferentialDrive> RobotMap::diffDrive;
std::shared_ptr<Encoder> RobotMap::rightWheelEncoderDevice;
std::shared_ptr<DoubleSolenoid> RobotMap::pneumaticShiftCyl;

//std::shared_ptr<MecanumDrive> RobotMap::m_mecanumDrive;;

void RobotMap::init() {

// Assign a shared_ptr to an object formed from software libraries, e.g., makes pneumaticShift point to new DoubleSolenoid()
// WPI_TalonSRX arguments refer to CAN IDs for each wheel motor controller


#if USES_NAVX_GYRO
    navXGyro.reset(new AHRS(SPI::Port::kMXP));
#else
	analogGyro.reset(new frc::ADXRS450_Gyro());
#endif

    driveTrainFrontLeft.reset(new WPI_TalonSRX(FRONTLEFT));
    driveTrainRearLeft.reset(new WPI_TalonSRX(REARLEFT));
    
    m_left.reset(new SpeedControllerGroup(*driveTrainFrontLeft, *driveTrainRearLeft));

    driveTrainFrontRight.reset(new WPI_TalonSRX(FRONTRIGHT));
    driveTrainRearRight.reset(new WPI_TalonSRX(REARRIGHT));
    
    m_right.reset(new SpeedControllerGroup(*driveTrainFrontRight, *driveTrainRearRight));
    diffDrive.reset(new DifferentialDrive(*m_left, *m_right));


// 1, 2 DIO slots, 3rd argument - reverse direction, 4th argument samples per pulse cycle
    rightWheelEncoderDevice.reset(new Encoder(RT_TRANS_ENCODER_CH_A, RT_TRANS_ENCODER_CH_B, true, Encoder::k4X));

     pneumaticShiftCyl.reset(new DoubleSolenoid(TRANS_FWD_CH_0, TRANS_REV_CH_1) ); // PCM IDs 0, 1 for transmission shifter


//---------------------------------------------------------------------------------------
//   use if Mecanum drive is used on robot
//   m_mecanumDrive.reset(new MecanumDrive(*driveTrainFrontLeft, *driveTrainRearLeft,
//    		*driveTrainFrontRight, *driveTrainRearRight));

    diffDrive->SetSafetyEnabled(false);
    diffDrive->SetExpiration(0.5);   // sets motor timeout @ 500 ms

}
