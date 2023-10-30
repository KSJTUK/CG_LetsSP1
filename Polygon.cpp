#include "pch.h"
#include "Polygon.h"
#include "Graphics\GraphicBuffer.h"

Poly::Poly() {
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();

	uint32 vertexSize{ static_cast<uint32>(glm::linearRand(3, 12)) };

	glm::vec3 firstPos{ -100.f, -100.f, 0.f };
	glm::vec3 randColor{ glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }) };

	float addAngle = 360.f / static_cast<float>(vertexSize);
	float angle = 0.f;
	for (decltype(vertexSize) i = 0; i < vertexSize; ++i) {
		glm::vec3 rotPos{ glm::rotate(firstPos, glm::radians(angle), glm::vec3{ 0.f, 0.f, 1.f }) };
		m_verticies.push_back(Vertex{ rotPos, randColor });
		angle += addAngle;
	}
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

Poly::~Poly() { }

Poly::Poly(const Poly& other) {
	m_verticies = other.m_verticies;
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

Poly& Poly::operator=(const Poly& other) {
	m_verticies = other.m_verticies;
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	return *this;
}

void Poly::Update(float deltaTime) {
}

void Poly::Render() {
	m_graphicBuffer->Render();
}
