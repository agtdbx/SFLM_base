#include <define.hpp>
#include <InputManager.hpp>

#include <iostream>
#include <SFML/Graphics.hpp>

static void	update(sf::RenderWindow *window, InputManager *inputManager);
static void	tick(sf::RenderWindow *window, const InputManager *inputManager);
static void	draw(sf::RenderWindow *window);

int main(void)
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML game base");
	window.setFramerateLimit(FPS_CAP);

	InputManager	inputManager;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		update(&window, &inputManager);
		tick(&window, &inputManager);
		draw(&window);
	}

	return (0);
}


static void	update(sf::RenderWindow *window, InputManager *inputManager)
{
	sf::Event event;

	inputManager->update();
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		else
			inputManager->listenEvent(&event);
	}
}


static void	tick(sf::RenderWindow *window, const InputManager *inputManager)
{
	static sf::Clock	clock;
	static int			nbCall = 0;
	static float		totalDelta = 0.0f;

	// Compute delta time
	float delta = clock.restart().asSeconds();

	// Display fps in title
	totalDelta += delta;
	nbCall++;
	if (totalDelta >= FPS_DISPLAY_UPDATE)
	{
		float avgDelta = totalDelta / (float)nbCall;
		window->setTitle(std::to_string(1.0f / avgDelta));
		totalDelta = 0.0f;
		nbCall = 0;
	}

	// Print space key pressed or down
	if (inputManager->keyPressed(sf::Keyboard::Space))
		std::cout << "Space pressed" << std::endl;
	else if (inputManager->keyDown(sf::Keyboard::Space))
		std::cout << "Space down" << std::endl;

	// Print right click pressed or down
	if (inputManager->mousePressed(sf::Mouse::Right))
		std::cout << "Right click pressed" << std::endl;
	else if (inputManager->mouseDown(sf::Mouse::Right))
		std::cout << "Right click down" << std::endl;

	// Print mouse wheel mouvement
	if (inputManager->mouseWheelUp())
		std::cout << "Mouse wheel up" << std::endl;
	else if (inputManager->mouseWheelDown())
		std::cout << "Mouse wheel down" << std::endl;
}


static void	draw(sf::RenderWindow *window)
{
	// clear the window with black color
	window->clear(sf::Color::Black);

	// draw everything here...
	// window->draw(...);

	// end the current frame
	window->display();
}
