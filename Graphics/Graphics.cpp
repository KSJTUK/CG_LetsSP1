#include "pch.h"
#include "Graphics.h"
#include "Shader.h"

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

	SHADER->UseProgram();

	// 투영 변환 행렬 계산 및 전송
	SetPerspectiveMat();

	SHADER->SetViewMat(glm::mat4{ 1.f });

	// 쉐이더 프로그램 사용 종료
	SHADER->UnUseProgram();

	m_isInited = true;
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Graphics::Render() {
	SHADER->UseProgram();

	glViewport(0, 0, m_windowInfo.width, m_windowInfo.height);

	SHADER->UnUseProgram();
}