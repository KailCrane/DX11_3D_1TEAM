#include "pch.h"
#include "Player.h"
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
#include "SwordHeavyEffect.h"

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
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "SwordScript.h"

/* Event */
#include "SceneChangeEvent.h"
 /*State ����*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitState.h"
#include "FallDownState.h"
#include "DeadState.h"
#include "ClimingDownState.h"
#include "ClimingEndState.h"
#include "ClimingUpState.h"

Player* Player::spPlayer;

Player::Player()
	: GameObject(LayerType::Player)
	, mHP(4) // ����
	, mCost(4) // ����
	, mSpeed(5.f) // �̵��ӵ�
	, mAttack(1.f) // ������
	, mAttack_Speed(0.04f) // ����
	, mDash_Speed(25.f) // ȸ�ǽ� �ִ� ���� ��
	, meDirectionEvasion(DirectionEvasion::NONE) // �÷��̾� 8���� enum ���� ǥ��
	
{
	AssertEx(spPlayer == nullptr, L"�̹� ���� �÷��̾� ������");
	spPlayer = this; //�������� ����

	mState[int(PlayerState::PauseState)] = new PauseState;
	mState[int(PlayerState::IdleState)] = new IdleState;
	mState[int(PlayerState::MoveState)] = new MoveState;
	mState[int(PlayerState::AttackState)] = new AttackState;
	mState[int(PlayerState::MagicAttackState)] = new MagicAttackState;
	mState[int(PlayerState::EvasionState)] = new EvasionState;
	mState[int(PlayerState::FallState)] = new FallState;
	mState[int(PlayerState::HitState)] = new HitState;
	mState[int(PlayerState::FallDownState)] = new FallDownState;
	mState[int(PlayerState::DeadState)] = new DeadState;
	mState[int(PlayerState::ClimingDownState)] = new ClimingDownState;
	mState[int(PlayerState::ClimingEndState)] = new ClimingEndState;
	mState[int(PlayerState::ClimingUpState)] = new ClimingUpState;

	// Sword_Heavy
	{
		mpSlashEffect = Factory::CreateObject<SwordHeavyEffect>(Vec3(0.f, 8.f, 0.f), L"PlayerSlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbx");
		mpSlashEffect->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
		mpSlashEffect->AddComponent(new PlayerSlashScript);
		auto pFollowScript = mpSlashEffect->AddComponent(new OwnerFollowScript(this));
		pFollowScript->SetOffset(Vec3(0.f, -0.f, -0.f));

		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::Clamp);

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_1.png");
		shared_ptr<Texture> pTexture2 = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash2", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_2.png");
		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetTexture(1, pTexture2);
		mpSlashEffect->GetRigidBody()->RemoveGravity();
		
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(mpSlashEffect);
	}

	//�� ������Ʈ
	//��  -> Sc 
	// Sc ( �˿�����Ʈ , �÷��̾� ������Ʈ 
	// ���� �����ͼ� ����

	//���� ������Ʈ
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(1.f, 0.2f, 0.2f);
		
		pGreatSword = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, -5.f, 0.f), physicsInfo, L"Forward_CullNone", L"..\\Resources\\FBX\\Weapon\\Sword.fbx",false, LayerType::Item);
		pGreatSword->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		pGreatSword->GetTransform()->SetRotation(Vec3(330.f, 100.f, 50.f));

		auto pFollowSc = pGreatSword->AddComponent(new OwnerFollowScript(this));
		
		
		SwordScript* pSwordSc = pGreatSword->AddComponent(new SwordScript);
		//gpEngine->GetTool()->UseGizmo();
		//gpEngine->GetTool()->SetGameObject(pGreatSword);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pGreatSword);
		//SetMeshTarget(pGreatSword);
	}
}

Player::~Player()
{
	for (size_t i = 0; i < PLAYER_STATE_COUNT; i++)
	{
		SAFE_DELETE(mState[i]);
	}
	
}

void Player::Initialize()
{
	GameObject::Initialize();
	
	StateChange(PlayerState::IdleState);

	//mActiveState->Initialize();
	
#pragma region "�÷��̾� �ִϸ��̼� �̸� ����"
/*�ִϸ��̼� �̸� ����*/
	//���̵�
	GetAnimator()->RenameAnimation(42, L"_Player_Idle01"); //�̸�����
	GetAnimator()->SetLoop(42, true); //����
	GetAnimator()->SetHasExitFlag(42, true); // ���� �ִϸ��̼� �ٳ����� ���� f ? t
	GetAnimator()->RenameAnimation(43, L"_Player_Idle02");
	GetAnimator()->SetLoop(43, true); 
	GetAnimator()->SetHasExitFlag(43, true); 

	//�̵�
	GetAnimator()->RenameAnimation(67, L"_Player_Move");
	GetAnimator()->SetLoop(67, true);
	GetAnimator()->SetHasExitFlag(67, true);

	//ȸ��
	GetAnimator()->RenameAnimation(63, L"_Player_Evasion");
	GetAnimator()->SetLoop(63, true);
	GetAnimator()->SetHasExitFlag(63, true);
	
	//����
	GetAnimator()->RenameAnimation(69, L"_Player_Attack01");
	GetAnimator()->SetLoop(69, true);
	GetAnimator()->SetHasExitFlag(69, true);
	GetAnimator()->RenameAnimation(70, L"_Player_Attack02");
	GetAnimator()->SetLoop(70, true);
	GetAnimator()->SetHasExitFlag(70, true);

	//����
	GetAnimator()->RenameAnimation(7, L"_Player_Fallstart");
	GetAnimator()->SetLoop(7, true);
	GetAnimator()->SetHasExitFlag(7, true);
	GetAnimator()->RenameAnimation(8, L"_Player_Fallend");
	GetAnimator()->SetLoop(8, true);
	GetAnimator()->SetHasExitFlag(8, true);

	//��ٸ�
	GetAnimator()->RenameAnimation(20, L"_Player_ClimingUp");
	GetAnimator()->SetLoop(20, true);
	GetAnimator()->SetHasExitFlag(20, true);
	GetAnimator()->RenameAnimation(21, L"_Player_ClimingDown");
	GetAnimator()->SetLoop(21, true);
	GetAnimator()->SetHasExitFlag(21, true);
	GetAnimator()->RenameAnimation(22, L"_Player_ClimingEnd");
	GetAnimator()->SetLoop(22, true);
	GetAnimator()->SetHasExitFlag(22, true);





