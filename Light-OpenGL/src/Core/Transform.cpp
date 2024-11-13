#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "ImGui/imgui.h"

Transform::Transform() :
	m_ParentModel(glm::mat4(1.0f)), m_Model(glm::mat4(1.0f)), m_Position(glm::vec2(0, 0)), m_Rotation(0.0f), m_Scale(glm::vec2(1.0f, 1.0f)), m_LinkScaleWithParent(false)
{
	m_Model = glm::translate(m_Model, glm::vec3(m_Position, 0.0f));
	m_Model = glm::rotate(m_Model, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::scale(m_Model, glm::vec3(m_Scale, 1.0f));
} 

Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale, bool linkedScale) :
	m_ParentModel(glm::mat4(1.0f)), m_Model(glm::mat4(1.0f)), m_Position(position), m_Rotation(rotation), m_Scale(scale), m_LinkScaleWithParent(linkedScale)
{
	m_Model = glm::translate(m_Model, glm::vec3(m_Position, 0.0f));
	m_Model = glm::rotate(m_Model, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::scale(m_Model, glm::vec3(m_Scale, 1.0f));
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModel()
{
	m_Model = glm::translate(m_ParentModel, glm::vec3(m_Position, 0.0f));
	m_Model = glm::rotate(m_Model, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::scale(m_Model, glm::vec3(m_Scale, 1.0f));

	return m_Model;
}
void Transform::DrawImGui(std::string uniqID)
{
	std::string header = "Transform Settings" + uniqID;
	if (ImGui::CollapsingHeader(header.c_str()))
	{
		ImGui::Checkbox(("Link Scale with Parent" + uniqID).c_str(), &m_LinkScaleWithParent);

		ImGui::Text("Position");
		ImGui::DragFloat2(("##Position" + uniqID).c_str(), &m_Position[0], 1.0f);

		ImGui::Text("Rotation");
		ImGui::SliderFloat(("##Rotation" + uniqID).c_str(), & m_Rotation, -PI, PI);

		ImGui::Text("Scale");
		ImGui::DragFloat2(("##Scale" + uniqID).c_str(), &m_Scale[0], 0.1f);
	}

}

glm::mat4 Transform::normalizeParentModel(glm::mat4 model)
{
	glm::mat4 normalized_model = model;

	normalized_model[0] = glm::normalize(normalized_model[0]);
	normalized_model[1] = glm::normalize(normalized_model[1]);
	normalized_model[2] = glm::normalize(normalized_model[2]);

	return normalized_model;
}


