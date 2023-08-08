#pragma once
#include "GameObject.h"
namespace hm
{


	class ImageFilter;
	class GameObject;
	class Scene
	{
	public:
		friend class RenderManager;
		Scene(SceneType eSceneType);
		virtual ~Scene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void Enter() abstract;
		virtual void Exit()  abstract;

	public:
		/* ���������� ���� ������Ʈ�� ���� �߰��ϴ� �Լ� 
		- DontDestroyObject�� �ߺ����� ���� �߰����� �ʵ��� ���������� ó���մϴ�.
		*/
		void AddGameObject(GameObject* _pGameObject);
		
		/*
		** Ư���� ���� �ܿ� ��� ���� **
		* TransfortGameObject���� DontDestroy ������Ʈ���� ���� ���� �о�ֱ� ���� �Լ�
		- �Ϲ������δ� AddGameObject�� ����Ͽ� 
		- ������ DontDestroy ������Ʈ�� �ߺ����� �������� �ʰ� �ؾ� �մϴ�. 
		*/
		void PushGameObjects(const std::vector<GameObject*>& _gameObjects);

		/* ������ ���ӿ�����Ʈ�� �����ϴ� �Լ�*/
		void RemoveGameObject(GameObject* _pGameObject);

		/* ������ ���� ������Ʈ�� ������ �� �����ϴ� �Լ� */
		void DeleteGameObject(GameObject* _pGameObject);

		/* ���̾� ������ ���� ������Ʈ���� ������ �����ϴ� �Լ� */
		void RemoveGameObjects(std::vector<GameObject*>& _gameObjects);
		void RemoveGameObjects(LayerType _eLayerType);

		/* ���̾� ������ ���� ������Ʈ���� �����ϴ� �Լ� */
		void DeleteGameObjects(std::vector<GameObject*>& _gameObjects);
		void DeleteGameObjects(LayerType _eLayerType);

		/*
		* ���̾ ���� ���ӿ�����Ʈ���� ������ ��ȯ�ϴ� �Լ�
		- ���ӿ�����Ʈ�� ���� ������ �ʿ䰡 ���� ���
		- ������ ��� �� �Լ��� ����ϴ� ���� ����
		*/
		const std::vector<GameObject*>& GetGameObjects(LayerType _eLayerType) const;

		/* ���̾ ���� ���ӿ�����Ʈ���� ������ ��ȯ�ϴ� �Լ�
		- ��ȯ���� ������ ���ϸ� ������ �����ǹǷ� ���� �ʿ�
		*/
		std::vector<GameObject*>& GetGameObjectsRef(LayerType _eLayerType);

		/* ���� ����� �� SceneManager���� �� �Լ��� ȣ���Ͽ� DontDestroy ������Ʈ���� ���� ������ �Ű��ִ� �Լ� */
		std::vector<GameObject*> TransportDontDestroyObjects();

		/* ���� �ִ� Physics Actor���� ������ ��� �������ִ� �Լ� */
		void RemovePhysicsActors();

		Camera* GetMainCamera();
		Camera* GetUICamera();

		SceneType GetSceneType() { return meSceneType; }

	private:
		/* ���ڷ� �Ѿ�� ���� ������Ʈ�� ���� ī�޶� ������ �������ִ� �Լ� */
		void RemoveCameraInObjectFromScene(GameObject* _pGameObject);

		/* ���ڷ� �Ѿ�� ���� ������Ʈ�� ���� ���� ������ �������ִ� �Լ� */
		void RemoveLightInObjectFromScene(GameObject* _pGameObject);

	protected:
		SceneType	meSceneType;
		std::array<std::vector<GameObject*>, LAYER_TYPE_COUNT> mGameObjects;

		GameObject* mpMainCamera;
		GameObject* mpUICamera;
		GameObject* mpDirLight;
		std::vector<GameObject*> mCameraObjects;
		std::vector<GameObject*> mLightObjects;
		std::vector<shared_ptr<ImageFilter>> mImageFilters;

	protected:
		static std::vector<wstring> mDontDestroyObjectNames;
	};
}


