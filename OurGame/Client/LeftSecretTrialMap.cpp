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
#include "TeleportZone.h"
#include "Ground.h"
#include "DecoObject.h"
#include "Monster.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"
#include "Mirror.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PlayerMoveOverMapScript.h"
#include "BonFireScript.h"
#include "OwnerFollowScript.h"
#include "FocusingScript.h"

/* Event */
#include "SceneChangeEvent.h"

LeftSecretTrialMap::LeftSecretTrialMap()
	: Map(MapType::LeftSecretTrialMap)
	, mbIsEnter(false)
{
}

LeftSecretTrialMap::~LeftSecretTrialMap()
{
}

void LeftSecretTrialMap::Initialize()
{
	Map::Initialize();
}

void LeftSecretTrialMap::Start()
{
	Map::Start();

	PLAYER->GetKeyInfo().SetLeftKey(KeyType::RIGHT);
	PLAYER->GetKeyInfo().SetForwardKey(KeyType::DOWN);

	if (PLAYER != nullptr)
	{
		mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
		switch (mSpawnPoint)
		{

		case 3:
			PLAYER->GetTransform()->SetPosition(Vec3(0.92f, -2.57f, 13.1f));
			mpMainCamera->GetTransform()->SetPosition(Vec3(-18.4f, 26.3f, 27.2f));
			mpMainCamera->GetTransform()->SetRotation(Vec3(47.f, -233.3f, 0.f));
			break;

		case 2:
			PLAYER->GetTransform()->SetPosition(Vec3(-13.7f, -2.57f, -43.8f));
			mpMainCamera->GetTransform()->SetPosition(Vec3(-31.f, 26.3f, -29.7f));
			mpMainCamera->GetTransform()->SetRotation(Vec3(47.f, -233.3f, 0.f));
			break;
		}
	}

	OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
	pFollowScript->SetOffset(Vec3(-17.4f, 29.f, 14.1f));
	mpMainCamera->GetScript<FocusingScript>()->SetFocusingMode(true);
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

	if (false == mbIsEnter)
	{
		mbIsEnter = true;
		InitObjectAdd();
		InitColliderAdd();
		FuncObjectAdd();
	}


	

	//���� �Ͼ������ ������ִ� �ڵ�
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));


}

void LeftSecretTrialMap::Exit()
{

}

void LeftSecretTrialMap::InitObjectAdd()
{

	//DecoObject == �ݶ��̴� ���� ������Ʈ
	//WallObject == �ݶ��̴� �ִ� ������Ʈ

	//Forward == �� ����� ���� ��ɾ�
	//Deferred == �� ����� �ִ� ��ɾ�

	//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
	//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�

	//Deferred_CullNone == ���׸��� ī�޶� ���� ©�� ���ִ� ���� _���� �״��

	//Object->AddComponent(new PlacementScript); == Ű����� �����̴� ������Ʈ �̵� ��ũ��Ʈ
	//SetGizmoTarget(Object); == ����Ƽ ������� ���콺�� �����̴� ������Ʈ �̵� �Լ�




	//��ü���� ���̵� ���� - Cube



	//// Toy
	//{
	//	PhysicsInfo physicsInfo;
	//	physicsInfo.eActorType = ActorType::Static;
	//	physicsInfo.eGeometryType = GeometryType::Box;
	//	physicsInfo.size = Vec3(2.f, 2.f, 2.f);

	//	Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(-6.3f, -2.1f, -7.1f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
	//	//pPlayer->AddComponent(new TestAnimationScript);
	//	//pPlayer->AddComponent(new PlayerMoveScript);
	//	pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
	//	AddGameObject(pPlayer);
	//}

	{
		DecoObject* pCube = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\Cube.fbx");
		pCube->GetTransform()->SetScale(Vec3(100.f, 100.f, 100.f));

		AddGameObject(pCube);
	}

	//���� �ٴ� - RoughUpperFloor
	{
		DecoObject* pRoughUpperFloor = Factory::CreateObject<DecoObject>(Vec3(-3.9f, -7.2f, -1.8f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\RoughUpperFloor.fbx");
		pRoughUpperFloor->GetTransform()->SetScale(Vec3(104.f, 104.f, 104.f));
		pRoughUpperFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.01f, 0.01f), 2);


		AddGameObject(pRoughUpperFloor);
	}

	//�Ʒ��� �ٴ� - RoughLowerFloor
	{
		DecoObject* pRoughLowerFloor = Factory::CreateObject<DecoObject>(Vec3(-8.7f, -8.f, 6.8f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\RoughLowerFloor.fbx");
		pRoughLowerFloor->GetTransform()->SetScale(Vec3(86.f, 86.f, 86.f));
		pRoughLowerFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.02f, 0.02f));
		AddGameObject(pRoughLowerFloor);
	}

	{
		GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(10.7f, -7.98f, -7.5f), L"Forward", L"", false, LayerType::Mirror);

		pMirror->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
		pMirror->AddComponent(new Mirror);
		pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));
		pMirror->GetMirror()->SetAlpha(0.07f);

		AddGameObject(pMirror);
	}



