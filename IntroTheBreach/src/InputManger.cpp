#include "InputManger.h"

InputManager::InputManager() {
	m_mouseCoord.x = 0;
	m_mouseCoord.y = 0;
}

InputManager::~InputManager() {
}

void InputManager::getInput() {
	m_mousePressed = false;
	m_mouseReleased = false;

	SDL_Event m_event;
	while (SDL_PollEvent(&m_event)) {
		if (m_event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&m_mouseCoord.x, &m_mouseCoord.y);
			m_mouseMoved = true;
		}
		if (m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_LEFT) {
			m_mousePressed = true;
		}
		if (m_event.type == SDL_MOUSEBUTTONUP && m_event.button.button == SDL_BUTTON_LEFT) {
			m_mouseReleased = true;
		}
	
	}
}
