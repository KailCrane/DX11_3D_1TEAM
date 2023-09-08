#include "pch.h"
#include "Monster_Player_TestScene.h"
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
#include "Npc.h"
#include "Monster.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"


namespace hm {

	Monster_Player_TestScene::Monster_Player_TestScene()
		: Map(MapType::Monster_Player_Test)
	{
	}
	Monster_Player_TestScene::~Monster_Player_TestScene()
	{
	}
	void Monster_Player_TestScene::Initialize()
	{
		Map::Initialize();
	}
	void Monster_Player_TestScene::Start()
	{
		Map::Start();
	}
	void Monster_Player_TestScene::Update()
	{
		Map::Update();
	}
	void Monster_Player_TestScene::FixedUpdate()
	{
		Map::FixedUpdate();
	}
	void Monster_Player_TestScene::FinalUpdate()
	{
		Map::FinalUpdate();
	}
	void Monster_Player_TestScene::Render()
	{
		Map::Render();
	}
	void Monster_Player_TestScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		// 1�� �ٴ� - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 0.1f, 37.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

			pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));
			pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));

			AddGameObject(pFloor);
		}

		// Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			//pPlayer->AddComponent(new TestAnimationScript);
			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			
		}

		// PotHead
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Npc* pPotHead = Factory::CreateObjectHasPhysical<Npc>(Vec3(5.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Npc\\Npc_PotHead.fbx");
			pPotHead->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			pPotHead->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			// �ִϸ��̼��� �̸��� FBX�� ����Ǿ� �ִ� ���� �״�� �������Ƿ� �ش� FBX�� ����ϴ� Ŭ������ �����ڿ� ���� Ư�� �κп���
			// ����ϱ� ���� �̸����� �ϰ������� �ٲ��� �ʿ䰡 ����
			pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

			// �ݺ� ���θ� �����ϴ� �Լ� (Finished �÷��׸� ����� �� ����)
			pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

			// �ε��� ��ȣ�ε� ��� ����
			pPotHead->GetAnimator()->SetLoop(9, true);

			// HasExit�� ���� �ִϸ��̼� �����߿� �ٸ� �ִϸ��̼��� ����Ǿ��� �� �ٷ� �ѱ���� ���θ� ���� (�⺻������ true)
			// �� ���� false�� �ִϸ��̼� �÷��� ���� �ٸ� �ִϸ��̼� Play�� ����Ǿ��� �� ���� �ִϸ��̼��� �� ������ �����
			pPotHead->GetAnimator()->SetHasExitFlag(9, false);

			// �ִϸ��̼� �����ϴ� ����� 2D�� ����ϰ� �ִϸ��̼� �̸�, �ݺ��Ұ��� ���θ� �־��ָ� ��
			pPotHead->GetAnimator()->Play(L"PotHead_Idle", true);

			AddGameObject(pPotHead);
			//SetAnimTarget(pPotHead);
		}

		// �����
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_HEADROLLER = Factory::CreateObjectHasPhysical<Monster>(Vec3(3.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_HEADROLLER.fbx");
			p_E_HEADROLLER->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_HEADROLLER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_HEADROLLER);
			AddGameObject(p_E_HEADROLLER);
			//SetAnimTarget(p_E_HEADROLLER);
		}

		// �ʷϰŹ�
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_LURKER = Factory::CreateObjectHasPhysical<Monster>(Vec3(1.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_LURKER.fbx");
			p_E_LURKER->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_LURKER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_LURKER);
			AddGameObject(p_E_LURKER);
			//SetAnimTarget(p_E_LURKER);
		}
		
		// �߰����� ����Ʈ
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_KNIGHT = Factory::CreateObjectHasPhysical<Monster>(Vec3(-1.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_KNIGHT.fbx");
			p_E_KNIGHT->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_KNIGHT->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_KNIGHT);
			AddGameObject(p_E_KNIGHT);
			//SetAnimTarget(p_E_KNIGHT);
		}

		// ������
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_MAGE = Factory::CreateObjectHasPhysical<Monster>(Vec3(-3.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_MAGE.fbx");
			p_E_MAGE->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_MAGE->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_MAGE);
			AddGameObject(p_E_MAGE);
			//SetAnimTarget(p_E_MAGE);
		}

		// �߰����� �����
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_GRIMACE_KNIGHT = Factory::CreateObjectHasPhysical<Monster>(Vec3(-5.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
			p_E_GRIMACE_KNIGHT->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_GRIMACE_KNIGHT);
			AddGameObject(p_E_GRIMACE_KNIGHT);
			//SetAnimTarget(p_E_GRIMACE_KNIGHT);
		}

		// ����
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_BAT_White = Factory::CreateObjectHasPhysical<Monster>(Vec3(-9.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
			p_E_BAT_White->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_BAT_White->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_BAT_White);
			AddGameObject(p_E_BAT_White);
			//SetAnimTarget(p_E_BAT_White);
		}

		// �׾Ƹ� �̹�
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* pPOT_Mimic_Melee = Factory::CreateObjectHasPhysical<Monster>(Vec3(-11.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\POT_Mimic_Melee.fbx");
			pPOT_Mimic_Melee->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			pPOT_Mimic_Melee->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(pPOT_Mimic_Melee);
			AddGameObject(pPOT_Mimic_Melee);
			//SetAnimTarget(pPOT_Mimic_Melee);
		}

		//�������� �ҸӴ� - _E_Grandma
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_Grandma = Factory::CreateObjectHasPhysical<Monster>(Vec3(-11.f, 0.f, 5.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_Grandma.fbx");
			p_E_Grandma->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_Grandma->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_Grandma);
			AddGameObject(p_E_Grandma);
			//SetAnimTarget(p_E_Grandma);
		}


	}
	void Monster_Player_TestScene::Exit()
	{
	}
}