#pragma once

class Graphics {
public:
	Graphics();
	~Graphics();

private:
	bool m_isInited{ false };

	float m_deltaTime{ };

private:
	// 카메라 외부파라미터 (투영행렬을 생성할 떄 쓰일 변수들)
	float m_fovy{ 90.f }; // 수직 시야각

	// 스크린 화면의 크기를 알아내기 위한 WindowInfo객체 참조
	WindowInfo m_windowInfo{ }; // aspect(종횡비) = width / height

	float m_near{ 0.1f };           // 시야 절두체의 가까운 평면과의 거리
	float m_far{ 1000.f };           // 시야 절두체의 먼 평면과의 거리

	// 카메라 클래스를 만들기 않을 예정이므로 고정 값 사용
	const glm::vec3 m_eye{ 0.f, 0.f, 1000.f };
	const glm::vec3 m_at{ 0.f, 0.f, -1.f };
	const glm::vec3 m_up{ 0.f, 1.f, 0.f };

	std::vector<class Poly> m_testPoly{ };


public:
	// getter
	bool IsInited() const;

	// setter
	void SetWindowInfo(const WindowInfo& winInfo);
	void SetPerspectiveMat();

	void MouseUp(const std::pair<glm::vec2, glm::vec2>&& mouseScreenCoord);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