#pragma endregion















	//GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	/* �ִϸ��̼��� �̸��� FBX�� ����Ǿ� �ִ� ���� �״�� �������Ƿ� �ش� FBX�� ����ϴ� Ŭ������ �����ڿ� ���� Ư�� �κп���
			 ����ϱ� ���� �̸����� �ϰ������� �ٲ��� �ʿ䰡 ����
	pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	 �ݺ� ���θ� �����ϴ� �Լ� (Finished �÷��׸� ����� �� ����)
	pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

	 �ε��� ��ȣ�ε� ��� ����
	pPotHead->GetAnimator()->SetLoop(9, true);

	 HasExit�� ���� �ִϸ��̼� �����߿� �ٸ� �ִϸ��̼��� ����Ǿ��� �� �ٷ� �ѱ���� ���θ� ���� (�⺻������ true)
	 �� ���� false�� �ִϸ��̼� �÷��� ���� �ٸ� �ִϸ��̼� Play�� ����Ǿ��� �� ���� �ִϸ��̼��� �� ������ �����
	pPotHead->GetAnimator()->SetHasExitFlag(9, false);*/

	
}

void Player::Update()
{
	GameObject::Update();
	
	mActiveState->Update();
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();
	
	
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
	

}

void Player::Render()
{
	GameObject::Render();


}

void Player::Destroy()
{
	GameObject::Destroy();
	

}

void Player::OnTriggerEnter(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}

	if (LayerType::Monster == pOtherCollider->GetGameObject()->GetLayerType())
	{
		
	}
}

void Player::OnTriggerStay(Collider* pOtherCollider)
{
}

void Player::OnTriggerExit(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}

void Player::StateChange(PlayerState _eState)
{
	if (mActiveState != nullptr) {
		mActiveState->Exit();
	}

	mActiveState = mState[int(_eState)];
	mActiveState->Enter();
}

void Player::SetDirectionChange(DirectionEvasion _eState)
{
	meDirectionEvasion = _eState;
}

Player* Player::GetPlayer()
{
	AssertEx(spPlayer != nullptr, L"�÷��̾ Nullptr �̴� _ GetPlayer()~");
	return spPlayer; 
}
