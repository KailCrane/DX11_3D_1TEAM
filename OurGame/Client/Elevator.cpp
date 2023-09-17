#include "pch.h"

#include "Elevator.h"

//������Ʈ�� ���� �ֱ� ����
#include "Scene.h"
#include "SceneManager.h"

//������Ʈ ������ ����
#include "Factory.h"

//�׽�Ʈ�� Input
#include "Input.h"

#include "Timer.h"

namespace yj
{
	Elevator::Elevator()
		: GameObject(LayerType::Ground),
		direction(0),
		state(StandbyDown),
		isPlayerIn(false)
	{
	}
	Elevator::~Elevator()
	{
	}
	void Elevator::Initialize()
	{
		GameObject::Initialize();

		Scene* mScene = SceneManager::GetInstance()->GetScene(SceneType::MainOfficeMap); //������ ���� �޾Ƽ� �־���� �ϳ� �����̺����� ����� ���� ���� ���ǽ� ������ ���ԵǾ� �ֱ� ������ ����ȭ�� ���� ���� �־��־���.

	

		pMoveFrame= Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Hod_Elevator.fbx");
		mScene->AddGameObject(pMoveFrame);

		pMoveFrame->GetTransform()->SetPosition(Vec3(-11.5f, -3.7f, -18.6));
		pMoveFrame->GetTransform()->SetRotation(Vec3(0.0f, 89.72f, 0.0f));
		pMoveFrame->GetTransform()->SetScale(Vec3(11.5f, 11.5f, 11.5f));

		DecoObject* pElevatorFrame = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\ElevatorFrame.fbx");

		pElevatorFrame->GetTransform()->SetPosition(Vec3(-11.5f, 3.9f, -18.0));
		pElevatorFrame->GetTransform()->SetRotation(Vec3(0.0f, 135.0f, 0.0f));
		pElevatorFrame->GetTransform()->SetScale(Vec3(26.0f, 26.0f, 26.0f));
		mScene->AddGameObject(pElevatorFrame);

		PhysicsInfo moveFrameInfo;
		moveFrameInfo.eActorType = ActorType::Kinematic;
		moveFrameInfo.eGeometryType = GeometryType::Box;
		moveFrameInfo.size = Vec3(4.0f, 0.5f, 4.0f);
		pElevatorCol = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(0, 0, 0), moveFrameInfo, L"Deferred", L"");
		mScene->AddGameObject(pElevatorCol);

		

#pragma region "���� �ٸ�����Ʈ"

		{
			PhysicsInfo mUpBarricadePhyInfo;
			mUpBarricadePhyInfo.eActorType = ActorType::Kinematic;
			mUpBarricadePhyInfo.eGeometryType = GeometryType::Box;
			mUpBarricadePhyInfo.size = Vec3::One;

			pUpperBarricade = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-8.2f, 1.1f, -18.0f), mUpBarricadePhyInfo, L"Deferred", L"");
			pUpperBarricade->GetRigidBody()->SetGeometrySize(Vec3(0.41f,2.4f,3.9f));
			mScene->AddGameObject(pUpperBarricade);
		}
#pragma endregion


#pragma region "�Ʒ� �ٸ�����Ʈ"
		{
			PhysicsInfo mBelowBarricadePhyInfo;
			mBelowBarricadePhyInfo.eActorType = ActorType::Static;
			mBelowBarricadePhyInfo.eGeometryType = GeometryType::Box;
			mBelowBarricadePhyInfo.size = Vec3::One;

			pBelowBarricade = Factory::CreateObjectHasPhysical<DecoObject>(Vec3::Zero, mBelowBarricadePhyInfo, L"Deferred", L"");
			pBelowBarricade->GetTransform()->SetPosition(Vec3(-11.6f, -7.6f, -15.6f));
			pBelowBarricade->GetRigidBody()->SetGeometrySize(Vec3(4.1f, 2.4f, 1.0f));

			mScene->AddGameObject(pBelowBarricade);
		}
#pragma endregion

#pragma region "üĿ_��"
		{
			PhysicsInfo mUpperCheckerPhyInfo;
			mUpperCheckerPhyInfo.eActorType = ActorType::Kinematic;
			mUpperCheckerPhyInfo.eGeometryType = GeometryType::Box;
			mUpperCheckerPhyInfo.size = Vec3::One;

			pUpperChecker = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-6.8f, 0.9f, -18.6f), mUpperCheckerPhyInfo, L"Deferred", L"");
			pUpperChecker->GetRigidBody()->SetGeometrySize(Vec3(1.0f, 1.0f, 4.7f));
			mScene->AddGameObject(pUpperChecker);
		}
#pragma endregion

