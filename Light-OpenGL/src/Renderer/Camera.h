#pragma once
#include"glm.hpp"

class Camera
{
private:
	glm::mat4 m_View;
	glm::vec3 m_Pos;
public:
	Camera();
	~Camera();
	void MoveCamera(glm::vec3 movement);
	inline glm::mat4 GetView() const { return m_View; };
};

