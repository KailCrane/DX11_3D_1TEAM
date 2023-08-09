#pragma once
#include "Component.h"

namespace hm
{
	class Camera;
	class Transform :
		public Component
	{
	public:
		Transform();
		virtual ~Transform();

	public:
		virtual void  Initialize() override;

		/* ���� ����� ������Ʈ�Ѵ� */
		virtual void  FinalUpdate() override;

		void  SetScale(const Vec3& _scale) { mScale = _scale; }
		void  SetRotation(const Vec3& _rotation);
		void  SetRotation(Axis _eAxis, float _degree);
		void  SetRotationExcludingColliders(const Vec3& _rotation);
		void  SetRotationExcludingColliders(Axis _eAxis, float _degree);
		void  SetPosition(const Vec3& _position);

		float GetBoundingSphereRadius() { return max(max(mScale.x, mScale.y), mScale.z); }

		Vec3 GetWorldPosition();
		const Vec3& GetPosition();
		const Vec3& GetRotation();
		const Vec3& GetScale();
		
		Vec3 GetRight() { return mMatWorld.Right(); }
		Vec3 GetUp() { return mMatWorld.Up(); }
		Vec3 GetLook() { return mMatWorld.Backward(); }

		void AddRotation(Axis _eAxis, float _degree);

		void Move(const Vec3& _velocity);

		const Matrix& GetWorldMatrix() { return mMatWorld; }
		const Matrix& GetWorldMatrix() const { return mMatWorld; }

	public:
		void PushData(Camera* pCamera);

	private:
		Transform* mpParent;

		Vec3    mScale;
		Vec3    mRotation;
		Vec3    mRelativeRotation;
		Vec3    mPosition;

		Matrix  mMatLocal;
		Matrix  mMatWorld;

	};

}

