#pragma once
#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "../Camera.h"

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateDt();
	void updateSFMLEvents();
private:
	void initWindow();
	
	sf::Clock dtClock, timeClock;
	double dt;

	sf::Window* window;
	sf::Event event;

	Camera c1;
	sf::Shader shader;

	bool cameraPaused;
};

