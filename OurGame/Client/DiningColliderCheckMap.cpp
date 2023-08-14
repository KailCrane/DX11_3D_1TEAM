#include "pch.h"
#include "DiningColliderCheckMap.h"
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
#include "WallObject.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PlayerMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"


namespace hm
{
	DiningColliderCheckMap::DiningColliderCheckMap()
		: Map(MapType::DiningColliderCheckMap)
	{
	}

	DiningColliderCheckMap::~DiningColliderCheckMap()
	{
	}

	void DiningColliderCheckMap::Initialize()
	{
		Map::Initialize();
	}

	void DiningColliderCheckMap::Update()
	{
		Map::Update();
	}

	void DiningColliderCheckMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void DiningColliderCheckMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void DiningColliderCheckMap::Render()
	{
		Map::Render();
	}

	void DiningColliderCheckMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);


		//���� �Ͼ������ ������ִ� �ڵ�
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
		

		//DecoObject == �ݶ��̴� ���� ������Ʈ
		//WallObject == �ݶ��̴� �ִ� ������Ʈ

		//Forward == �� ����� ���� ��ɾ�
		//Deferred == �� ����� �ִ� ��ɾ�
		
		//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
		//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�
		


		// ��ü�� ���̵���� ��
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx");

			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			AddGameObject(pNormalBase);
		}

		// 1�� �ٴ� - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 0.1f, 37.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

			pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));

			AddGameObject(pFloor);
		}

		// 2�� �ٴ� - floorextension_nocollider
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(27.2f, 0.1f, 19.f);

			Ground* pfloorextension_nocollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -1.87f, -15.4f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

			pfloorextension_nocollider->GetTransform()->SetScale(Vec3(110.f, 10.f, 145.f));
			pfloorextension_nocollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 62.5f));
			AddGameObject(pfloorextension_nocollider);
		}

		//1�� ��� - Stairs
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 14.f);

			Ground* pStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-12.f, -5.2f, 0.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

			pStairs->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
			pStairs->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
			pStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 1.f));
			pStairs->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
			AddGameObject(pStairs);
		}

		//1�� ��� �� - StairRailCollider
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.7f, 3.f, 16.f);

			Ground* pStairRailCollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(-9.8f, -4.f, 1.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\StairRailCollider.fbx");

			pStairRailCollider->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
			pStairRailCollider->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
			pStairRailCollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 0.0f));
			pStairRailCollider->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
			AddGameObject(pStairRailCollider);
		}


		//�ܰ� �����ִ� ��� ���� ���� �� -wallPanel_Merged
		{
			DecoObject* pWallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(0.2f, -5.2f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\wallPanel_Merged.fbx");

			pWallPanel_Merged->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			AddGameObject(pWallPanel_Merged);
		}
		
		// ��ũ�� ��� ���� �� -POT_Door_4_Variant
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.size = Vec3(3.8f, 5.f, 0.4f);

			WallObject* pPOT_Door = Factory::CreateObjectHasPhysical<WallObject>(Vec3(8.75f, -5.5f, -5.8f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\POT_Door_4_Variant.fbx");
			pPOT_Door->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pPOT_Door->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.5f, 4.7f));

			AddGameObject(pPOT_Door);
		}

		//������ -fireplace
		{
			DecoObject* pfireplace = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -5.f, -1.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fireplace.fbx");

			pfireplace->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			

			AddGameObject(pfireplace);
		}


		









		// Toy ��� �ϴ� ��ġ
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Sphere;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Forward", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			PlayerMoveScript* pPlayerSc =  pPlayer->AddComponent(new PlayerMoveScript);

			AddGameObject(pPlayer);
		}






		// Table // �׳� �ϴ°� ����
		/*{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(5.f, 10.f, 20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossTable.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(-90.f, 20.f, 0.f));
			AddGameObject(pDecoObject);
		}*/

		// Left Collider // �׷��� �Ȱ������� �ݶ��̴��� �����ϴ°�
		/*{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(13.f, 5.f, 17.f);

			WallObject* pWallObject = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.f, 2.5f, -36.f), info, L"Forward", L"");
			AddGameObject(pWallObject);
		}*/
	}

	void DiningColliderCheckMap::Exit()
	{
	}
}
