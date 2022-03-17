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
	 *   QueryPerformanceFrequency(__int64*)�ǲ���ϵͳ������ͳ�Ʒֱ��ʵĺ���
	 *   �Ӳ���(__int64*)�з�����ÿ����ͳ�ƵĴ���
	 */
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}


/// <summary>
/// ���ش�Reset()��������Ϊ��ʼʱ�䵽���ڵ���ʱ�䣨��������ͣʱ�䣩
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
/// ����֡��֮֡���ʱ���
/// </summary>
/// <returns></returns>
float DirectX3DRenderer::GameTimer::DeltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

/// <summary>
/// ���ü�ʱ��
/// </summary>
void DirectX3DRenderer::GameTimer::Reset()
{
	/*
	 *   QueryPerformanceCounter(__int64*)�ǲ���ϵͳ������ͳ�Ʒֱ��ʵĺ���
	 *   �Ӳ���(__int64*)�з��ص�ǰCPU����ֵ���������ڴ���ʱ�䣩
	 */
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

/// <summary>
/// ��ʱ��ȡ����ͣ
/// </summary>
void DirectX3DRenderer::GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);  //����ͣʱ���ۼӼ�¼

		mPrevTime = startTime;
		mStopTime = 0;   //������ͣʱ��
		mStopped = false;
	}
}

/// <summary>
/// ��ʱ����ͣ
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
/// ��Ϸѭ���еļ�ʱ������
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
		mDeltaTime = 0.0f;  //����(��ʵ���쳣��)
}