#include "pch.h"
#include "LeftSecretFightMap.h"
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


LeftSecretFightMap::LeftSecretFightMap()
	: Map(MapType::LeftSecretFightMap)
{
}

LeftSecretFightMap::~LeftSecretFightMap()
{
}

void LeftSecretFightMap::Initialize()
{
	Map::Initialize();
}

void LeftSecretFightMap::Update()
{
	Map::Update();
}

void LeftSecretFightMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void LeftSecretFightMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void LeftSecretFightMap::Render()
{
	Map::Render();
}

void LeftSecretFightMap::Enter()
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

	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"ObjectTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
	//Object->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); == �ؽ��� ��ȣ ����

	//Object->AddComponent(new PlacementScript); == Ű����� �����̴� ������Ʈ �̵� ��ũ��Ʈ
	//SetGizmoTarget(Object); == ����Ƽ ������� ���콺�� �����̴� ������Ʈ �̵� �Լ�


	//��ü���� ���̵� ���� - Room_Walls
	{
		DecoObject* pRoom_Walls = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Room_Walls.fbx");
		pRoom_Walls->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"EntranceHallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Room_Walls.fbm\\grandmaWallPaperTexture.png");
		pRoom_Walls->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); // �ؽ��� ������ �����Ű�¹�

		pRoom_Walls->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pRoom_Walls);
	}

	// 1�� �ٴ� - Grimace_Decay_Floor
	{
		DecoObject* pGrimace_Decay_Floor = Factory::CreateObject<DecoObject>(Vec3(-4.8f, -9.f, 9.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Grimace_Decay_Floor.fbx");
		pGrimace_Decay_Floor->GetTransform()->SetScale(Vec3(39.f, 40.f, 38.f));

		//shared_ptr<Texture> pTexture2 = GET_SINGLE(Resources)->Load<Texture>(L"Grimace_Decay_FloorTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Grimace_Decay_Floor.fbm\\grandmaFloorNewTest.png");
		//pGrimace_Decay_Floor->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture2); // �ؽ��� ������ �����Ű�¹�

		pGrimace_Decay_Floor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.01f, 0.01f));

		AddGameObject(pGrimace_Decay_Floor);
	}

	// 2�� �ٴ� - Floor
	{
		DecoObject* pFloor = Factory::CreateObject<DecoObject>(Vec3(10.44f, -2.3f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Floor.fbx");
		pFloor->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		pFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pFloor);
	}

	//2�� �Ⱥ��̴� �� - Wall
	{
		DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(5.54f, 1.14f, -17.41f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Wall.fbx");
		pWall->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));

		pWall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pWall);
	}

#pragma region "������"
	//������ 1 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-20.3f, -8.45f, 7.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(33.5f, 30.f, 30.f));

		

		AddGameObject(pWallRim);
	}

	//������ 2 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-17.06f, -8.45f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(7.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//������ 3 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(1.2f, -8.45f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(18.5f, 30.f, 30.f));


		
		AddGameObject(pWallRim);
	}

	//������ 4 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(15.4f, -2.3f, 24.81f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(10.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//������ 5 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(20.5f, 8.6f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(49.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//������ 6 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.5f, 8.6f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(20.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//������ 7 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-10.f, 4.7f, -8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(20.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}
#pragma endregion

#pragma region "����"
	//���� 1 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(10.4f , -1.62f , 17.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(14.f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}
	//���� 2 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(10.4f, -1.62f, -2.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(12.5f, 8.f, 8.f));


		AddGameObject(pCeilingBeamLow);
	}

	//���� 3 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(5.3f, -1.62f, -8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(9.f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}

	//���� 4 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(0.4f, 5.38f, -17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(15.5f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}
#pragma endregion

	//������ũ �� - SpikeDoor_avatest
	{
		DecoObject* pSpikeDoor_avatest = Factory::CreateObject<DecoObject>(Vec3(-10.8f, -6.5f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\SpikeDoor_avatest.fbx");
		pSpikeDoor_avatest->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pSpikeDoor_avatest->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));

		AddGameObject(pSpikeDoor_avatest);
	}


}

void LeftSecretFightMap::Exit()
{
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
}