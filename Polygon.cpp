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
		m_indicies.push_back(i);
	}
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

Poly::~Poly() { }

Poly::Poly(const std::vector<glm::vec3> otherVertex, const glm::vec3& color) {
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init(); 

	auto endLoop{ otherVertex.size() };
	for (decltype(endLoop) i = 0; i < endLoop; ++i) {
		m_verticies.push_back(Vertex{ otherVertex[i], color });
		m_indicies.push_back(i);
	}
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

Poly::Poly(const Poly& other) {
	m_verticies = other.m_verticies;
	m_indicies = other.m_indicies;
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
}

Poly& Poly::operator=(const Poly& other) {
	m_verticies = other.m_verticies;
	m_indicies = other.m_indicies;
	m_graphicBuffer = std::make_unique<GraphicBuffers>();
	m_graphicBuffer->Init();
	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);
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

void Poly::SortCCW(std::vector<Vertex>& verticies) {
	Poly& my = *this;
	Vertex origin{ verticies[0] };
	std::function<bool(Poly&, const glm::vec3&, const glm::vec3, const glm::vec3&)> ccw{ &Poly::CCW };

	std::sort(verticies.begin(), verticies.end(), [&origin, &my, &ccw](const Vertex& v1, const Vertex& v2)->bool {
		bool rt{ ccw(my, origin.position, v1.position, v2.position) };
		if (rt) {
			return true;
		}
		else {
			return false;
		}
	});
}

void Poly::SortCCW(std::vector<glm::vec3>& verticies) {
	Poly& my = *this;
	glm::vec3 origin{ verticies[0] };
	std::function<bool(Poly&, const glm::vec3&, const glm::vec3, const glm::vec3&)> ccw{ &Poly::CCW };

	std::sort(verticies.begin(), verticies.end(), [&origin, &my, &ccw](const glm::vec3& v1, const glm::vec3& v2)->bool {
		std::pair<glm::vec2, glm::vec2> line{ origin, v1 };
		bool rt{ ccw(my, origin, v1, v2) };
		if (rt) {
			return true;
		}
		else {
			return false;
		}
		});
}

bool Poly::CutPolygon(const std::pair<glm::vec2, glm::vec2>& line, Poly& newPoly) {
	glm::vec2 start{ m_verticies[0].position };
	auto endLoop{ m_verticies.size() };

	std::vector<int> intersectionIndex{ };

	std::vector<glm::vec3> resultVector{ };
	for (decltype(endLoop) i = 1; i < endLoop; ++i) {
		glm::vec2 end{ m_verticies[i].position };

		// 만약 만나는 점이 있다면
		glm::vec3 result{ };
		std::pair<glm::vec2, glm::vec2> polygonLine{ start, end };
		if (!GetIntersectionPoint(start, end, line.first, line.second, result)) {
			// 마지막 라인을 검사했는데 교차하지 않는경우 이후 검사는 할 필요가 없음
			if (i == endLoop - 1) {
				break;
			}
		}
		else {
			// 교차 점이 있다면 추가
			resultVector.push_back(result);
		}

		// 정점들이 만드는 라인을 검사하는데 FAN으로 그리고 있어서 첫번째 정점과의 직선만 검사하고 있음
		// 따라서 아래에 있는 정점들 간의 직선에 대해서도 추가로 교차 검사를 해줌
		if (i < endLoop - 1) {
			glm::vec2 bottomStart{ m_verticies[i].position };
			glm::vec3 bottomEnd = m_verticies[i + 1].position;
			glm::vec3 bottomResult{ };
			decltype(polygonLine) bottomPolygonLine = { bottomStart, bottomEnd };
			if (!GetIntersectionPoint(bottomStart, bottomEnd, line.first, line.second, bottomResult)) {
				continue;
			}

			resultVector.push_back(bottomResult);
		}
	}



	if (resultVector.size() <= 1) {
		return false;
	}

	std::vector<glm::vec3> cwPoints{ };
	std::vector<uint32> cwIndex{ };

	std::vector<glm::vec3> ccwPoints{ };
	std::vector<uint32> ccwIndex{ };

	CW_CCWLinePoint(line, m_verticies, cwPoints, ccwPoints, cwIndex, ccwIndex);

	if (IsCWPoint(line, m_verticies[0])) {
		cwPoints.insert(cwPoints.end(), resultVector.begin(), resultVector.end());
		ccwPoints.insert(ccwPoints.end(), resultVector.begin(), resultVector.end());

		glm::vec3 color{ m_verticies[0].color };
		m_verticies.clear();
		for (auto& point : cwPoints) {
			m_verticies.push_back(Vertex{ point, glm::vec3{ 0.f, 0.f, 1.f } });
		}

		SortCCW(m_verticies);
		SortCCW(ccwPoints);

		newPoly = Poly{ ccwPoints, glm::vec3{ 1.f, 0.f, 0.f } };
	}
	else {
		cwPoints.insert(cwPoints.end(), resultVector.begin(), resultVector.end());
		ccwPoints.insert(ccwPoints.end(), resultVector.begin(), resultVector.end());

		glm::vec3 color{ m_verticies[0].color };
		m_verticies.clear();
		for (auto& point : ccwPoints) {
			m_verticies.push_back(Vertex{ point, glm::vec3{ 0.f, 0.f, 1.f } });
		}

		SortCCW(m_verticies);
		SortCCW(cwPoints);

		newPoly = Poly{ cwPoints, glm::vec3{ 1.f, 0.f, 0.f } };
	}

	m_indicies.clear();
	auto endLoop2{ m_verticies.size() };
	for (decltype(endLoop) i = 0; i < endLoop2; ++i) {
		m_indicies.push_back(i);
	}

	m_graphicBuffer->SetVerticies(m_verticies);
	m_graphicBuffer->SetIndexBuffer(m_indicies);

	return true;
}

bool Poly::IsCWPoint(const std::pair<glm::vec2, glm::vec2>& line, const Vertex& point) {
	glm::vec3 pointA{ line.first, 0.f };
	glm::vec3 lineVector{ glm::vec3{ line.second, 0.f } - glm::vec3{ line.first, 0.f } };
	glm::vec3 pointVector{ point.position - pointA };

	glm::vec3 crossVector = glm::cross(lineVector, pointVector);
	if (crossVector.z > 0.f) {
		return true;
	}
	return false;
}

bool Poly::IsCCWPointVertex(const std::pair<glm::vec2, glm::vec2>& line, const Vertex& point) {
	glm::vec3 pointA{ line.first, 0.f };
	glm::vec3 lineVector{ glm::vec3{ line.second, 0.f } - glm::vec3{ line.first, 0.f } };
	glm::vec3 pointVector{ point.position - pointA };

	glm::vec3 crossVector = glm::cross(lineVector, pointVector);
	if (crossVector.z < 0.f) {
		return true;
	}
	return false;
}

bool Poly::CCW(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) {
	glm::vec3 v1{ p2 - p1 };
	glm::vec3 v2{ p3 - p1 };
	if (glm::cross(v1, v2).z > 0.f) {
		return true;
	}
	else {
		return false;
	}
}

void Poly::CW_CCWLinePoint(const std::pair<glm::vec2, glm::vec2>& line, std::vector<Vertex>& points,
	std::vector<glm::vec3>& cwPoints, std::vector<glm::vec3>& ccwPoints, std::vector<uint32>& cwIndex, std::vector<uint32>& ccwIndex) {
	
	auto endLoop{ points.size() };
	glm::vec3 pointA{ line.first, 0.f };
	glm::vec3 lineVector{ glm::vec3{ line.second, 0.f } - glm::vec3{ line.first, 0.f } };
	for (auto i = 0; i < endLoop; ++i) {
		glm::vec3 pointVector{ points[i].position - pointA };
		glm::vec3 crossVec = glm::cross(lineVector, pointVector);
		if (crossVec.z > 0.f) {
			cwPoints.push_back(points[i].position);
			cwIndex.push_back(i);
		}
		else {
			ccwPoints.push_back(points[i].position);
			ccwIndex.push_back(i);
		}
	}
}

void Poly::Update(float deltaTime) {
}

void Poly::Render() {
	m_graphicBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_graphicBuffer->Render();
}
