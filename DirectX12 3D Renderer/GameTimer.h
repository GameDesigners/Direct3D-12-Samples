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

		void Reset();   //重置计时器，通常在消息循环之前调用。
		void Start();   //取消计时器暂停
		void Stop();    //计时器暂停
		void Tick();    //在每一帧中调用（游戏循环中调用）

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

