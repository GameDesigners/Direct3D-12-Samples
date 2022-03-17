#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <Windows.h>

namespace DirectX3DRenderer{
	class GameTimer
	{
	public:
		GameTimer();

		float TotalTime() const;
		float DeltaTime() const;

		void Reset();   //���ü�ʱ����ͨ������Ϣѭ��֮ǰ���á�
		void Start();   //ȡ����ʱ����ͣ
		void Stop();    //��ʱ����ͣ
		void Tick();    //��ÿһ֡�е��ã���Ϸѭ���е��ã�

	private:
		double mSecondsPerCount;
		double mDeltaTime;
		
		__int64 mBaseTime;
		__int64 mPausedTime;
		__int64 mStopTime;
		__int64 mPrevTime;
		__int64 mCurrTime;

		bool mStopped;
	};
}
#endif // !GAMETIMER_H

