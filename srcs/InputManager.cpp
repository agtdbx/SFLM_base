#include <InputManager.hpp>

//**** INITIALISION ************************************************************
//---- Constructors ------------------------------------------------------------

InputManager::InputManager(void)
{
	this->updatePressedKey = false;

	for (int i = 0; i < 101; i++)
		this->keyStates[i] = KEY_UP;

	for (int i = 0; i < 5; i++)
		this->mouseStates[i] = KEY_UP;
}


InputManager::InputManager(const InputManager &obj)
{
	this->updatePressedKey = obj.updatePressedKey;

	for (int i = 0; i < 101; i++)
		this->keyStates[i] = obj.keyStates[i];

	for (int i = 0; i < 5; i++)
		this->mouseStates[i] = obj.mouseStates[i];
}

//---- Destructor --------------------------------------------------------------

InputManager::~InputManager()
{

}

//**** ACCESSORS ***************************************************************
//---- Getters -----------------------------------------------------------------

bool	InputManager::keyPressed(sf::Keyboard::Key key) const
{
	return (this->keyStates[key] == KEY_PRESS);
}


bool	InputManager::keyDown(sf::Keyboard::Key key) const
{
	return (this->keyStates[key] == KEY_DOWN || this->keyStates[key] == KEY_PRESS);
}


bool	InputManager::keyUp(sf::Keyboard::Key key) const
{
	return (this->keyStates[key] == KEY_UP);
}


bool	InputManager::mousePressed(sf::Mouse::Button button) const
{
	return (this->mouseStates[button] == KEY_PRESS);
}


bool	InputManager::mouseDown(sf::Mouse::Button button) const
{
	return (this->mouseStates[button] == KEY_DOWN || this->mouseStates[button] == KEY_PRESS);
}


bool	InputManager::mouseUp(sf::Mouse::Button button) const
{
	return (this->mouseStates[button] == KEY_UP);
}


bool	InputManager::mouseWheelUp(void) const
{
	return (this->mouseWheel == WHEEL_UP);
}


bool	InputManager::mouseWheelDown(void) const
{
	return (this->mouseWheel == WHEEL_DOWN);
}

//---- Setters -----------------------------------------------------------------

//---- Operators ---------------------------------------------------------------

InputManager	&InputManager::operator=(const InputManager &obj)
{
	if (this == &obj)
		return (*this);

	this->updatePressedKey = obj.updatePressedKey;

	for (int i = 0; i < 101; i++)
		this->keyStates[i] = obj.keyStates[i];

	for (int i = 0; i < 5; i++)
		this->mouseStates[i] = obj.mouseStates[i];

	return (*this);
}

//**** PUBLIC METHODS **********************************************************

void	InputManager::update(void)
{
	if (this->updatePressedKey)
	{
		for (int i = 0; i < 101; i++)
			if (this->keyStates[i] == KEY_PRESS)
				this->keyStates[i] = KEY_DOWN;

		for (int i = 0; i < 5; i++)
			if (this->mouseStates[i] == KEY_PRESS)
				this->mouseStates[i] = KEY_DOWN;

		this->updatePressedKey = false;
	}

	this->mouseWheel = WHEEL_NONE;
}


void	InputManager::listenEvent(sf::Event *event)
{
	// Key events
	if (event->type == sf::Event::KeyPressed)
	{
		if (this->keyStates[event->key.code] != KEY_UP)
			return ;
		this->keyStates[event->key.code] = KEY_PRESS;
		this->updatePressedKey = true;
	}
	else if (event->type == sf::Event::KeyReleased)
	{
		this->keyStates[event->key.code] = KEY_UP;
	}

	// Mouse events
	else if (event->type == sf::Event::MouseButtonPressed)
	{
		this->mouseStates[event->key.code] = KEY_PRESS;
		this->updatePressedKey = true;
	}
	else if (event->type == sf::Event::MouseButtonReleased)
	{
		this->mouseStates[event->key.code] = KEY_UP;
	}
	else if (event->type == sf::Event::MouseWheelScrolled)
	{
		if (event->mouseWheelScroll.delta > 0)
			this->mouseWheel = WHEEL_UP;
		else
			this->mouseWheel = WHEEL_DOWN;
	}
}

//**** PRIVATE METHODS *********************************************************

