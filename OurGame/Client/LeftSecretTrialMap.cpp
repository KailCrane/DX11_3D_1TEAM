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


	
#pragma region "���"
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
#pragma endregion

#pragma region "������"
	{
		//������ ��� õ�� 1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(5.4f, 4.1f, 11.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 2 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(6.5f, 4.1f, -13.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 3 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.7f, 4.1f, -11.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			
			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 4 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(2.f, 4.1f, -18.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 5 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-4.f, 4.1f, -17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� õ�� 6 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-3.2f, 4.1f, -22.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ�7 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-9.3f, -1.6f, -17.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 8 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-4.1f, -1.6f, -17.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 8_1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(3.48f, -3.9f, -18.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 25.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			
			AddGameObject(pbannisterTop);
		}

		//������ ��� ������ �ٴ� 9 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-3.2f, -1.6f, -18.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 10 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -3.9f, 6.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 10_1 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.7f, -3.9f, 6.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
			AddGameObject(pbannisterTop);
		}

		//������ ��� �߰� �ٴ� 11 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.7f, -1.6f, 6.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 40.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 12 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(-9.22f, -1.6f, 7.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 12.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 13 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(3.48f, -1.6f, 1.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 25.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pbannisterTop);
		}

		//������ ��� �� �ٴ� 14 - bannisterTop
		{
			DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(3.48f, -0.5f, 1.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\bannisterTop.fbx");
			pbannisterTop->GetTransform()->SetScale(Vec3(50.f, 50.f, 25.f));
			pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pbannisterTop);
		}
	}
#pragma endregion

#pragma region "���� ����"
	{
		//������ 1 - painting4Frame01
		{
			DecoObject* pPainting4Frame01 = Factory::CreateObject<DecoObject>(Vec3(5.3f, 2.4f, 12.6f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame01.fbx");
			pPainting4Frame01->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPainting4Frame01->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
			
			AddGameObject(pPainting4Frame01);
		}

		//������ 2 - painting4Frame02
		{
			DecoObject* pPainting4Frame02 = Factory::CreateObject<DecoObject>(Vec3(5.4f, 2.2f, 6.9f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame02.fbx");
			pPainting4Frame02->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pPainting4Frame02->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
		
			AddGameObject(pPainting4Frame02);
		}

		//������ 3 - painting4Frame03
		{
			DecoObject* pPainting4Frame03 = Factory::CreateObject<DecoObject>(Vec3(5.4f, 1.3f, 16.0f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame03.fbx");
			pPainting4Frame03->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pPainting4Frame03->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
		
			AddGameObject(pPainting4Frame03);
		}

		//������ 4 - painting4Frame04
		{
			DecoObject* pPainting4Frame04 = Factory::CreateObject<DecoObject>(Vec3(-4.2f, 1.8f, -6.3f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame04.fbx");
			pPainting4Frame04->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pPainting4Frame04->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
			
			AddGameObject(pPainting4Frame04);
		}

		//������ 5 - painting4Frame05
		{
			DecoObject* pPainting4Frame05 = Factory::CreateObject<DecoObject>(Vec3(5.3f, 2.2f, 14.2f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame05.fbx");
			pPainting4Frame05->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pPainting4Frame05->GetTransform()->SetRotation(Vec3(0.f, 00.f, 0.f));
		
			AddGameObject(pPainting4Frame05);
		}

		//������ 6 - painting4Frame06
		{
			DecoObject* pPainting4Frame06 = Factory::CreateObject<DecoObject>(Vec3(4.7f, -0.4f, 4.8f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\painting4Frame06.fbx");
			pPainting4Frame06->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
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
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.35f, -0.67f, 7.06f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(27.f, 27.f, 27.f));
				
				AddGameObject(pWallPanel);
			}

			//�� �г� 2
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.35f, -0.67f, 10.96f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(27.f, 27.f, 27.f));
				
				AddGameObject(pWallPanel);
			}

			//�� �г� 3
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.35f, -0.67f, 16.46f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(27.f, 27.f, 30.f));
				
				AddGameObject(pWallPanel);
			}

			//�� �г� 4
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.35f, -0.67f, 3.39f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(27.f, 27.f, 33.f));
				
				AddGameObject(pWallPanel);
			}

			//�� �г� 5
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(15.25f, -0.67f, -13.31f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\WallPanel.fbx");
				pWallPanel->GetTransform()->SetScale(Vec3(27.f, 27.f, 29.f));
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
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -2.8f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 2
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.2f, -2.8f, -14.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 3
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-3.2f, -2.8f, -14.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 4
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-3.2f, -2.8f, -12.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 5
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -2.8f, -12.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 6
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -2.8f, -9.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 7
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-4.6f, -2.8f, -9.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 8
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-1.3f, -2.8f, -9.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 9
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-3.2f, -2.8f, -7.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 10
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-3.2f, -2.8f, -4.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.2f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 11
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-5.6f, -2.8f, -6.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.7f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 12
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-1.1f, -2.8f, -3.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.1f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}

	{
		//�������� �����ʺ��� 13
		DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-5.6f, -2.8f, -3.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
		pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pTwoTierShelf->GetTransform()->SetScale(Vec3(3.7f, 3.5f, 3.2f));
		
		AddGameObject(pTwoTierShelf);
	}
#pragma endregion
#pragma region "�������ݾȿ��ִ� ��� �ڽ� ����"
	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-6.9f, -2.4f, -0.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.f,0.f,0.f));
		
		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-7.2f ,-2.3f ,0.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(30.f, 35.f, 35.f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.f, 0.f, 10.f));
		
		AddGameObject(pEmptyBox);
	}

	{
		//�ڽ�- EmptyBox
		DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-6.9f, -2.4f, 1.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\EmptyBox.fbx");
		pEmptyBox->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));
		pEmptyBox->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
	
		AddGameObject(pEmptyBox);
	}
#pragma endregion
	





	// Ŀư - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(0.3f, 3.5f, 3.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(42.f, 42.f, 42.f));
		
		AddGameObject(pCurtainHorizontal);
	}

	//Ŀư �Ʒ��� - CurtainVertical
	{
		DecoObject* pCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(0.6f, -0.2f, 4.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainVertical.fbx");
		pCurtainVertical->GetTransform()->SetScale(Vec3(42.f, 42.f, 42.f));
		
		AddGameObject(pCurtainVertical);
	}

	// Ŀư 2 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(17.2f, 3.5f, -17.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(42.f, 42.f, 42.f));
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		AddGameObject(pCurtainHorizontal);
	}

	//Ŀư 2 �Ʒ��� - CurtainVertical
	{
		DecoObject* pCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(18.5f, -0.2f, -17.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\CurtainVertical.fbx");
		pCurtainVertical->GetTransform()->SetScale(Vec3(42.f, 42.f, 42.f));
		pCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		
		AddGameObject(pCurtainVertical);
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