#pragma region "���"
	{
		//��� ������ - ColumnFull

		{
			//������ �ǿ��� ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-20.4f, 2.8f, 12.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 64.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-20.4f, 2.8f, -26.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 64.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-39.4f, 2.8f, -45.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 64.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//������ �ǿ��� ���� �׹�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-50.f, 2.8f, -45.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 64.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ ù��° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-18.4f, -3.6f, -5.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 64.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-18.4f, -3.6f, 34.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 46.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ������� _ ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.4f, -3.6f, 34.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 46.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ ù��° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-8.2f, 0.4f, -5.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 90.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 0.4f, -5.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 90.f, 64.f));

			AddGameObject(pColumnFull);
		}

		{
			//�Ʒ��� �ǿ����� ���� ū��� _ ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 0.4f, 4.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pColumnFull->GetTransform()->SetScale(Vec3(64.f, 90.f, 64.f));
			AddGameObject(pColumnFull);
		}
	}
#pragma endregion

#pragma region "������"
	{
		//������ ��� õ�� 1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(10.8f, 8.f, 22.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.f, 100.f, 100.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 2 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(13.f, 8.2f, -26.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.f, 100.f, 24.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 3 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(1.4f, 8.2f, -23.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.f, 100.f, 24.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 4 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(4.0f, 8.2f, -36.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 5 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-8.0f, 8.2f, -34.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 6 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-6.4f, 8.2f, -45.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ�7 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-18.6f, -3.2f, -34.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 8 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-8.2f, -3.2f, -34.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 8_1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(6.96f, -7.8f, -36.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 50.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 9 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-6.4f, -3.2f, -36.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 10 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-18.4f, -7.8f, 13.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 100.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 10_1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(1.4f, -7.8f, 13.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 100.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 11 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(1.4f, -3.2f, 12.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 80.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 12 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-18.44f, -3.2f, 15.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 24.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 13 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(6.96f, -3.2f, 3.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 50.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 14 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(6.96f, -1.0f, 3.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(100.0f, 100.0f, 50.0f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

			AddGameObject(pbannisterTop);
		}

	}
#pragma endregion

