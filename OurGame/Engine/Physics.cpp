#include "pch.h"
#include "Physics.h"
#include "ContactCallback.h"
#include "Timer.h"
#include "GameObject.h"
#include "RigidBody.h"

namespace hm
{
	Physics::Physics()
		:mpFoundation(nullptr)
	    ,mpPhysics(nullptr)
		,mpTransfort(nullptr)
		,mpPvd(nullptr)
		,mpSceneClient(nullptr)
		,mpScene(nullptr)
		,mpControllerMgr(nullptr)
		,mpCpuDispatcher(nullptr)
		,mpCallback(nullptr)
		,mGravity(0.f, -9.81f, 0.f)
	{
	}
	Physics::~Physics()
	{
		mpCpuDispatcher->release();

		SAFE_DELETE(mpCallback);
		mpControllerMgr->release();
		mpScene->release();
		mpPhysics->release();
		mpCooking->release();
		mpPvd->release();
		mpTransfort->release();
		mpFoundation->release();
	}
	void Physics::Initialize()
	{
		mpFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mAllocCallback, mErrorCallback);

		mpTransfort = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		mpPvd = PxCreatePvd(*mpFoundation);
		mpPvd->connect(*mpTransfort, PxPvdInstrumentationFlag::eALL);

		mpPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mpFoundation, PxTolerancesScale(), false, mpPvd);
		mpCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mpFoundation, PxCookingParams(mpPhysics->getTolerancesScale()));

		mpCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		mpCallback = new ContactCallback;

		PxSceneDesc sceneDesc(mpPhysics->getTolerancesScale());
		sceneDesc.gravity = mGravity;
		sceneDesc.cpuDispatcher = mpCpuDispatcher;
		sceneDesc.filterShader = PlayerFilterShader;
		sceneDesc.broadPhaseType = PxBroadPhaseType::eABP;
		sceneDesc.simulationEventCallback = mpCallback;

		mpScene = mpPhysics->createScene(sceneDesc);
		mpSceneClient = mpScene->getScenePvdClient();

		mpSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		mpSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		mpSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);

		mpControllerMgr = PxCreateControllerManager(*mpScene);
	}

	void Physics::Update()
	{
		mpScene->simulate(DELTA_TIME);
		mpScene->fetchResults(true);
	}

	void Physics::Render()
	{

	}

	void Physics::AddActor(GameObject* _pGameObject)
	{
		AssertEx(_pGameObject, L"Physics::AddActor() - GameObject is nullptr");
		AssertEx(_pGameObject->GetRigidBody(), L"Physics::AddActor() - RigidBody is nullptr");
		AssertEx(_pGameObject->GetRigidBody()->IsAppliedPhysics(), L"Physics::AddActor() - Is not applied physics");
		mpScene->addActor(*_pGameObject->GetRigidBody()->GetActor());
	}

	void Physics::RemoveActor(GameObject* _pGameObject)
	{
		AssertEx(_pGameObject, L"Physics::RemoveActor() - GameObject is nullptr");
		AssertEx(_pGameObject->GetRigidBody(), L"Physics::RemoveActor() - RigidBody is nullptr");
		AssertEx(_pGameObject->GetRigidBody()->IsAppliedPhysics(), L"Physics::RemoveActor() - Is not applied physics");
		mpScene->removeActor(*_pGameObject->GetRigidBody()->GetActor());
	}


	PxFilterFlags Physics::PlayerFilterShader(PxFilterObjectAttributes _attributes0, PxFilterData _filterData0, PxFilterObjectAttributes _attributes1, PxFilterData _filterData1, PxPairFlags& _pairFlags, const void* _pConstantBlock, PxU32 _constantBlockSize)
	{
		// Ʈ���ſ� Ʈ���� �Ǵ� Ʈ���ſ� �浹�ϴ� ��ü�� �����Ͽ� ó���մϴ�.
		if (PxFilterObjectIsTrigger(_attributes0) || PxFilterObjectIsTrigger(_attributes1))
		{
			//if ((_filterData1.word1 & _filterData0.word0) || (_filterData0.word1 & _filterData1.word0))
			//{
				// Ʈ���ſ� �浹�ϴ� ��ü ��� OnTrigger �̺�Ʈ�� ó���ϵ��� �մϴ�.
				_pairFlags = PxPairFlag::eTRIGGER_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST;
				return PxFilterFlag::eDEFAULT;
			//}
		}

		// �浹�ϴ� ��ü�� ��� �浹 �÷��׸� �����մϴ�.
		_pairFlags = PxPairFlag::eCONTACT_DEFAULT;

		// �� ���Ͱ� ���� �浹�÷��װ� ������ ���� ���
		if ((_filterData0.word0 & _filterData1.word1) || (_filterData1.word0 & _filterData0.word1))
		{
			_pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST;
			return PxFilterFlag::eDEFAULT;
		}

		return PxFilterFlag::eKILL;
	}
}


