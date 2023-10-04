#include "pch.h"
#include "TitleScene.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "UI.h"

/* Interface */
#include "Interface.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "CinematicCamMove.h"
#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"
#include "StartButtonScript.h"
#include "LogoBlinkScript.h"
#include "PlayerMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	TitleScene::TitleScene()
		: Scene(SceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (nullptr != mpActiveInterface)
		{
			Vec3 pos = mpActiveInterface->GetTransform()->GetPosition();
			pos.x -= 80.f;
			pos.y += 15.f;

			mpSelectedInterface->GetTransform()->SetPosition(pos);
		}
		
		// ����
		// - GrandmaBossMap
		// - Right2Map
		if (IS_DOWN(KeyType::P))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Right2Map);
		}

		// ����
		// - HallColliderCheckMap - 2��ġ �з�
		// - CorridorRightMap
		// - RightSecretPassageMap
		if (IS_DOWN(KeyType::O))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::PhysicsTest);
		}

		// ��
		// - DiningColliderCheckMap
		// - EntranceHallMap
		// - LeftSecretFightMap
		// - LeftSecretTrialMap
		// - Monster_Player_TestScene
		if (IS_DOWN(KeyType::L))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::EntranceHallMap);
		}

		// ����
		// - MainOfficeMap - 3��ġ �з�
		// - RightMap
		if (IS_DOWN(KeyType::K))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::HallColliderCheckMap);
		}
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::FinalUpdate()
	{
		Scene::FinalUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::Destroy()
	{
		Scene::Destroy();
	}

	void TitleScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);

		// Create Main Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"MainCamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pGameObject->AddComponent(new CameraMoveScript);
			//pGameObject->AddComponent(new yj::CinematicCamMove);

			pCamera->SetCullingMask(LayerType::Interface, true);
			pCamera->SetCullingMask(LayerType::Mirror, true);

			pTransform->SetPosition(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pGameObject);
		}

		// Create UI Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"UICamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pCamera->SetProjectionType(ProjectionType::Orthographic);
			pCamera->EnableAllCullingMask();
			pCamera->SetCullingMask(LayerType::Interface, false);

			pTransform->SetPosition(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pGameObject);
		}
		
		// Create DirLight
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"DirLight");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(0.f, 10.f, 0.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(1.f, 1.f, 1.f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightDirection(Vec3(0.f, -1.f, 0.f));
			pLight->SetLightType(LightType::DirectionalLight);
			AddGameObject(pGameObject);
		}

		// Title
		{
			Interface* pLogoInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, 0.f), Vec2(300.f, 200.f), L"..\\Resources\\Texture\\DD_Logo_Smooth_Dropshadow.png");
			pLogoInterface->AddComponent(new LogoBlinkScript);
			AddGameObject(pLogoInterface);
		}

		// Select Interface
		{
			mpSelectedInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, -3.f), Vec2(40.f, 39.f), L"..\\Resources\\Texture\\icon_crowfoot.png");
			mpSelectedInterface->SetAlpha(0.8f);
			AddGameObject(mpSelectedInterface);
		}

		// Buttons
		{		
			// ����
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(-450.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"����", MapType::Right2Map));

				// Ŭ�� ����� ��ũ��Ʈ�� ����
				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();

				// Ŭ������ �� �ݹ�
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });

				// ���콺�� ��ư���� ����� ��
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"����", 35.f, true); }); 

				// ���콺�� ��ư�� �ö��� ��
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"����", 40.f, true); mpActiveInterface = pInterface; }); 

				// �ؽ��� ���İ� ����
				pInterface->SetAlpha(0.f);

				// �ؽ�Ʈ ����
				pInterface->SetText(L"����", 25.f, true);

				// �ؽ�Ʈ �÷� ����
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));
				AddGameObject(pInterface);

				// �ӽ÷� ����
				mpActiveInterface = pInterface;
			}

			// ��
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(-150.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"��", MapType::Monster_Player_Test));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"��", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"��", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"����", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// ����
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(150.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"����", MapType::PhysicsTest));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"����", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"����", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"����", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// ����
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(450.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"����", MapType::Right2Map));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"����", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"����", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"����", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// Exit Button
			{
				ButtonInfo info = {};
				info.clickedCallback = []() { PostQuitMessage(0); };

				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(0.f, -300.f, -1.f), Vec2(50.f, 50.f), info);

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"����", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"����", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetText(L"����", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

		}

		//Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(0.8f, 0.5f, 0.8f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, -100.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			pPlayer->SetDontDestroyObject(L"Player");

			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.6f, 0.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			//SetMeshTarget(pPlayer);
		}



	}

	void TitleScene::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	}
}

