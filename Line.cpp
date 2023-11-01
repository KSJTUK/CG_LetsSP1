#include "pch.h"
#include "Line.h"
#include "Graphics\GraphicBuffer.h"

Line::Line(const std::pair<Vertex, Vertex>& startEnd) {
	m_verticies.push_back(startEnd.first);
	m_verticies.push_back(startEnd.second);
	m_indicies = { 0, 1 };

	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_graphicBuffer->SetDrawMode(GL_LINES);
}

Line::Line(const std::pair<glm::vec3, glm::vec3>& startEnd, const glm::vec3& color) {
	m_verticies.push_back(Vertex{ startEnd.first, color });
	m_verticies.push_back(Vertex{ startEnd.second, color } );
	m_indicies = { 0, 1 };

	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_graphicBuffer->SetDrawMode(GL_LINES);
}

Line::Line(const std::pair<glm::vec2, glm::vec2>& startEnd, const glm::vec3& color) {
	m_verticies.push_back(Vertex{ glm::vec3{ startEnd.first, 0.f }, color });
	m_verticies.push_back(Vertex{ glm::vec3{ startEnd.second, 0.f }, color });
	m_indicies = { 0, 1 };

	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_graphicBuffer->SetDrawMode(GL_LINES);
}

Line::Line(const std::vector<Vertex>& startEnd) {
	m_verticies = startEnd;
	m_indicies = { 0, 1 };

	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_graphicBuffer->SetDrawMode(GL_LINES);
}

Line::~Line() { }

void Line::Update(const glm::vec3& newEnd) {
	m_verticies[1].position = newEnd;
	m_graphicBuffer->SetVerticies(m_verticies);
}

void Line::Render() {
	m_graphicBuffer->Render();
}
