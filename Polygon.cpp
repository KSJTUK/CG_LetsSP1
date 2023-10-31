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

Poly::Poly(const std::vector<glm::vec3> otherVertex, const glm::vec3& color) {
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init(); auto endLoop{ otherVertex.size() };

	for (decltype(endLoop) i = 0; i < endLoop; ++i) {
		m_verticies.push_back(Vertex{ otherVertex[i], color });
	}
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

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

bool Poly::GetIntersectionPoint(const glm::vec2& ap1, const glm::vec2& ap2, const glm::vec2& bp1, const glm::vec2& bp2, glm::vec3& result) {
	constexpr float epsilonf{ glm::epsilon<float>() };

	float under{ ((bp2.y - bp1.y) * (ap2.x - ap1.x) - (bp2.x - bp1.x) * (ap2.y - ap1.y)) };
	if (glm::abs(under) <= epsilonf) {
		return false;
	}
	float _t{ ((bp2.x - bp1.x) * (ap1.y - bp1.y) - (bp2.y - bp1.y) * (ap1.x - bp1.x)) };
	float _s{ ((ap2.x - ap1.x) * (ap1.y - bp1.y) - (ap2.y - ap1.y) * (ap1.x - bp1.x)) };

	float t{ _t / under };
	float s{ _s / under };

	if (t <= 0.f or t >= 1.f or s <= 0.f or s >= 1.f) {
		return false;
	}

	if (glm::abs(t) <= epsilonf and glm::abs(s) <= epsilonf) {
		return false;
	}

	result.x = ap1.x + t * (ap2.x - ap1.x);
	result.y = ap1.y + t * (ap2.y - ap1.y);
	return true;
}

bool Poly::CutPolygon(const std::pair<glm::vec2, glm::vec2>& line, Poly& newPoly) {
	glm::vec2 start{ m_verticies[0].position };
	auto endLoop{ m_verticies.size() };

	std::vector<int> intersectionIndex{ };

	std::vector<glm::vec3> resultVector{ };
	for (decltype(endLoop) i = 1; i < endLoop; ++i) {
		glm::vec2 end{ m_verticies[i].position };

		glm::vec3 result{ };
		std::pair<glm::vec2, glm::vec2> polygonLine{ start, end };
		if (!GetIntersectionPoint(start, end, line.first, line.second, result)) {
			if (i == endLoop - 1) {
				return false;
			}
			//continue;
		}
		else {
			intersectionIndex.push_back(static_cast<int>(i));
			resultVector.push_back(result);
		}

		if (i < endLoop - 1) {
			glm::vec2 bottomStart{ m_verticies[i].position };
			glm::vec3 bottomEnd = m_verticies[i + 1].position;
			glm::vec3 bottomResult{ };
			decltype(polygonLine) bottomPolygonLine = { bottomStart, bottomEnd };
			if (!GetIntersectionPoint(bottomStart, bottomEnd, line.first, line.second, bottomResult)) {
				continue;
			}
			
			resultVector.push_back(bottomResult);
			if (resultVector.size() > 1) break;
		}
	}

	if (resultVector.size() <= 1) {
		return false;
	}

	glm::vec3 color = m_verticies[0].color;
	decltype(m_verticies) copyResult{ };
	for (auto& vec : resultVector) {
		copyResult.push_back(Vertex{ vec, color });
	}

	auto idxStart{ intersectionIndex.front() }, idxEnd{ intersectionIndex.back() };
	for (int i = idxStart; i <= idxEnd; ++i) {
		resultVector.insert(resultVector.begin(), m_verticies[i].position);
	}

	for (int i = idxStart; i <= idxEnd; ++i) {
		m_verticies.erase(m_verticies.begin() + idxStart, m_verticies.begin() + idxEnd);
		m_verticies.insert(m_verticies.end(), copyResult.rbegin(), copyResult.rend());
	}

	m_graphicBuffer->SetVerticies(m_verticies);

	newPoly = Poly{ resultVector, color };
	return true;
}

void Poly::Update(float deltaTime) {
}

void Poly::Render() {
	m_graphicBuffer->Render();
}
