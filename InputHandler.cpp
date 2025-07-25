#include "InputHandler.h"
#include <Novice.h>
#include "Command.h"
#include "Player.h"

ICommand* InputHandler::HandleInput() {
	if (Novice::CheckHitKey(DIK_A)) {
		return pressKeyA_;
	}
	if (Novice::CheckHitKey(DIK_D)) {
		return pressKeyD_;
	}
	return nullptr;
}

void InputHandler::AssignMoveLeftCommand2PressKeyA() {
	ICommand* command = new MoveLeftCommand();
	this->pressKeyA_ = command;
}

void InputHandler::AssignMoveLeftCommand2PressKeyD() {
	ICommand* command = new MoveRightCommand();
	this->pressKeyD_ = command;
}