#pragma region "üĿ_�Ʒ�"
		{
			PhysicsInfo mBelowCheckerPhyInfo;
			mBelowCheckerPhyInfo.eActorType = ActorType::Kinematic;
			mBelowCheckerPhyInfo.eGeometryType = GeometryType::Box;
			mBelowCheckerPhyInfo.size = Vec3::One;

			pBelowChecker = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-11.5f, -8.4f, -14.3f), mBelowCheckerPhyInfo, L"Deferred", L"");
			pUpperChecker->GetRigidBody()->SetGeometrySize(Vec3(3.0f, 1.0f, 1.0f));
			mScene->AddGameObject(pBelowChecker);
		}
#pragma endregion


	}

	void Elevator::Start()
	{

	}

	void Elevator::Update()
	{
		GameObject::Update();
		//1�� �Ʒ� �ݶ��̴��� �ε����ٰ� ����
		
		if (state == Move)
		{
			ElevatorMove();
		}
		CheckPlayerStayFront();

		if (IS_DOWN(KeyType::U))
		{
			isPlayerIn = true;
		}
		if (IS_DOWN(KeyType::I))
		{
			isPlayerIn = false;
		}
		if (pElevatorCol->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
		{
			isPlayerIn = true;
		}
		/*else
		{
			isPlayerIn = false;
		}*/

		if (state == StandbyUp || state == StandbyDown)
		{
			if (isPlayerIn)
			{
				if (state == StandbyUp)
				{
					direction = 0;
				}
				if (state == StandbyDown)
				{
					direction = 1;
				}
				state = Move;
			}
		}

		if (state == ArriveDown || state == ArriveUp)
		{
			if (!isPlayerIn)
			{
				if (ArriveDown)
				{
				   state = StandbyDown;
				}
				if (ArriveUp)
				{
					state = StandbyUp;
				}
			}
		}
		Vec3 parent_pos = pMoveFrame->GetTransform()->GetPosition();
		Vec3 fixed_pos = Vec3(parent_pos.x, parent_pos.y - 5.5f, parent_pos.z);
		pElevatorCol->GetTransform()->SetPosition(Vec3(fixed_pos));
	}


	void Elevator::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Elevator::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Elevator::Render()
	{
		GameObject::Render();
	}

	void Elevator::Destroy()
	{
		GameObject::Destroy();
	}

	void Elevator::ElevatorMove()
	{
		if (direction == 0)
		{
			Vec3 mFramePos = pMoveFrame->GetTransform()->GetPosition();
			Vec3 mFixedPos = Vec3(mFramePos.x, mFramePos.y -= frameCurrSpeed * DELTA_TIME, mFramePos.z);

			pMoveFrame->GetTransform()->SetPosition(mFixedPos);
			if (mFixedPos.y <= belowLimit)
			{
				if (isPlayerIn)
				{
					state = ArriveDown;
				}
				else
				{
					state = StandbyDown;
				}
				BarricadeOff(0);
				BarricadeOff(1);
			}
		}
		else
		{
			Vec3 mFramePos = pMoveFrame->GetTransform()->GetPosition();
			Vec3 mFixedPos = Vec3(mFramePos.x, mFramePos.y + frameCurrSpeed * DELTA_TIME, mFramePos.z);

			pMoveFrame->GetTransform()->SetPosition(mFixedPos);
			if (pMoveFrame->GetTransform()->GetPosition().y >= upLimit)
			{
				if (isPlayerIn)
				{
					state = ArriveUp;
				}
				else
				{
					state = StandbyUp;
				}
				BarricadeOff(0);
				BarricadeOff(1);
			}
		}
	}

	void Elevator::CheckPlayerStayFront()
	{

		if (IS_DOWN(KeyType::Y))
			//if (pBelowChecker->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
		{
			if (CheckState(StandbyDown))
			{
				return;
			}
			else
			{
				direction = 0;
				state = Move;
				BarricadeOn(0);
				BarricadeOn(1);
			}
			//
		}
		if (IS_DOWN(KeyType::T))
			//else if (pUpperChecker->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
		{
			if (state == StandbyUp)
			{
				return;
			}
			else
			{
				direction = 1;
				state = Move;
				BarricadeOn(0);
				BarricadeOn(1);
			}
		}

	}

	void Elevator::BarricadeOn(int num)
	{
		if (num == 0)
		{
			pUpperBarricade->Enable();
		}
		else
		{
			pBelowBarricade->Enable();
		}
	}

	void Elevator::BarricadeOff(int num)
	{
		if (num == 0)
		{
			pBelowBarricade->Disable();
		}
		else
		{
			pUpperBarricade->Disable();
		}
	}
}


