#pragma once

#include "SDL.h"

class InputManager {
public:
	InputManager();
	~InputManager();

	int2 m_mouseCoord;
	bool m_mousePressed;
	bool m_mouseReleased;
	bool m_mouseMoved;

	void getInput();
};