#include "pch.h"
#include "GraphicBuffer.h"
#include "Shader.h"

GraphicBuffers::GraphicBuffers() : m_drawMode{ GL_LINE_LOOP } { }

GraphicBuffers::~GraphicBuffers() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void GraphicBuffers::Init() {
	// VAO 객체 생성 및 바인드
	// VBO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);

	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// 셰이더언어 파일에 있는 모델 변환 행렬 변수의 로케이션을 저장
	m_modelTransformLocation = glGetUniformLocation(SHADER->GetShaderProgramID(), "modelTransform");
	if (m_modelTransformLocation == -1) {
		assert(0);
	}
}


void GraphicBuffers::SetTransformMat(glm::mat4& trans) {
	glUniformMatrix4fv(m_modelTransformLocation, 1, GL_FALSE, glm::value_ptr(trans));
}

void GraphicBuffers::SetTransformMat(glm::mat4&& trans) {
	glUniformMatrix4fv(m_modelTransformLocation, 1, GL_FALSE, glm::value_ptr(trans));
}

void GraphicBuffers::SetVerticies(const std::vector<Vertex>& verticies) {
	m_vertexDataSize = static_cast<uint32>(verticies.size());
	// Vertex객체의 정보를 VBO에 넘겨줌
	glBufferData(GL_ARRAY_BUFFER, m_vertexDataSize * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);

	// location 0번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 1번에 Vertex객체의 color정보를 넘겨줌
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void GraphicBuffers::Render() {
	// shaderProgram 에서 UseProgram을 활성화 했다는 가정하에 수행
	glBindVertexArray(m_vertexArray);
	glDrawArrays(m_drawMode, 0, m_vertexDataSize);
	glBindVertexArray(0); // Array 바인드 해제
}
