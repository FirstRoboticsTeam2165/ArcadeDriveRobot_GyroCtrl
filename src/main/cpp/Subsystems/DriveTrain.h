
#pragma once
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotMap.h"
#include "AHRS.h"
#include "ctre/Phoenix.h"



/**
 *
 *
 * @author ExampleAuthor
 */
class DriveTrain: public Subsystem, public PIDOutput, PIDSource {
//Note: Here we declare PIDSource as a base class to DriveTrain.  PIDGet is defined within
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities

#if USES_NAVX_GYRO
	std::shared_ptr<AHRS> navX;
#else
	std::shared_ptr<frc::ADXRS450_Gyro> analGyro;
#endif

	std::shared_ptr<PIDController> gyroPid;
	std::shared_ptr<WPI_TalonSRX> frontLeftCntrl;
	std::shared_ptr<WPI_TalonSRX> rearLeftCntrl;
	std::shared_ptr<WPI_TalonSRX> frontRightCntrl;
	std::shared_ptr<WPI_TalonSRX> rearRightCntrl;
	std::shared_ptr<DifferentialDrive> robotDrive;

//	std::shared_ptr<MecanumDrive> m_mecanum;

	static double Kp1;
	static double Ki1;
	static double Kd1;

	double m_rotate = 0.0;

	void PIDWrite(double) override;  // pure virtual function of PIDOut
	double PIDGet() override;  // pure virtual function of PIDSource

public:
	DriveTrain();
	void InitDefaultCommand();

	void NoGyroArcadeDrive(double, double);
	void GyroArcadeDrive(double);

//	void NoGyroMecanumDrive(double, double, double);
//	void GyroMecanumDrive(double, double);

	double GetGyroAngle(); // rotation around z-axis
	double GetAngleRate(); // degrees/second
	void ZeroAngle();  // use to set angle to zero

	void ApplyWheelBrakes();  // set robot coasting
	void ReleaseWheelBrakes();  // brake when inputs to controllers are zero

	double PidOut();  // Output from PID controller
	bool AtSetPoint();
	void SetAngleSetPt(double angle);
	void ChangePID_Parm(double kp, double ki, double kd);
	void EnableGyroPID();
	void DisableGyroPID();

// Use these methods with only the navX_MXP gyro
	double GetPitchAngle();  // rotation about y-axis
	double GetRollAngle(); // rotation about x-axis
	double GetYawAngle();  // rotation about z-axis

};

