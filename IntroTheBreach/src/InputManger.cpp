#include "InputManger.h"
#include "Engine.h"

int2 InputManager::m_mouseCoord = int2(0, 0);

bool InputManager::m_mouseMoved = false;

bool InputManager::m_mousePressed = false;
bool InputManager::m_mouseReleased = false;
string InputManager::m_mouseState = "up";

bool InputManager::m_keyDown = false;

bool InputManager::m_quit = false;

InputManager::InputManager() {
	m_event = SDL_Event();

	available_for_pressing = true;
	available_for_releasing = false;
}

InputManager::~InputManager() {
}

void InputManager::update() {
	m_mouseMoved = false;

	m_mousePressed = false;
	m_mouseReleased = false;

	m_keyDown = false;

	if (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
		case SDL_MOUSEMOTION:
			m_mouseMoved = true;
			SDL_GetMouseState(&m_mouseCoord.x, &m_mouseCoord.y);

			//std::cout << "MOUSE MOVED\n";

			break;

		case SDL_MOUSEBUTTONDOWN:
			if (available_for_pressing) {
				if (m_event.button.button == SDL_BUTTON_LEFT) {
					m_mousePressed = true;
					m_mouseState = "down";

					std::cout << m_mouseCoord.x << " " << m_mouseCoord.y << "\n";
					std::cout << screenToGridCoords(m_mouseCoord).x << " " << screenToGridCoords(m_mouseCoord).y << "\n\n\n";
					//std::cout << "MOUSE PRESSED\n";
				}

				available_for_pressing = false;
				available_for_releasing = true;
			}

			break;

		case SDL_MOUSEBUTTONUP:
			if (available_for_releasing) {
				m_mouseReleased = true;
				m_mouseState = "up";

				//std::cout << "MOUSE RELEASED\n";

				available_for_pressing = true;
				available_for_releasing = false;
			}

			break;

		case SDL_KEYDOWN:
			m_keyDown = true;

			//std::cout << "KEY PRESSED\n";

			break;

		case SDL_QUIT:
			m_quit = true;

			//std::cout << "DEATH\n";

			break;

		default:

			break;
		}
	}
}

button::button() {
	button_down = false;

	m_rect = SDL_Rect();
}

button::button(SDL_Rect rect) {
	button_down = false;

	m_rect = rect;
}

button::~button() {

}

bool button::collisionWithMouse()
{
	if (InputManager::m_mouseCoord.x < m_rect.x)
	{
		return false;
	}
	if (InputManager::m_mouseCoord.x + 1 > m_rect.x + m_rect.w)
	{
		return false;
	}
	if (InputManager::m_mouseCoord.y < m_rect.y)
	{
		return false;
	}
	if (InputManager::m_mouseCoord.y + 1 > m_rect.y + m_rect.h)
	{
		return false;
	}

	return true;
}

bool button::pressed() {
	if (!collisionWithMouse())
	{
		if (InputManager::m_mouseReleased)
		{
			button_down = false;
		}
		return false;
	}
	if (InputManager::m_mousePressed)
	{
		button_down = true;
		return false;
	}
	if (InputManager::m_mouseReleased)
	{
		if (button_down)
		{
			button_down = false;
			return true;
		}
		button_down = false;
	}
	return false;
}
