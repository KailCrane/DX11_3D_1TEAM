#pragma once
#include "Component.h"
#include "Frustum.h"

namespace hm
{
    enum class ProjectionType
    {
        Orthographic,
        Perspective,
    };

	class Camera :
		public Component
	{
    public:
        Camera();
        virtual ~Camera();

        virtual void    Update() override;

        /* �����, ��������� ����Ѵ�.*/
        virtual void    FinalUpdate() override;

        void            SetProjectionType(ProjectionType eType) { meProjectionType = eType; }
        ProjectionType  GetProjectionType()   const { return meProjectionType; }

        void            SetCullingMask(LayerType _eLayerType, bool _bFlag);
        void            DisableAllCullingMask();
        void            EnableAllCullingMask();

        const Matrix& GetViewMatrix()       const { return mMatView; }
        const Matrix& GetProjectionMatrix() const { return mMatProjection; }

    public:
        void SortGameObject();

        /* Forward Rendering���� �׷��� ��ü���� �׷��ִ� �Լ� */
        void RenderForward();

        void RenderDeferred();

        void RenderParticle();


        const std::vector<GameObject*>& GetForwardObjects() { return mForwardObjects; }
        const std::vector<GameObject*>& GetDeferredObjects() { return mDeferredObjects; }

	private:
        ProjectionType meProjectionType;

        float           mNear;
        float           mFar;
        float           mFov;
        float           mScale;
        UINT32          mCullingMask;
        Matrix          mMatView;
        Matrix          mMatProjection;

        std::vector<GameObject*> mForwardObjects;
        std::vector<GameObject*> mDeferredObjects;
        std::vector<GameObject*> mParticleObjects;

        Frustum         mFrustumCulling;
	};
}

