#include "pch.h"
#include "EntranceHallMap.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "TeleportZone.h"
#include "Player.h"
#include "Ground.h"
#include "Monster.h"
#include "JarDoor.h"
#include "KeyDoor.h"

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


EntranceHallMap::EntranceHallMap()
	: Map(MapType::EntranceHallMap)
{
}

EntranceHallMap::~EntranceHallMap()
{
}

void EntranceHallMap::Initialize()
{
	Map::Initialize();
}

void EntranceHallMap::Start()
{
	Map::Start();
}

void EntranceHallMap::Update()
{
	Map::Update();
	if (mTarget != nullptr)
		{
			if (IS_UP(KeyType::LEFT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::RIGHT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::UP))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::DOWN))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::Z))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::X))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
				mTarget->GetTransform()->SetPosition(fixed_pos);

			}
			if (IS_UP(KeyType::R)) //ȸ��
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::T)) //ȸ��
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::Y)) //ȸ��
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::U)) //ȸ��
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::O)) //������ - ��ü�� Ű���
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::P)) //������ - ��ü�� ���̱�
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::K)) //������ - y������ Ű���
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y, target_scale.z += 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::L)) //������ - y�� ���� ���̱�
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y, target_scale.z -= 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::N)) //������ -y�ุ Ű���
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y += 0.5, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::M)) //������ -y�ุ ���̱�
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y -= 0.5, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::H)) //������ - x�ุ Ű���
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x +=0.5, target_scale.y, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::J)) //������ -x�ุ ���̱�
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -=0.5, target_scale.y, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::F)) //������ -z�ุ Ű���
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z += 0.5);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::G)) //������ -z�ุ ���̱�
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z -= 0.5);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::ENTER))
			{
				Vec3 a = mTarget->GetTransform()->GetPosition();
				Vec3 b = mTarget->GetTransform()->GetRotation();
				Vec3 c = mTarget->GetTransform()->GetScale();
				int d = 0;


			}
		}
}

void EntranceHallMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void EntranceHallMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void EntranceHallMap::Render()
{
	Map::Render();
}

void EntranceHallMap::Enter()
{
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

	//���� �Ͼ������ ������ִ� �ڵ�
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

	InitObjectAdd();
	InitColliderAdd();
	GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 1);

	if (PLAYER)
	{
		int a = 0;
	}
	PLAYER->GetRigidBody()->ApplyGravity();
	PLAYER->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
	PLAYER->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

}

void EntranceHallMap::Exit()
{
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
	//GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
}

void EntranceHallMap::InitObjectAdd()
{
#pragma region "����"
#pragma endregion

	//DecoObject == �ݶ��̴� ���� ������Ʈ
	//WallObject == �ݶ��̴� �ִ� ������Ʈ

	//Forward == �� ����� ���� ��ɾ�
	//Deferred == �� ����� �ִ� ��ɾ�

	//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
	//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�

	//Deferred_CullNone == ���׸��� ī�޶� ���� ©�� ���ִ� ���� _���� �״��

	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"ObjectTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
	//Object->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); == �ؽ��� ��ȣ ����

	//Object->AddComponent(new PlacementScript); == Ű����� �����̴� ������Ʈ �̵� ��ũ��Ʈ
	//SetGizmoTarget(Object); == ����Ƽ ������� ���콺�� �����̴� ������Ʈ �̵� �Լ�


	//��ü���� ���̵� ���� - EntranceHall
	{
		DecoObject* pEntranceHall = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbx");
		pEntranceHall->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"EntranceHallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); // �ؽ��� ������ �����Ű�¹�

		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pEntranceHall);
	}

	//�ٴ� - EntranceHallFloor
	{
		DecoObject* pEntranceHallFloor = Factory::CreateObject<DecoObject>(Vec3(0.1f, -9.7f, 4.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHallFloor.fbx");
		pEntranceHallFloor->GetTransform()->SetScale(Vec3(58.5f, 1.f, 58.5f));

		pEntranceHallFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.05f, 0.05f));

		AddGameObject(pEntranceHallFloor);
	}

	//�ٴ� ������ - wallPanel_Merged
	{
		DecoObject* pwallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -10.6f, 4.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\wallPanel_Merged.fbx");
		pwallPanel_Merged->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pwallPanel_Merged->GetTransform()->SetScale(Vec3(41.4f, 41.4f, 41.4f));

		AddGameObject(pwallPanel_Merged);
	}

