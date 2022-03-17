#include "GameTimer.h"

DirectX3DRenderer::GameTimer::GameTimer() :
	mSecondsPerCount(0),
	mDeltaTime(-1.0),
	mBaseTime(0),
	mPausedTime(0),
	mPrevTime(0),
	mCurrTime(0),
	mStopTime(0),
	mStopped(false)
{
	/*
	 *   QueryPerformanceFrequency(__int64*)是操作系统的性能统计分辨率的函数
	 *   从参数(__int64*)中返回是每秒钟统计的次数
	 */
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}


/// <summary>
/// 返回从Reset()函数调用为起始时间到现在的总时间（不包含暂停时间）
/// </summary>
/// <returns></returns>
float DirectX3DRenderer::GameTimer::TotalTime() const
{
	if (mStopped)
		return static_cast<float>((mStopTime - mPausedTime - mBaseTime) * mSecondsPerCount);
	else
		return static_cast<float>((mCurrTime - mPausedTime - mBaseTime) * mSecondsPerCount);
}

/// <summary>
/// 返回帧与帧之间的时间差
/// </summary>
/// <returns></returns>
float DirectX3DRenderer::GameTimer::DeltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

/// <summary>
/// 重置计时器
/// </summary>
void DirectX3DRenderer::GameTimer::Reset()
{
	/*
	 *   QueryPerformanceCounter(__int64*)是操作系统的性能统计分辨率的函数
	 *   从参数(__int64*)中返回当前CPU计数值（可以用于代表时间）
	 */
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

/// <summary>
/// 计时器取消暂停
/// </summary>
void DirectX3DRenderer::GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);  //将暂停时间累加记录

		mPrevTime = startTime;
		mStopTime = 0;   //重置暂停时间
		mStopped = false;
	}
}

/// <summary>
/// 计时器暂停
/// </summary>
void DirectX3DRenderer::GameTimer::Stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		
		mStopTime = currTime;
		mStopped = true;
	}
}

/// <summary>
/// 游戏循环中的计时器调用
/// </summary>
void DirectX3DRenderer::GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0f;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;
	mPrevTime = mCurrTime;
	if (mDeltaTime < 0)
		mDeltaTime = 0.0f;  //修正(其实算异常了)
}