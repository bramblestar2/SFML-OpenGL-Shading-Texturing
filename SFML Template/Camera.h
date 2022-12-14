#pragma once
//OpenGL
#include <SFML/OpenGL.hpp>
#include <SFML/Window/Window.hpp>
//SFML
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

/// <summary>
/// If you are bringing this class into another project,
/// make sure to change the Context Settings of the window,
/// because if not, there won't be any depth and shapes
/// will overlap each other
/// </summary>
class Camera
{
public:
	Camera(const sf::Vector2f _Size = sf::Vector2f(), const sf::Vector3f _Cam_Position = sf::Vector3f());
	~Camera();

	void enableDepth();

	float getFOV() const { return fov; }
	float getYaw() const { return yaw; }
	float getPitch() const { return pitch; }
	float getMouseSensitivity() const { return mouseSensitivity; }
	glm::mat4* getViewPtr(); //for shaders
	glm::mat4* getProjectionPtr(); //for shaders
	glm::mat4* getModelPtr(); //for shaders
	glm::vec3 getCameraPosition() const { return cameraPos; }

	void setSize(const float _X, const float _Y);
	void setSize(const sf::Vector2f _Size);
	void setMouseSensitivity(const float _Sensitivity) { mouseSensitivity = _Sensitivity; }
	void setLastMouse(const sf::Vector2f _Last);
	
	void setFOV(const float _FOV);
	void setViewDistance(const float _Near, const float _Far);
	void setCameraSpeed(const float _Speed) { cameraSpeed = _Speed; }
	void setCameraPosition(const sf::Vector3f _Position);
	void setYaw(const float _Yaw) { yaw = _Yaw; updateDirection(); }
	void setPitch(const float _Pitch) { pitch = _Pitch; updateDirection(); }

	void move(const float _X, const float _Y, const float _Z) { move(sf::Vector3f(_X, _Y, _Z)); }
	void move(const sf::Vector3f _Direction);

	void update(const double _DT);
	void updateMatrix(); //Updates sfml's matrix
	void updateMouseMovement(sf::Window* window, const double _DT);
	void updateMovement(const double _DT);

private:
	void updateDirection();
	void updateView();

	sf::Vector2f cameraSize;
	//X > Near
	//Y > Far
	sf::Vector2f viewDistance;

	//Camera
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float cameraSpeed;
	float fov;
	//

	//Mouse looking
	sf::Vector2f last;

	float mouseSensitivity;
	float yaw, pitch;
	bool firstMouse;
	//
};

