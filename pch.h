#pragma once

// gl 헤더
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

// glm 헤더
#include <gl/glm/glm.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtx/vector_angle.hpp>

// STL 헤더
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <memory>
#include <algorithm>

using int32 = __int32;
using int64 = __int64;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct FLOAT2 {
	float x;
	float y;
};

struct FLOAT3 {
	float x;
	float y;
	float z;
};

using float2 = FLOAT2;
using float3 = FLOAT3;

// 정점의 정보를 담을 구조체 정의
struct Vertex {
	float3 position;
	float3 color;
};

// 생성할 윈도우의 정보를 담을 구조체 정의
struct WindowInfo {
	int x;
	int y;
	uint32 width;
	uint32 height;
	float fWidth;
	float fHeight;
	std::string windowTitle;
};

extern std::unique_ptr<class Game> game;