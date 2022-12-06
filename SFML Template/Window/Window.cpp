#include "Window.h"

Window::Window()
{
	initWindow();

	c1 = Camera(sf::Vector2f(window->getSize()), sf::Vector3f(0, 0, 3));

	cameraPaused = false;

	c1.setMouseSensitivity(0.25f);
	c1.enableDepth();
	c1.setViewDistance(0.1f, 200.f);
	c1.setFOV(45);

	glDisable(GL_TEXTURE);
	glDisable(GL_LIGHTING);

	shader.loadFromFile("test.vs", "test.fs");

	//shader.setParameter("view", c1.getMatrixPtr());

	sf::Shader::bind(&shader);
}

Window::~Window()
{
	delete window;
	sf::Shader::bind(NULL);
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sf::Glsl::Mat4 view(glm::value_ptr(*c1.getViewPtr()));
	sf::Glsl::Mat4 proj(glm::value_ptr(*c1.getProjectionPtr()));
	sf::Glsl::Mat4 model(glm::value_ptr(*c1.getModelPtr()));
	shader.setUniform("view", view);
	shader.setUniform("projection", proj);
	shader.setUniform("model", model);
	
	
	GLfloat cube[] =
	{
		//POSITION				//COLOR
		0,		0,		0,		255,255,255,255,
		100,	0,		0,		255,255,255,255,
		100,	100,	0,		255,255,255,255,
		0,		100,	0,		255,255,255,255,

		0,		0,		0,		255,255,255,255,
		0,		0,		100,	255,255,255,255,
		0,		100,	100,	255,255,255,255,
		0,		100,	0,		255,255,255,255,

		0,		100,	0,		255,255,255,255,
		100,	100,	0,		255,255,255,255,
		100,	100,	100,	255,255,255,255,
		00,		100,	100,	255,255,255,255,

		100,	0,		0,		255,255,255,255,
		100,	0,		100,	255,255,255,255,
		100,	100,	100,	255,255,255,255,
		100,	100,	0,		255,255,255,255,

		0,		0,		0,		255,255,255,255,
		100,	0,		0,		255,255,255,255,
		100,	0,		100,	255,255,255,255,
		0,		0,		100,	255,255,255,255,

		0,		0,		100,	255,255,255,255,
		100,	0,		100,	255,255,255,255,
		100,	100,	100,	255,255,255,255,
		0,		100,	100,	255,255,255,255,
	};

	
	// Enable position and color vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 7 * sizeof(GLfloat), cube);
	glColorPointer(4, GL_FLOAT, 7 * sizeof(GLfloat), cube + 3);
	// Disable normal and texture coordinates vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawArrays(GL_QUADS, 0, 24);
	shader.setUniform("ourColor", sf::Glsl::Vec4(1,1,1,1));
	//shader.setUniform("texture", sf::Shader::CurrentTexture);

	window->display();
}

void Window::update()
{
	if (!cameraPaused)
	{
		c1.updateMovement(dt);
		c1.updateMouseMovement(window, dt);
		c1.update(dt);
	}
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					window->close();
					break;
				case sf::Keyboard::Tab:
					cameraPaused = cameraPaused ? false : true;
					if (!cameraPaused)
						c1.setLastMouse(sf::Vector2f(sf::Mouse::getPosition(*window)));
					break;
			}
			break;

		case sf::Event::MouseMoved:
			break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::Window(sf::VideoMode(600, 500), "SFML/OpenGL Template", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	window->setActive(true);
}
