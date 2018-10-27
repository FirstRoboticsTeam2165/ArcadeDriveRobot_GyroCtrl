

#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
//  shared pointers to joysticks
	std::shared_ptr<Joystick> joystick0;

// shared pointers to joystick buttons
	std::shared_ptr<JoystickButton> joystick0_Button1;
	std::shared_ptr<JoystickButton> joystick0_Button2;
	std::shared_ptr<JoystickButton> joystick0_Button3;
	std::shared_ptr<JoystickButton> joystick0_Button4;
	std::shared_ptr<JoystickButton> joystick0_Button5;
	std::shared_ptr<JoystickButton> joystick0_Button6;

// Joystick USB
	static constexpr int USB_0 = 0;

// Joystick Button Numbers
	static constexpr int BUTTON_1 = 1;   // Trigger
	static constexpr int BUTTON_2 = 2;
	static constexpr int BUTTON_3 = 3;
	static constexpr int BUTTON_4 = 4;
	static constexpr int BUTTON_5 = 5;
	static constexpr int BUTTON_6 = 6;

public:
	OI();
//declare method to provide public access to joysticks and buttons
	std::shared_ptr<Joystick> getJoystick0();
	std::shared_ptr<JoystickButton> getJoystick0_Button1();
	std::shared_ptr<JoystickButton> getJoystick0_Button2();
	std::shared_ptr<JoystickButton> getJoystick0_Button3();
	std::shared_ptr<JoystickButton> getJoystick0_Button4();
	std::shared_ptr<JoystickButton> getJoystick0_Button5();
	std::shared_ptr<JoystickButton> getJoystick0_Button6();
};

#endif
