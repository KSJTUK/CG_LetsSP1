#include "pch.h"
#include "Graphics.h"
#include "GraphicBuffer.h"
#include "Shader.h"
#include "Polygon.h"

Graphics::Graphics() { }

Graphics::~Graphics() { }

bool Graphics::IsInited() const {
	return m_isInited;
}

void Graphics::SetWindowInfo(const WindowInfo& winInfo) {
	m_windowInfo = winInfo;

	SetPerspectiveMat();
}

void Graphics::SetPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	SHADER->UseProgram();
	float aspect = m_windowInfo.fWidth / m_windowInfo.fHeight;
	float halfFovy = m_fovy / 2.f;

	SHADER->SetPerspectiveMat(glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far));
	SHADER->UnUseProgram();
}

void Graphics::Init() {
	SHADER->Init();

	// 투영 변환 행렬 계산 및 전송
	SetPerspectiveMat();

	SHADER->UseProgram();
	SHADER->SetViewMat(glm::lookAt(m_eye, m_eye + m_at, m_up));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_testPoly.push_back(Poly{ });

	// 쉐이더 프로그램 사용 종료
	SHADER->UnUseProgram();

	m_isInited = true;
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Graphics::Render() {
	SHADER->UseProgram();

	for (auto& polygon : m_testPoly) {
		polygon.Render();
	}

	SHADER->UnUseProgram();
}