#pragma region "���� ����"
	{
		//������ 1 - painting4Frame01
		{
			DecoObject* pPainting4Frame01 = Factory::CreateObject<DecoObject>(Vec3(10.6f, 4.8f, 25.2f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame01.fbx");
			pPainting4Frame01->GetTransform()->SetScale(Vec3(40.f, 40.f, 40.f));
			pPainting4Frame01->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pPainting4Frame01);
		}

		//������ 2 - painting4Frame02
		{
			DecoObject* pPainting4Frame02 = Factory::CreateObject<DecoObject>(Vec3(10.8f, 4.4f, 13.8f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame02.fbx");
			pPainting4Frame02->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pPainting4Frame02->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pPainting4Frame02);
		}

		//������ 3 - painting4Frame03
		{
			DecoObject* pPainting4Frame03 = Factory::CreateObject<DecoObject>(Vec3(10.8f, 2.6f, 32.0f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame03.fbx");
			pPainting4Frame03->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pPainting4Frame03->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pPainting4Frame03);
		}

		//������ 4 - painting4Frame04
		{
			DecoObject* pPainting4Frame04 = Factory::CreateObject<DecoObject>(Vec3(-8.4f, 3.6f, -12.6f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame04.fbx");
			pPainting4Frame04->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pPainting4Frame04->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));

			AddGameObject(pPainting4Frame04);
		}

		//������ 5 - painting4Frame05
		{
			DecoObject* pPainting4Frame05 = Factory::CreateObject<DecoObject>(Vec3(10.6f, 4.4f, 28.4f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame05.fbx");
			pPainting4Frame05->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pPainting4Frame05->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));

			AddGameObject(pPainting4Frame05);
		}

		//������ 6 - painting4Frame06
		{
			DecoObject* pPainting4Frame06 = Factory::CreateObject<DecoObject>(Vec3(9.4f, -0.8f, 9.6f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame06.fbx");
			pPainting4Frame06->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pPainting4Frame06->GetTransform()->SetRotation(Vec3(0.f, 00.f, -20.f));

			AddGameObject(pPainting4Frame06);
		}
	}
#pragma endregion

#pragma region "���г� �����Ÿ��"
	{
		//���г�
		{
			//�� �г� 1
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(10.7f, -1.34f, 14.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(54.f, 54.f, 54.f));

				AddGameObject(pWallPanel);
			}

			//�� �г� 2
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(10.7f, -1.34f, 21.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(54.f, 54.f, 54.f));

				AddGameObject(pWallPanel);
			}

			//�� �г� 3
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(10.7f, -1.34f, 32.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(54.f, 54.f, 60.f));

				AddGameObject(pWallPanel);
			}

			//�� �г� 4
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(10.7f, -1.34f, 6.78f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(54.f, 54.f, 66.f));

				AddGameObject(pWallPanel);
			}

			//�� �г� 5
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(30.5f, -1.34f, -26.62f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(54.f, 54.f, 58.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pWallPanel);
			}
		}
	}
#pragma endregion

#pragma region "���� ���ݵ� ����"
	//�������� - TwoTierShelf
	{
		//�������� �����ʺ��� 1
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-13.6f, -5.6f, -33.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 2
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-12.4f, -5.6f, -28.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 3
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.4f, -5.6f, -28.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 4
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.4f, -5.6f, -24.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 5
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-13.6f, -5.6f, -24.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 6
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-13.6f, -5.6f, -18.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 7
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -5.6f, -19.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 8
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-2.6f, -5.6f, -19.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(7.0f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 9
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.4f, -5.6f, -15.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 10
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.4f, -5.6f, -9.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 11
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-11.2f, -5.6f, -13.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(7.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 12
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-2.2f, -5.6f, -7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(6.2f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 13
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-11.2f, -5.6f, -7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(7.4f, 7.0f, 6.4f));

		AddGameObject(pTwoTierShelf);
	}

#pragma endregion



#pragma region "�������ݾȿ��ִ� ��� �ڽ� ����"
	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, -0.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-14.4f, -4.6f, 1.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(60.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 10.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 3.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 7.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-14.4f, -4.8f, 9.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 11.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 14.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 16.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 70.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -4.8f, 17.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -2.0f, 17.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-13.8f, -2.0f, 15.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -4.8f, 23.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -4.8f, 16.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(24.4f, -4.8f, -28.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(70.0f, 70.0f, 68.0f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

		AddGameObject(pEmptyBox);
	}
#pragma endregion

	//�ڽ��� ���� 1 - SilverwareShelfFiller_Plates
	{
		DecoObject* pSilverwareShelfFiller_Plates = Factory::CreateObject<DecoObject>(Vec3(-12.8f, -1.6f, 13.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\SilverwareShelfFiller_Plates.fbx");
		pSilverwareShelfFiller_Plates->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));

		AddGameObject(pSilverwareShelfFiller_Plates);
	}

	//�ڽ��� ���� 2- SilverwareShelfFiller_Plates
	{
		DecoObject* pSilverwareShelfFiller_Plates = Factory::CreateObject<DecoObject>(Vec3(-15.2f, -4.4f, 5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\SilverwareShelfFiller_Plates.fbx");
		pSilverwareShelfFiller_Plates->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));

		AddGameObject(pSilverwareShelfFiller_Plates);
	}

	//�ڽ��� ���� - SilverwareShelfFiller_Goblets
	{
		DecoObject* pSilverwareShelfFiller_Goblets = Factory::CreateObject<DecoObject>(Vec3(-14.0f, -1.6f, 12.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\SilverwareShelfFiller_Goblets.fbx");
		pSilverwareShelfFiller_Goblets->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));

		AddGameObject(pSilverwareShelfFiller_Goblets);
	}

	// Ŀư - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(0.6f, 7.0f, 6.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(84.0f, 84.0f, 84.0f));

		AddGameObject(pCurtainHorizontal);
	}

	//Ŀư �Ʒ��� - CurtainVertical
	{
		DecoObject* pCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(1.2f, -0.4f, 9.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainVertical.fbx");
		pCurtainVertical->GetTransform()->SetScale(Vec3(84.0f, 84.0f, 84.0f));

		AddGameObject(pCurtainVertical);
	}

	// Ŀư 2 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(34.4f, 7.0f, -35.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(84.0f, 84.0f, 84.0f));
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));
		AddGameObject(pCurtainHorizontal);
	}

	//Ŀư 2 �Ʒ��� - CurtainVertical
	{
		DecoObject* pCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(37.0f, -0.4f, -35.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainVertical.fbx");
		pCurtainVertical->GetTransform()->SetScale(Vec3(84.0f, 84.0f, 84.0f));
		pCurtainVertical->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));

		AddGameObject(pCurtainVertical);
	}


	//���帮�� - ChandelierWithChain
	{
		DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(-8.2f, 18.0f, 1.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\ChandelierWithChain.fbx");
		pChandelier->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));
		pChandelier->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		pChandelier->DrawShadow(false);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 13, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 13, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 13, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 14, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 14, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 14, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 15, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 15, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 15, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 16, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 16, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 16, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 17, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 17, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 17, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 18, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 18, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 18, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 19, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 19, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 19, 0);

		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 20, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 20, 0);
		pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 20, 0);

		AddGameObject(pChandelier);
	}

	//��ٸ� - Ladder
	{
		DecoObject* pLadder = Factory::CreateObject<DecoObject>(Vec3(-14.8f, -5.6f, 15.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\Ladder.fbx");
		pLadder->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));
		pLadder->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		AddGameObject(pLadder);
	}

	{
		DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(-13.7f, -0.5f, -6.9f), L"Fire", L"");
		pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
		pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
		pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
		pBonFire->AddComponent(new BonFireScript);
		AddGameObject(pBonFire);
		
		DecoObject* pLightObject = nullptr;
		{
			pLightObject = new DecoObject;
			Transform* pTransform = pLightObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-14.f, 5.9f, -6.5f));
			pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Light* pLight = pLightObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(1.0f, 0.3f, 0.2f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(70.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pLightObject);
		}
	}
}

