#pragma once
#include "Command.h"

class InputHandler {
private:
	ICommand* pressKeyA_;
	ICommand* pressKeyD_;

public:
	ICommand* HandleInput();
	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveLeftCommand2PressKeyD();
};