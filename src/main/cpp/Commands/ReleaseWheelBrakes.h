#ifndef ReleaseWheelBrakes_H
#define ReleaseWheelBrakes_H

#include "../Robot.h"

class ReleaseWheelBrakes : public Command {
public:
	ReleaseWheelBrakes(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_time;
};

#endif  // ReleaseWheelBrakes_H
