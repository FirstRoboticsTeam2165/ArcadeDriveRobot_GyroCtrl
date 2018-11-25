/* We used the PIDController Class so that we may change PID parameters if we choose.
 * PIDSubsystem does not uses const PID parameters.
 */




#include "DriveTrain.h"
#include "../Commands/DriveJoysticksGyro.h"
#include "math.h"
#include "SmartDashboard/SmartDashboard.h"


 	double DriveTrain::Kp1 = 0.075; // old 0.045
	double DriveTrain::Ki1 = 0.00;
	double DriveTrain::Kd1 = 0.001;


DriveTrain::DriveTrain() : Subsystem("DriveTrain") {


#if USES_NAVX_GYRO
	navX = RobotMap::navXGyro;
	navX->Reset(); // calibrate and zero gyro
#else
	analGyro = RobotMap::analogGyro;
	analGyro->Reset();
#endif

    frontLeftCntrl = RobotMap::driveTrainFrontLeft;
    rearLeftCntrl = RobotMap::driveTrainRearLeft;
    frontRightCntrl = RobotMap::driveTrainFrontRight;
    rearRightCntrl = RobotMap::driveTrainRearRight;
    robotDrive = RobotMap::diffDrive;

//    m_mecanum = RobotMap::m_mecanumDrive;

    gyroPid = RobotMap::driveTrainGyroPID;


    gyroPid.reset(new PIDController(Kp1, Ki1, Kd1 ,this, this, 0.02));  // this - a pointer to DriveTrain class
// 1st this refers to PIDOut and 2nd this refers to PIDSource - here both base-classes of DriveTain

    gyroPid->SetContinuous(false);
    gyroPid->SetAbsoluteTolerance(0.2);
    gyroPid->SetOutputRange(-0.4, 0.4);
    gyroPid->SetInputRange(-359.0, 359.0);
    gyroPid->SetContinuous(true);
    gyroPid->SetSetpoint(0.0);
    gyroPid->Enable();  // enable PID controller

// Set every Talon to reset the motor safety timeout. See CTRE MecanumDrive_Example
	frontLeftCntrl->Set(ControlMode::PercentOutput, 0);
	rearLeftCntrl->Set(ControlMode::PercentOutput, 0);
	frontRightCntrl->Set(ControlMode::PercentOutput, 0);
	rearRightCntrl->Set(ControlMode::PercentOutput, 0);

    frontLeftCntrl->Set(0.0);  // set speed of all motors to zero initially.
    rearLeftCntrl->Set(0.0);
    frontRightCntrl->Set(0.0);
    rearRightCntrl->Set(0.0);

    frontLeftCntrl->SetInverted(false);
    rearLeftCntrl->SetInverted(false);
    frontRightCntrl->SetInverted(false);
    rearRightCntrl->SetInverted(false);

    ApplyWheelBrakes();  // robot set in coast condition


}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveJoysticksGyro());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

	void DriveTrain::PIDWrite(double output){

		this->m_rotate = output;
		SmartDashboard::PutNumber("PID output", m_rotate);
	}

	double DriveTrain::PidOut()
	{
		return m_rotate;
	}

	void DriveTrain::SetAngleSetPt(double angle) {

		gyroPid->SetSetpoint(angle);
	}

	void DriveTrain::ChangePID_Parm(double kp, double ki, double kd) {

		DriveTrain::Kp1 = kp;
		DriveTrain::Ki1 = ki;
		DriveTrain::Kd1 = kd;
	}

	void DriveTrain::EnableGyroPID() {
		gyroPid->Enable();
	}

	void DriveTrain::DisableGyroPID() {
		gyroPid->Disable();
	}


	void DriveTrain::NoGyroArcadeDrive(double m_move, double m_rot) {

		robotDrive->ArcadeDrive(m_move, m_rot, true);
	}


	void DriveTrain::GyroArcadeDrive(double m_move)  {

		robotDrive->ArcadeDrive(m_move, m_rotate, true);
	}

/*
	void DriveTrain::NoGyroMecanumDrive(double m_slide, double m_move, double m_rot) {
		m_mecanum->DriveCartesian(m_slide, m_move, m_rot);
	}

	void DriveTrain::GyroMecanumDrive(double m_slide, double m_move) {
		m_mecanum->DriveCartesian(m_slide, m_move, m_rotate);
	}
*/

#if USES_NAVX_GYRO
// uses navX_MXP gyro
	double DriveTrain::PIDGet()  {
		double get_gyro = -(navX->GetAngle());
		frc::SmartDashboard::PutNumber("PID Input", get_gyro);
		return -(navX->GetAngle());
	}

	double DriveTrain::GetGyroAngle() {
		return navX->GetAngle();
	}

	bool DriveTrain::AtSetPoint()
	{

		return (fabs(navX->GetAngle() - gyroPid->GetSetpoint()) < 1.0);
	}

	double DriveTrain::GetAngleRate()  {  // degrees/second
		frc::SmartDashboard::PutNumber("GetAngleRate", navX->GetRate());
		return navX->GetRate();
	}

	void DriveTrain::ZeroAngle(){

		navX->ZeroYaw();
	}

	double DriveTrain::GetYawAngle()
	{
		return navX->GetYaw();
	}

	double DriveTrain::GetPitchAngle() {  // rotation around y-axis

		return navX->GetPitch();
	}

	double DriveTrain::GetRollAngle() {

		return navX->GetRoll();
	}
#else
// uses ADXRS450_Gyro
	double DriveTrain::PIDGet()  {
		double get_gyro = analGyro->GetAngle();
		SmartDashboard::PutNumber("PID Input", get_gyro);
		return -analGyro->GetAngle();
	}

	void DriveTrain::ZeroAngle(){

		analGyro->Reset();
	}

	double DriveTrain::GetAngleRate()  {  // degrees/second

		return analGyro->GetRate();
	}

#endif

	void DriveTrain::ApplyWheelBrakes() {
		frontLeftCntrl->SetNeutralMode(NeutralMode::Brake);
		rearLeftCntrl->SetNeutralMode(NeutralMode::Brake);
		frontRightCntrl->SetNeutralMode(NeutralMode::Brake);
		rearRightCntrl->SetNeutralMode(NeutralMode::Brake);
	}

	void DriveTrain::ReleaseWheelBrakes() {

		frontLeftCntrl->SetNeutralMode(NeutralMode::Coast);
		rearLeftCntrl->SetNeutralMode(NeutralMode::Coast);
		frontRightCntrl->SetNeutralMode(NeutralMode::Coast);
		rearRightCntrl->SetNeutralMode(NeutralMode::Coast);
	}


