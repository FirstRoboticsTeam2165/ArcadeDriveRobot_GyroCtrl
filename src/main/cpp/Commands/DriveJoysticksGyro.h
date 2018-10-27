#ifndef DriveJoysticksGyro_H
#define DriveJoysticksGyro_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "math.h"
#include "WPILib.h"

class DriveJoysticksGyro : public Command {

private:
	const double STRAIGHT_TOL = 0.35;  // this value was originally set at 0.5
	const double MAXGYRORATE = 1.0;
	bool curTransState;
	bool prevTransState;
	bool noGyroReset;
	static bool m_setGyroOff;

	double setZ_Gain;


public:
	DriveJoysticksGyro();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveJoysticksGyro_H
