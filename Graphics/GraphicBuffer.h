#pragma once

// VAO, VBO, EBO를 바인딩해서 삼각형을 그려줄 클래스
class GraphicBuffers {
public:
	GraphicBuffers();
	~GraphicBuffers();

private:
	// Vertex Buffer Object ID
	uint32 m_vertexBuffer{ };

	// Vertex Array Object ID
	uint32 m_vertexArray{ };

	size_t m_vertexDataSize{ };
	size_t m_indexDataSize{ };

	// 그리기 모드 점, 선, 삼각형 등
	// default값은 삼각형(생성자에서 설정)
	uint32 m_drawMode{ };

	// 모델 변환 행렬 변수의 위치 저장
	uint32 m_modelTransformLocation{ };

public:
	void Init();

	void SetTransformMat(glm::mat4& trans);
	void SetTransformMat(glm::mat4&& trans);

	void SetVerticies(const std::vector<Vertex>& verticies);

	void Render();
};