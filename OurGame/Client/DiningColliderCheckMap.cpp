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
#include "PlacementScript.h"

/* Event */
#include "SceneChangeEvent.h"


namespace sy
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

		//if (mTarget != nullptr)
		//{
		//	if (IS_UP(KeyType::LEFT))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
		//		mTarget->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::RIGHT))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::UP))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::DOWN))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::Z))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::X))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
		//		mTarget->GetTransform()->SetPosition(fixed_pos);

		//	}
		//	if (IS_UP(KeyType::R)) //ȸ��
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}
		//	if (IS_UP(KeyType::T)) //ȸ��
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}

		//	if (IS_UP(KeyType::Y)) //ȸ��
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}
		//	if (IS_UP(KeyType::U)) //ȸ��
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}

		//	if (IS_UP(KeyType::O)) //������ - ��ü�� Ű���
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::P)) //������ - ��ü�� ���̱�
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::K)) //������ - y������ Ű���
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y, target_scale.z += 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::L)) //������ - y�� ���� ���̱�
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y, target_scale.z -= 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::N)) //������ -y�ุ Ű���
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y += 0.5, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::M)) //������ -y�ุ ���̱�
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y -= 0.5, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::H)) //������ - x�ุ Ű���
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x +=0.5, target_scale.y, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::J)) //������ -x�ุ ���̱�
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -=0.5, target_scale.y, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::F)) //������ -z�ุ Ű���
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z += 0.5);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::G)) //������ -z�ุ ���̱�
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z -= 0.5);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::ENTER))
		//	{
		//		Vec3 a = mTarget->GetTransform()->GetPosition();
		//		Vec3 b = mTarget->GetTransform()->GetRotation();
		//		Vec3 c = mTarget->GetTransform()->GetScale();
		//		int d = 0;


		//	}
		//}
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
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));


#pragma region "����"
#pragma endregion

		//DecoObject == �ݶ��̴� ���� ������Ʈ
		//WallObject == �ݶ��̴� �ִ� ������Ʈ

		//Forward == �� ����� ���� ��ɾ�
		//Deferred == �� ����� �ִ� ��ɾ�

		//->GetTransform()->SetPositionExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [�̵�] ��Ű�� �Լ�
		//->GetTransform()->SetRotationExcludingColliders == �ݶ��̴��� �����ϰ� ������Ʈ�� [ȸ��] ��Ű�� �Լ�



		// ��ü�� ���̵���� ��
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx",true);

			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pNormalBase->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr,2,0); //3��°���� == �ؽ�ó ù��° png ���� �ι�° png���� �����ϰ� ���ִ°�
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(115, 118, 128),2,0); //3��°���� == �ؽ�ó ù��° png ���� �ι�° png���� �����ϰ� ���ִ°�
			AddGameObject(pNormalBase);
		}

