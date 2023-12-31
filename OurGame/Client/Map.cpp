#include "pch.h"
#include "Map.h"
#include "PlacementScript.h"
#include "Input.h"
#include "RenderManager.h"
#include "CameraHolder.h"

namespace hm
{
	GameObject* Map::spPlayerHolder = nullptr;
	GameObject* Map::spCutSceneHolder = nullptr;
	GameObject* Map::spCutSceneFocusingTarget = nullptr;

	Map::Map(MapType _eMapType)
		: Scene(_eMapType)
		, mbShadow(false)
	{

		if (nullptr == spPlayerHolder)
		{
			spPlayerHolder = new GameObject(LayerType::Unknown);
			spPlayerHolder->AddComponent(new Transform);
			spPlayerHolder->SetDontDestroyObject(L"PlayerHolder");
			AddGameObject(spPlayerHolder);
		}

		if (nullptr == spCutSceneHolder)
		{
			spCutSceneHolder = new GameObject(LayerType::Unknown);
			spCutSceneHolder->AddComponent(new Transform);
			spCutSceneHolder->SetDontDestroyObject(L"CutSceneHolder");
			AddGameObject(spCutSceneHolder);
		}

		if (nullptr == spCutSceneFocusingTarget)
		{
			spCutSceneFocusingTarget = new GameObject(LayerType::Unknown);
			spCutSceneFocusingTarget->AddComponent(new Transform);
			spCutSceneFocusingTarget->SetDontDestroyObject(L"CutSceneTarget");
			AddGameObject(spCutSceneFocusingTarget);
		}
	}

	Map::~Map()
	{
	}
	void Map::Initialize()
	{
		Scene::Initialize();
	}
	void Map::Update()
	{
		Scene::Update();

		//if (IS_DOWN(KeyType::M) && nullptr != mpDirLight)
		//	
		// (mpDirLight);

		if (IS_DOWN(KeyType::N))
			GET_SINGLE(RenderManager)->BakeStaticShadow(this);
	}
	void Map::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void Map::FinalUpdate()
	{
		Scene::FinalUpdate();
	}
	void Map::Render()
	{
		Scene::Render();
	}
	void Map::Enter()
	{
	//배경맵 하얀색으로 만들어주는 코드
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region "어드민"
#pragma endregion

	//DecoObject == 콜라이더 없는 오브젝트
	//WallObject == 콜라이더 있는 오브젝트

	//Forward == 빛 계산이 없는 명령어
	//Deferred == 빛 계산이 있는 명령어

	//->GetTransform()->SetPositionExcludingColliders == 콜라이더를 제외하고 오브젝트만 [이동] 시키는 함수
	//->GetTransform()->SetRotationExcludingColliders == 콜라이더를 제외하고 오브젝트만 [회전] 시키는 함수

	//Deferred_CullNone == 머테리얼 카메라 시점 짤림 없애는 버전 _원본 그대로

	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"ObjectTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
	//Object->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);

	//Object->AddComponent(new PlacementScript); == 키보드로 움직이는 오브젝트 이동 스크립트
	//SetGizmoTarget(Object); == 유니티 방식으로 마우스로 움직이는 오브젝트 이동 함수



	}
	void Map::Exit()
	{
	}
	void Map::SetGizmoTarget(GameObject* _pTarget)
	{
		TOOL->UseGizmo();
		TOOL->SetGameObject(_pTarget);
	}
	void Map::SetMeshTarget(GameObject* _pTarget)
	{
		TOOL->UseMeshTool();
		TOOL->SetGameObject(_pTarget);
	}
	void Map::SetPlayerHolder(GameObject* _pHolder)
	{
		spPlayerHolder = _pHolder;
	}
	void Map::SetCutSceneHolder(GameObject* _pHolder)
	{
		spCutSceneHolder = _pHolder;
	}
	void Map::SetPlayerHolderPosition(const Vec3& _pos)
	{
		spPlayerHolder->GetTransform()->SetPosition(_pos);
	}
	void Map::SetCutSceneHolderPosition(const Vec3& _pos)
	{
		spCutSceneHolder->GetTransform()->SetPosition(_pos);
	}
}

