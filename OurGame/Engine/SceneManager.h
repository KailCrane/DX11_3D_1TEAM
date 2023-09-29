#pragma once
#include "Scene.h"

namespace hm
{
	class SceneManager
	{
	public:
		DECLARE_SINGLE(SceneManager);

	public:
		void Initialize();
		void Update();
		void FixedUpdate();
		void FinalUpdate();
		void Render();
		void Destroy();

		Scene* GetActiveScene() { return mpActiveScene; }
		Scene* GetScene(SceneType _eSceneType);
		void AddScene(Scene* _pScene);
		void AddMap(Scene* _pMap);
		void ActiveAndInitializeScene(SceneType _eSceneType);
		Vec3 ScreenToWorldPosition(const Vec3& _screenCoord, Camera* _pCamera);
		Vec3 WorldToScreenPosition(const Vec3& _worldCoord, Camera* _pCamera);

	private:
		/* ���� �ٲ۴� (*�� �Լ��� �̺�Ʈ�� ó���ؾ��ϹǷ� ���� ȣ�� ����)
		* ���� �ٲٴ� �۾��� �ش� �����ӿ��� ó���ؾ� �� ���� ��� ó���� �Ŀ� �̷������ ��
		*/
		friend class EventManager;
		void ChangeScene(SceneType _eSceneType);

	private:
		std::array<Scene*, SCENE_TYPE_COUNT> mScenes = {};
		Scene* mpActiveScene = nullptr;
	};
}