#pragma region "1��"
		//1��
		{
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

			{
				//1-2�� ��� �� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-16.7f, -0.7f, -6.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
				AddGameObject(pColumnFull);
			}

			//1�� ��� �� - Cube1 
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube1 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-9.8f, -4.f, 1.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube1.fbx");

				pCube1->GetTransform()->SetScale(Vec3(30.f, 26.f, 25.f));
				pCube1->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
				pCube1->GetTransform()->SetPositionExcludingColliders(Vec3(8.f, -0.3f, -1.0f));
				pCube1->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube1);
			}

			{
				//1�� �Ǿ� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.f, 3.f, 25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 40.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//1�� ���� ���� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.5f, -2.8f, -5.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 22.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}



			//�ܰ� �����ִ� ��� ���� ���� �� -wallPanel_Merged
			{
				DecoObject* pWallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(0.2f, -5.35f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\wallPanel_Merged.fbx");

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

			// ��ũ�� �� ������ ���� - DoorFrame
			{
				DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(8.75f, -6.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\DoorFrame.fbx");

				pDoorFrame->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

				AddGameObject(pDoorFrame);
			}

			//������ -fireplace
			{
				DecoObject* pfireplace = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -5.f, -1.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fireplace.fbx");

				pfireplace->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


				AddGameObject(pfireplace);
			}

			//1�� �ٴ� ���� �׵θ� - RimStarter
			{
				DecoObject* pRimStarter = Factory::CreateObject<DecoObject>(Vec3(-0.3f, -8.5f, 3.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\RimStarter.fbx");

				pRimStarter->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));


				AddGameObject(pRimStarter);
			}
		}
#pragma endregion

#pragma region "2��"

		//2��
		{
			// 2�� �ٴ� - floorextension_nocollider
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(27.2f, 0.1f, 19.f);

				Ground* pfloorextension_nocollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -1.87f, -15.4f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

				pfloorextension_nocollider->GetTransform()->SetScale(Vec3(110.f, 10.f, 145.f));
				pfloorextension_nocollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 62.5f));
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
				AddGameObject(pfloorextension_nocollider);
			}

			//2�� ��� - Stairs
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(5.f, 0.1f, 14.2f);

				Ground* pStairs_2floor = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.2f, 1.6f, -22.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

				pStairs_2floor->GetTransform()->SetScale(Vec3(15.f, 15.5f, 15.f));
				pStairs_2floor->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pStairs_2floor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.1f, 0.f));
				pStairs_2floor->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));

				
				AddGameObject(pStairs_2floor);
			}

			{
				//2�� ��� �Ʒ� ������ - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(5.6f, -1.8f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
			
				AddGameObject(pWallRim);

			}

			{
				//2�� ���-�� ���� ������ - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-3.4f, -1.8f, -25.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}

			//2�� ��� �� ����- Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -20.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			//2�� ��� �� ������ - Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -25.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			{
				//2�� ���� �Ʒ� ������ - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -1.9f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}
			{
				//2�� ���� �� ������ - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -0.4f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}


			// 2�� ��� �Ʒ��� - Cube3
			{
				DecoObject* pCube3 = Factory::CreateObject<DecoObject>(Vec3(3.f, 0.5f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube3.fbx");

				pCube3->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));
				pCube3->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pCube3);
			}

			{
				//2�� �Ǿ� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -6.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);


			}

			{
				//2�� �߰� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -13.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2�� ��� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 2.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2�� ��� �� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2�� ��� �� ���� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -24.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2-3�� ��� ���� ���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2�� �ǿ����� ū���
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-27.6f, 6.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2�� ���� ����� - BannisterStick
				for (float i = 0; i < 12; i++)
				{
					DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(7.5f - (i * 1.5f), -1.f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

					pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
					pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

					AddGameObject(pBannisterStick);

				}
			}

		}
#pragma endregion

#pragma region "3��"
		// 3�� �ٴ� �ݶ��̴�
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.5f, 0.1f, 50.f);

			Ground* pWallObject = Factory::CreateObjectHasPhysical<Ground>(Vec3(11.f, 4.9f, 0.f), info, L"Forward", L"");
			AddGameObject(pWallObject);
		}

		// 3�� �ٴ� - floorextension_nocollider
		{
			Ground* pfloorextension_nocollider = Factory::CreateObject<Ground>(Vec3(11.5f, 5.f, 169.8f), L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

			pfloorextension_nocollider->GetTransform()->SetScale(Vec3(20.f, 10.f, 400.f));
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
			AddGameObject(pfloorextension_nocollider);
		}

		{
			//3�� ���� Ŀư 1 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 18.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3�� ���� Ŀư 2 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 9.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3�� ���� Ŀư 3 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}


		{
			//3�� ���� Ŀư 4 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -11.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3�� ���� Ŀư 5 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3�� ���� Ŀư 6 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3�� ���� Ŀư 7 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-7.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}





		{
			//3�� ���� ���� ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3�� �߰� ���� ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3�� ���� �ǿ��� ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.4f, 6.2f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);

		}

		
		{
			//3�� ���� �ǿ��� �ι�° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pColumnFull);
		}

		{
			//3�� ���� �ǿ��� ����° ���
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 13.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}

		{
			//3�� ���� �� ����� �Ʒ� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);
			
		}

		{
			//3�� ���� �� ����� �� ������ 
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);
			
		}

		{
			//3�� ���� �� ����� �ݴ��� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.1f, 5.1f, 10.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 72.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			
			AddGameObject(pWallRim);
		}

		{
			//3�� ���� �� ����� �ݴ��� õ�� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.3f, 14.2f, 12.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 73.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
		

			AddGameObject(pWallRim);
		}

		{
			//3�� ���� �� õ�� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-5.7f, 14.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 40.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			

			AddGameObject(pWallRim);
		}

		{
			//3�� ���� ª�� ����� �Ʒ� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3�� ���� ª�� ����� �� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//3�� ���� ª�� ����� ���� /  �Ʒ� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 5.1f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3�� ���� ª�� ����� ���� / �� ������ - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 6.5f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//���� ����� - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//���� ����� - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 20.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//���� ����� - BannisterStick
			for (float i = 0; i < 9; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 11.7f-(i*2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");
				
				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//���� ����� - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -7.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//���� ����� - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -14.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}


		


#pragma endregion






		
		

		









		// Toy ��� �ϴ� ��ġ
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Sphere;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			PlayerMoveScript* pPlayerSc =  pPlayer->AddComponent(new PlayerMoveScript);
	
			AddGameObject(pPlayer);
		}*/






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
