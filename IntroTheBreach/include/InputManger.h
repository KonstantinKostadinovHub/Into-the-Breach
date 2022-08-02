#pragma once

#include "SDL.h"
#include "Engine.h"

class InputManager {
public:
	InputManager();
	~InputManager();

	SDL_Event m_event;

	static bool m_mouseMoved;
	static int2 m_mouseCoord;

	static bool m_mousePressed;
	static bool m_mouseReleased;
	static string m_mouseState;
	
	static bool m_keyDown;

	static bool m_quit;

	void update();

private:
	bool available_for_pressing;
	bool available_for_releasing;
};

struct button {
	button();
	button(SDL_Rect rect);
	~button();

	SDL_Rect m_rect;
	bool button_down;

	bool collisionWithMouse();
	bool pressed();
};