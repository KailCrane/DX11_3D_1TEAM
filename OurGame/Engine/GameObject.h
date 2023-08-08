#pragma once
#include "Object.h"
#include "Component.h"

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

	class GameObject :
		public Object
	{
	public:
		GameObject(LayerType _eLayerType);
		GameObject(std::vector<GameObject*> _gameObjects, LayerType _eLayerType);
		virtual ~GameObject();

		virtual void Initialize() const;
		virtual void Update() const;
		virtual void FixedUpdate() const;
		virtual void FinalUpdate() const;
		virtual void Render() const;
		virtual void Destroy() const;

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

		LayerType GetLayerType() { return meLayerType; }

		/* DontDestroyObject�� ���ӿ� ���������� �����ؾ� �ϹǷ� �����ϱ� ���� �̸��� �ʼ������� �ο��Ѵ�. */
		void SetDontDestroyObject(const wstring& _name);
		bool IsDontDestroy() { return mbDontDestroy; }

		void Enable() { mbEnable = true; }
		void Disable() { mbEnable = false; }

		/* Frustum Culling�� ������� �������� ���� */
		void SetFrustumCheckFlag(bool _bFlag) { mbCheckFrustum = _bFlag; }
		bool IsFrustumCheck() { return mbCheckFrustum; }

		/* ������ ��ü������ �˻��ϴ� �Լ� */
		bool IsPhysicsObject();

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

		virtual void OnCollisionEnter(Collider* pOtherCollider) {}
		virtual void OnCollisionStay(Collider* pOtherCollider) {}
		virtual void OnCollisionExit(Collider* pOtherCollider) {}

		virtual void OnTriggerEnter(Collider* pOtherCollider) {}
		virtual void OnTriggerStay(Collider* pOtherCollider) {}
		virtual void OnTriggerExit(Collider* pOtherCollider) {}

	private:
		LayerType                                     meLayerType;
		std::array<Component*, FIXED_COMPONENT_COUNT> mComponents;
		std::vector<MonoBehavior*>					  mScripts;
		
	protected:
		bool mbDontDestroy;
		bool mbEnable;
		bool mbCheckFrustum;
	};
}


