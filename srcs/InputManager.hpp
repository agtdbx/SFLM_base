#ifndef INPUTMANAGER_HPP
# define INPUTMANAGER_HPP

# include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager(void);
	InputManager(const InputManager &obj);
	~InputManager();

	bool	keyPressed(sf::Keyboard::Key key) const;
	bool	keyDown(sf::Keyboard::Key key) const;
	bool	keyUp(sf::Keyboard::Key key) const;

	bool	mousePressed(sf::Mouse::Button button) const;
	bool	mouseDown(sf::Mouse::Button button) const;
	bool	mouseUp(sf::Mouse::Button button) const;
	bool	mouseWheelUp(void) const;
	bool	mouseWheelDown(void) const;

	InputManager	&operator=(const InputManager &obj);

	void	update(void);
	void	listenEvent(sf::Event *event);

private:
	enum KeyState
	{
		KEY_PRESS,
		KEY_DOWN,
		KEY_UP
	};

	enum MouseWleelState
	{
		WHEEL_NONE,
		WHEEL_UP,
		WHEEL_DOWN
	};

	bool			updatePressedKey;
	KeyState		keyStates[101];
	KeyState		mouseStates[5];
	MouseWleelState	mouseWheel;
};

#endif
