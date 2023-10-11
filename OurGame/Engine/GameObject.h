#pragma once
#include "Object.h"
#include "Component.h"
#include "MonoBehavior.h"

namespace hm
{
	class Component;
	class MonoBehavior;
	class Transform;
	class Camera;
	class MeshRenderer;
	class Light;
	class ParticleSystem;
	class Collider;
	class RigidBody;
	class Animator;
	class UIText;
	class AI;
	class Mirror;
	class AudioSound;

	class GameObject :
		public Object
	{
	public:
		GameObject(LayerType _eLayerType);
		GameObject(GameObject* _pOther);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		template<typename T, typename ... Types>
		T* Clone(Types ... _args)
		{
			T* pObject = new T(_args...);
			for (int i = 0; i < FIXED_COMPONENT_COUNT; ++i)
			{
				if (nullptr != mComponents[i])
					mComponents[i]->Clone(pObject);
			}

			for (int i = 0; i < mScripts.size(); ++i)
			{
				mScripts[i]->Clone(pObject);
			}

			pObject->meObjectType = meObjectType;
			pObject->mbCheckFrustum = mbCheckFrustum;
			pObject->mbEnable = mbEnable;
			pObject->mbDontDestroy = mbDontDestroy;
			// GameObject�� ������ ������ �������� ���� �߰������ ��

			return pObject;
		}

		/* ���޹��� ComponentType�� ���� �ش� �ε����� �´� ������Ʈ�� ��ȯ�ϴ� �Լ�
		* _eComponentType : ������ ������Ʈ�� Ÿ��
		*/
		Component* GetFixedComponent(ComponentType _eComponentType);
		Transform* GetTransform();
		Camera* GetCamera();
		MeshRenderer* GetMeshRenderer();
		Light* GetLight();
		ParticleSystem* GetParticleSystem();
		Collider* GetCollider();
		RigidBody* GetRigidBody();
		Animator* GetAnimator();
		UIText* GetUIText();
		AI* GetAI();
		Mirror* GetMirror();
		AudioSound* GetAudioSound();
		GameObject* GetGameObject() { return this; }

		LayerType GetLayerType() { return meLayerType; }

		/* DontDestroyObject�� ���ӿ� ���������� �����ؾ� �ϹǷ� �����ϱ� ���� �̸��� �ʼ������� �ο��Ѵ�. */
		void SetDontDestroyObject(const wstring& _name);
		bool IsDontDestroy() { return mbDontDestroy; }

		virtual void Enable();
		virtual void Disable();
		bool IsEnable() { return mbEnable; }

		/* Frustum Culling�� ������� �������� ���� */
		void SetFrustumCheckFlag(bool _bFlag) { mbCheckFrustum = _bFlag; }
		bool IsFrustumCheck() { return mbCheckFrustum; }

		/* ������ ��ü������ �˻��ϴ� �Լ� */
		bool IsPhysicsObject();

		void SetShader(const wstring& _shaderName);

		void DrawShadow(bool _bFlag) { mbShadow = _bFlag; }
		bool IsDrawShadow() { return mbShadow; }

		bool IsReflect() { return mbReflect; }
		void SetReflect(bool _bFlag) { mbReflect = _bFlag; }

		void SetMotionBlur(bool _bFlag) { mbMotionBlur = _bFlag; }
		bool IsMotionBlur() { return mbMotionBlur; }

		const std::vector<MonoBehavior*>& GetScripts() { return mScripts; }

		/*
		* AddComponent(Component* _pComponent)
		* ���� ������Ʈ�� ������Ʈ�� �߰��ϴ� �Լ�
		* �Լ� ���ο��� ������Ʈ�� ���� ������Ʈ�� �����͸� �����Ѵ�.
		*/
		template<typename T>
		T* AddComponent(T* _pComponent = new T)
		{
			_pComponent->SetGameObject(this);
			int componentType = static_cast<int>(_pComponent->GetComponentType());

			if (FIXED_COMPONENT_COUNT > componentType)
			{
				mComponents[componentType] = _pComponent;
			}
			else
			{
				mScripts.push_back(reinterpret_cast<MonoBehavior*>(_pComponent));
			}

			return _pComponent;
		}


		/* 
		* Ÿ���� ���ø� �Ű������� �ѱ�� Ÿ�Կ� �´� ��ũ��Ʈ�� ã�Ƽ� ��ȯ�ϴ� �Լ�
		*/
		template<typename T>
		T* GetScript()
		{
			for (auto pScript : mScripts)
			{
				T* pPtr = dynamic_cast<T*>(pScript);
				if (nullptr != pPtr)
					return pPtr;
			}

			return nullptr;
		}

		virtual void OnCollisionEnter(Collider* pOtherCollider) {}
		virtual void OnCollisionStay(Collider* pOtherCollider) {}
		virtual void OnCollisionExit(Collider* pOtherCollider) {}

		virtual void OnTriggerEnter(Collider* pOtherCollider) {}
		virtual void OnTriggerStay(Collider* pOtherCollider) {}
		virtual void OnTriggerExit(Collider* pOtherCollider) {}

		bool IsRaysCollide(const Vec3& _origin, const Vec3& _dir, LayerType _eLayerType, float _length);

	private:
		LayerType                                     meLayerType;
		std::array<Component*, FIXED_COMPONENT_COUNT> mComponents;
		std::vector<MonoBehavior*>					  mScripts;
		
	protected:
		bool mbDontDestroy;
		bool mbEnable;
		bool mbCheckFrustum;
		bool mbShadow;
		bool mbReflect;
		bool mbMotionBlur;
	};
}


