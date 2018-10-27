#ifndef AUTONOMOUSNOOP_H
#define AUTONOMOUSNOOP_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author del
 */
class AutonomousNoOp : public Command {
public:
	AutonomousNoOp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AUTONOMOUSNOOP_H
