#include "pch.h"
#include "EntranceHallMap.h"
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
	//Object->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);

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
		SetGizmoTarget(pColumnFull);
		AddGameObject(pColumnFull);
	}
#pragma endregion





}

void EntranceHallMap::Exit()
{
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
}