void LeftSecretTrialMap::InitColliderAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(31.85f, 1.f, 40.84f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-3.9f, -8.5f, -16.7f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(31.85f, 1.0f, 12.252f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-8.3f, -3.7f, 9.5f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(12.08f, 1.0f, 46.478f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(7.3f, -3.7f, -10.2f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(2.61f, 3.9f, 23.9f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-13.6f, -5.1f, -24.4f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(2.61f, 3.9f, 23.9f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-6.4f, -5.1f, -17.8f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(15.795f, 3.9f, 2.64f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-7.0f, -5.1f, -19.8f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(15.795f, 3.9f, 2.64f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-7.0f, -5.1f, -7.2f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(9.46f, 4.0f, 2.64f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-10.0f, -5.1f, -13.7f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(12.3f, 4.0f, 2.64f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-9.4f, -5.1f, -28.5f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(23.99f, 5.2f, 10.64f);

		Ground* pWallAndGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-8.6f, -5.8f, -42.7f), physicsInfo, L"Forward", L"");

		AddGameObject(pWallAndGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(12.00f, 11.23f, 10.29f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-2.8f, -2.5f, -41.1f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(12.00f, 11.23f, 10.29f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(6.8f, 3.1f, -31.8f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}

	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.96f, 12.07f, 61.74f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-18.7f, -2.5f, -17.7f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.96f, 12.07f, 26.48f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(10.9f, 2.5f, 0.4f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.96f, 12.07f, 10.6f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(10.9f, 2.5f, -21.4f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
}

void LeftSecretTrialMap::FuncObjectAdd()
{

#pragma region "ȭ��� �ø���"
	// ȭ��� 1
	{
		//ȭ��� 3�� ������Ʈ ��Ʈ
		float x = -12.8f;
		float y = -2.6f;
		float z = 8.3f;
		{
			//���� - FireLamp_Bottom
			DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Bottom.fbx");
			pFireLamp_Bottom->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
			AddGameObject(pFireLamp_Bottom);
		}
		{
			//�������� - FireLamp_Wood
			DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Wood.fbx");
			pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));

			AddGameObject(pFireLamp_Wood);
		}
		{
			//��ܺ� - FireLamp_Top
			DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 1.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Top.fbx");
			pFireLamp_Top->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

			AddGameObject(pFireLamp_Top);
		}
	}

	// ȭ��� 2
	{
		//ȭ��� 3�� ������Ʈ ��Ʈ
		float x = 6.4f;
		float y = -2.6f;
		float z = 8.3f;
		{
			//���� - FireLamp_Bottom
			DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Bottom.fbx");
			pFireLamp_Bottom->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
			AddGameObject(pFireLamp_Bottom);
		}
		{
			//�������� - FireLamp_Wood
			DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Wood.fbx");
			pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));

			AddGameObject(pFireLamp_Wood);
		}
		{
			//��ܺ� - FireLamp_Top
			DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 1.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Top.fbx");
			pFireLamp_Top->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

			AddGameObject(pFireLamp_Top);
		}
	}

	// ȭ��� 3
	{
		//ȭ��� 3�� ������Ʈ ��Ʈ
		float x = 6.4f;
		float y = -2.6f;
		float z = -22.9f;
		{
			//���� - FireLamp_Bottom
			DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Bottom.fbx");
			pFireLamp_Bottom->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
			AddGameObject(pFireLamp_Bottom);
		}
		{
			//�������� - FireLamp_Wood
			DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Wood.fbx");
			pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));

			AddGameObject(pFireLamp_Wood);
		}
		{
			//��ܺ� - FireLamp_Top
			DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 1.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Top.fbx");
			pFireLamp_Top->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

			AddGameObject(pFireLamp_Top);
		}
	}

	// ȭ��� 4
	{
		//ȭ��� 3�� ������Ʈ ��Ʈ
		float x = -13.6f;
		float y = -2.6f;
		float z = -7.f;
		{
			//���� - FireLamp_Bottom
			DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Bottom.fbx");
			pFireLamp_Bottom->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
			AddGameObject(pFireLamp_Bottom);
		}
		{
			//�������� - FireLamp_Wood
			DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Wood.fbx");
			pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));

			AddGameObject(pFireLamp_Wood);
		}
		{
			//��ܺ� - FireLamp_Top
			DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 1.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Top.fbx");
			pFireLamp_Top->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

			AddGameObject(pFireLamp_Top);
		}
	}

	// ȭ��� 5
	{
		//ȭ��� 3�� ������Ʈ ��Ʈ
		float x = -13.6f;
		float y = -2.6f;
		float z = -22.4f;
		{
			//���� - FireLamp_Bottom
			DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Bottom.fbx");
			pFireLamp_Bottom->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
			AddGameObject(pFireLamp_Bottom);
		}
		{
			//�������� - FireLamp_Wood
			DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Wood.fbx");
			pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));

			AddGameObject(pFireLamp_Wood);
		}
		{
			//��ܺ� - FireLamp_Top
			DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 1.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\FireLamp_Top.fbx");
			pFireLamp_Top->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

			AddGameObject(pFireLamp_Top);
		}
	}
#pragma endregion

	{
		GameObject* pLightObject = new GameObject(LayerType::Unknown);
		Transform* pTransform = pLightObject->AddComponent(new Transform);
		pTransform->SetPosition(Vec3(-8.4f, 12.2f, -27.3f));
		pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
		pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
		Light* pLight = pLightObject->AddComponent(new Light);
		pLight->SetDiffuse(Vec3(1.0f, 1.0f, 0.7f));
		pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
		pLight->SetLightRange(40.f);
		pLight->SetLightType(LightType::PointLight);
		AddGameObject(pLightObject);
	}


	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(4.7f, 10.8f, 3.5f);

		yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(14.1f, -1.7f, -14.5f), physicsInfo, L"Forward", L"", false, MapType::BossMap,1);
		AddGameObject(pTelZone);
	}

	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(4.7f, 10.8f, 3.5f);

		yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(-13.5f, -1.1f, -49.6f), physicsInfo, L"Forward", L"", false, MapType::LeftSecretFightMap, 2);
		AddGameObject(pTelZone);
	}
}
