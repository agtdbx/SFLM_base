#ifndef MENU_HPP
# define MENU_HPP

# include <SFML/Graphics.hpp>
# include <iostream>
# include <vector>

class Menu
{
public:
	Menu(sf::RenderWindow *window);
	~Menu( void );

	bool	run( void );

private:
	sf::RenderWindow	*window;
	bool	runMenu, returnValue;
	std::vector<int>	keyPress;

	void	input( void );
	void	tick( void );
	void	render( void );
};

#endif
