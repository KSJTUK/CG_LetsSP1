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

struct Vertex {
	float3 position;
	float3 color;
};

extern std::unique_ptr<class Game> game;