#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	class LaserLockOnScript :
		public MonoBehavior
	{
    public:
        LaserLockOnScript(GameObject* _pBoss);
        virtual ~LaserLockOnScript() = default;

        virtual void Initialize() override;
        virtual void FixedUpdate() override;

        virtual Component* Clone(GameObject* _pGameObject);

    public:
        void CreateMarker();

    private:
        float mFlipWidth;

        std::queue<Vec3> mPlayerPath;
        TimerObject mDuration;
        TimerObject mDeleteTimer;
        TimerObject mScaleTimer;
        GameObject* mpBoss;

        TimerObject mStartDuration;
        bool mbHitFlag;

        GameObject* mpMarker;

        bool mbInitAngleSetting;
	};
}


