#include "pch.h"
#include "LeftSecretTrialMap.h"
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

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "Monster.h"

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
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"

LeftSecretTrialMap::LeftSecretTrialMap()
	: Map(MapType::LeftSecretTrialMap)
{
}

LeftSecretTrialMap::~LeftSecretTrialMap()
{
}

void LeftSecretTrialMap::Initialize()
{
	Map::Initialize();
}

void LeftSecretTrialMap::Update()
{
	Map::Update();
}

void LeftSecretTrialMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void LeftSecretTrialMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void LeftSecretTrialMap::Render()
{
	Map::Render();
}

void LeftSecretTrialMap::Enter()
{
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

	//���� �Ͼ������ ������ִ� �ڵ�
	gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));


#pragma region "����"
#pragma endregion

	//DecoObject == �ݶ��̴� ���� ������Ʈ
	//WallObject == �ݶ��̴� �ִ� ������Ʈ

	//Forward == �� ����� ���� ��ɾ�
	//Deferred == �� ����� �ִ� ��ɾ�

	//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
	//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�
	
	//Deferred_CullNone == ���׸��� ī�޶� ���� ©�� ���ִ� ���� _���� �״��
		

	//��ü���� ���̵� ���� - Cube
	{
		DecoObject* pCube = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\Cube.fbx");
		pCube->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		AddGameObject(pCube);
	}

	//���� �ٴ� - RoughUpperFloor
	{
		DecoObject* pRoughUpperFloor = Factory::CreateObject<DecoObject>(Vec3(-1.95f, -3.6f, -0.9f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\RoughUpperFloor.fbx");
		pRoughUpperFloor->GetTransform()->SetScale(Vec3(52.f, 52.f, 52.f));
		AddGameObject(pRoughUpperFloor);
	}

	//�Ʒ��� �ٴ� - RoughLowerFloor
	{
		DecoObject* pRoughLowerFloor = Factory::CreateObject<DecoObject>(Vec3(-4.35f, -4.f, 3.4f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\RoughLowerFloor.fbx");
		pRoughLowerFloor->GetTransform()->SetScale(Vec3(43.f, 43.f, 43.2f));
		
		AddGameObject(pRoughLowerFloor);
	}

	{
		//��� ������ - ColumnFull

		{
			//������ �ǿ��� ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-10.2f, 1.4f, 6.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 32.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-10.2f, 1.4f, -13.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 32.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-19.7f, 1.4f, -22.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 32.f, 32.f));

			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� �׹�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-25.f, 1.4f, -22.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 32.f, 32.f));
		
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ ù��° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -1.8f, -2.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 23.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -1.8f, 17.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 23.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.7f, -1.8f, 17.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 23.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ ù��° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-4.1f, 0.2f, -2.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 45.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.65f, 0.2f, -2.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 45.f, 32.f));
			
			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.65f, 0.2f, 2.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(32.f, 45.f, 32.f));
			AddGameObject(pColumnFull);
		}
	}


}

void LeftSecretTrialMap::Exit()
{
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
}