#pragma region "���"
	{
		//ù��° ��� - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(11.7f, 0.85f, 24.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}
	{
		//�ι�° ��� - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(11.7f, 0.85f, -14.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}

	{
		//����° ��� - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.3f, 0.85f, -14.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}
#pragma endregion

#pragma region "������"
	//������ - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(12.4f, 9.8f, 5.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pbannisterTop->GetTransform()->SetScale(Vec3(40.f, 130.f, 40.f));


		AddGameObject(pbannisterTop);
	}

	//������ - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.4f, 9.8f, -14.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pbannisterTop->GetTransform()->SetScale(Vec3(25.f, 130.f, 40.f));


		AddGameObject(pbannisterTop);
	}
#pragma endregion

#pragma region "���г�"
	//���г� 1 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, 17.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//���г� 2 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, 7.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//���г� 3 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, -2.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//���г� 4 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//���г� ����ĭ - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(9.3f, -8.5f, -15.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel_shot);
	}

	//���г� ����ĭ 2  - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(-7.3f, -8.5f, -15.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(6.f, 10.f, 10.f));

		AddGameObject(pWallPanel_shot);
	}

	//���г� �� �׵θ� - DoorFrameBig
	{
		DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.9f, -14.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\DoorFrameBig.fbx");
		pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pDoorFrameBig->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));

		AddGameObject(pDoorFrameBig);
	}
#pragma endregion

	//Ŀư - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(0.f, 6.4f, -13.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(22.f, 22.f, 22.f));


		AddGameObject(pCurtainHorizontal);
	}

	//����� �� - jarDoor
	{
		pJarRDoor = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.6f, -15.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarRDoor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pJarRDoor->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
		AddGameObject(pJarRDoor);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(2, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(3, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
	}

	{
		pJarLDoor = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.6f, -15.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarLDoor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pJarLDoor->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
		AddGameObject(pJarLDoor);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(4, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(5, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(6, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(7, false);
	}


	//Ź�� - MiddleShelf
	{
		DecoObject* pMiddleShelf = Factory::CreateObject<DecoObject>(Vec3(8.6f, -7.2f, 5.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MiddleShelf.fbx");
		pMiddleShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMiddleShelf->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));

		AddGameObject(pMiddleShelf);
	}

	//Ź���� �� ȭ�� - MansionPlantPot
	{
		DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(8.6f, -2.4f, 9.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionPlantPot.fbx");
		pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionPlantPot->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));

		AddGameObject(pMansionPlantPot);
	}

	//Ź���� ���� ȭ�е� 1 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(7.9f, -3.9f, 3.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pMansionSpicePot_small);
	}

	//Ź���� ���� ȭ�е� 2 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(9.0f, -3.9f, 1.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pMansionSpicePot_small);
	}

	//���� - Chair
	{
		DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(6.3f, -5.1f, 21.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\Chair.fbx");
		pChair->GetTransform()->SetRotation(Vec3(0.f, 75.f, 0.f));
		pChair->GetTransform()->SetScale(Vec3(9.f, 9.f, 9.f));

		AddGameObject(pChair);
	}

	//�׸����� 1 - paintingFrame
	{
		DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(12.f, 3.2f, 15.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame.fbx");
		pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

		AddGameObject(pPaintingFrame);
	}

	//�׸����� 2 - paintingFrame2
	{
		DecoObject* pPaintingFrame2 = Factory::CreateObject<DecoObject>(Vec3(12.f, 3.1f, 4.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame2.fbx");
		pPaintingFrame2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame2->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));

		AddGameObject(pPaintingFrame2);
	}

	//�׸����� 3 - paintingFrame4
	{
		DecoObject* pPaintingFrame4 = Factory::CreateObject<DecoObject>(Vec3(11.9f, 3.1f, -7.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame4.fbx");
		pPaintingFrame4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame4->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

		AddGameObject(pPaintingFrame4);
	}

	

	////////////yj
	{

		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(10.35f, 13.0f,1.0f);

		DecoObject* pDoorCollider = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-0.1f,-3.2f,-15.0f), physicsInfo, L"Deferred", L"");
		AddGameObject(pDoorCollider);

		yj::JarDoor* pJarDoor = Factory::CreateObject<yj::JarDoor>(Vec3::Zero, L"Deferred", L"", false, 2, pJarLDoor, pJarRDoor, pDoorCollider);
		AddGameObject(pJarDoor);

		//Ű+�Ķ��� �׾Ƹ� - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.192, 3.8f, 2.28f);

			pPot1 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(7.1f, -7.7f, -12.1f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\POT_Key.fbx");
			pPot1->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pPot1->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pPot1->SetReceiver(pJarDoor);
			AddGameObject(pPot1);
		}

		//Ű+�Ķ��� �׾Ƹ� �ι�° - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.192, 3.8f, 2.28f);

			yj::KeyPot* pPot2 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(-7.1f, -7.7f, -12.1f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\POT_Key.fbx");
			pPot2->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pPot2->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pPot2->SetReceiver(pJarDoor);
			AddGameObject(pPot2);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(9.2, 3.8f, 8.75f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(0.1f, -7.7f, -21.6f), physicsInfo, L"Deferred", L"",false,MapType::Right2Map);
			AddGameObject(pTelZone);
			SetGizmoTarget(pTelZone);
		}

	}
}

void EntranceHallMap::InitColliderAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(49.0f, 0.98f, 78.4f);

		Ground* pGroundCol = Factory::CreateObjectHasPhysical<Ground>(Vec3(-6.1f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pGroundCol);
	}

	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.98f, 49.74f, 78.4f);

		WallObject* pLWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.7f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pLWallCol);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.98f, 49.74f, 78.4f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.7f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pRWallCol);
	}
}