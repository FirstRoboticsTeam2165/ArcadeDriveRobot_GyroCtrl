

#include "RobotMap.h"
//#include "LiveWindow/LiveWindow.h"
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

//std::shared_ptr<MecanumDrive> RobotMap::m_mecanumDrive;

std::shared_ptr<PIDController> RobotMap::driveTrainGyroPID; // address via reset of PIDController is set in DriveTrain

void RobotMap::init() {

//    LiveWindow *lw = LiveWindow::GetInstance();
// Assign a shared_ptr to an object formed from software libraries, e.g., makes pneumaticShift point to new DoubleSolenoid()
// Numbers in CANTalon() arguments refer to CAN IDs for each wheel motor controller


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

//    m_mecanumDrive.reset(new MecanumDrive(*driveTrainFrontLeft, *driveTrainRearLeft,
//    		*driveTrainFrontRight, *driveTrainRearRight));

//    diffDrive->SetSafetyEnabled(false);
//    diffDrive->SetExpiration(0.5);   // sets motor timeout @ 500 ms

}
