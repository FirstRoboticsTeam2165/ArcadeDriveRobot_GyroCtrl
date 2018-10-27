
#include "OI.h"


#include "SmartDashboard/SmartDashboard.h"

// add #include files for command that you create
#include "Commands/DriveJoysticksGyro.h"




OI::OI() {
    // Assign joystick pointer to an instance of the Joystick( ) class

    joystick0.reset(new Joystick(USB_0));  // Logitech Extreme 3D PRO assigned to DR joystick0

    // Assign joystickbutton pointers to buttons on joystick

    joystick0_Button1.reset(new JoystickButton(joystick0.get(), BUTTON_1));

    joystick0_Button2.reset(new JoystickButton(joystick0.get(), BUTTON_2));

    joystick0_Button3.reset(new JoystickButton(joystick0.get(), BUTTON_3));  // low gear ration - fast robot


    joystick0_Button4.reset(new JoystickButton(joystick0.get(), BUTTON_4));  // high gear ratio - slow robot


    joystick0_Button5.reset(new JoystickButton(joystick0.get(), BUTTON_5));


    joystick0_Button6.reset(new JoystickButton(joystick0.get(), BUTTON_6));

    // SmartDashboard Buttons

    SmartDashboard::PutData("DriveJoysticksGyro", new DriveJoysticksGyro());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());



}

	std::shared_ptr<Joystick> OI::getJoystick0() {return joystick0;}
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button1() {return joystick0_Button1;} // disengage gyro
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button2() {return joystick0_Button2;} // drive straight by gyro
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button3() {return joystick0_Button3;} // low gear ration - fast robot
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button4() {return joystick0_Button4;} // high gear ratio - slow robot
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button5() {return joystick0_Button5;}
	std::shared_ptr<JoystickButton> OI::getJoystick0_Button6() {return joystick0_Button6;} // shift by current
