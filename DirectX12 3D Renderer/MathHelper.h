#ifndef MATHHELP_H
#define MATHHELP_H
#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

namespace DirectX3DRenderer {
	class MathHelper
	{
	public:

		/// <summary>
		/// 返回一个范围为[0,1)的随机浮点数
		/// </summary>
		inline static float RandF01()
		{
			return static_cast<float>(rand()) / (float)RAND_MAX;
		}

		/// <summary>
		/// 返回一个范围为[min,max)的随机浮点数
		/// </summary>
		inline static float RandF(float min, float max)
		{
			return min + RandF01() * (max - min);
		}

		/// <summary>
		/// 返回一个范围为[min,max)的随机整数
		/// </summary>
		inline static float Rand(int min, int max)
		{
			return min + rand() % (max - min + 1);
		}

		template<class T>
		static T Min(const T& a, const T& b)
		{
			return a < b ? a : b;
		}

		template<typename T>
		static T Clamp(const T& x, const T& low, const T& high)
		{
			return x < low ? low : (x > high ? high : x);
		}

		static DirectX::XMFLOAT4X4 Identity4x4;
		static const float Pi;
	};
}
#endif // !MATHHELP_H
