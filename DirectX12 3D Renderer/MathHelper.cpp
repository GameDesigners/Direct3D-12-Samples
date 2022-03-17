#include "MathHelper.h"


const float DirectX3DRenderer::MathHelper::Pi = 3.1415926535f;

DirectX::XMFLOAT4X4 DirectX3DRenderer::MathHelper::Identity4x4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);