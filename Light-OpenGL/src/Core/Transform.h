#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include<string>
constexpr auto PI = 3.14159265f;
class Transform 
{
private:
	glm::mat4 m_ParentModel;
	glm::mat4 m_Model;

	glm::vec2 m_Position;
	float m_Rotation;
	glm::vec2 m_Scale;

	bool m_LinkScaleWithParent;

public:
	Transform();
	Transform(glm::vec2 position, float rotation = 0.0f, glm::vec2 scale = glm::vec2(1.0f,1.0f), bool linkedScale = false);

	~Transform();

	inline void SetParentModel(const glm::mat4& parentModel) {
		m_ParentModel = m_LinkScaleWithParent ? parentModel : normalizeParentModel(parentModel); }

	inline void SetPosition(const glm::vec2& position)  { m_Position = position; }
    inline void SetRotation(float rotation) 
	{    
		while (rotation > PI) 
		{
			rotation -= 2 * PI;
		}
		while (rotation < -PI) 
		{
			rotation += 2 * PI;
		}
		m_Rotation = rotation;
	}
    inline void SetScale(const glm::vec2& scale) { m_Scale = scale; }

    inline const glm::mat4& GetParentModel() const { return m_ParentModel; }
    inline const glm::vec2& GetPosition() const { return m_Position; }
    inline float GetRotation() const { return m_Rotation; }
    inline const glm::vec2& GetScale() const { return m_Scale; }

	glm::mat4 GetModel();

	void DrawImGui(std::string uniqID);

private:
	glm::mat4 normalizeParentModel(glm::mat4 model);

};

