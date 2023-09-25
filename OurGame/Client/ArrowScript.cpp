#include "pch.h"
#include "ArrowScript.h"
#include "GameObject.h"
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
#include "Grandma.h"

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
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "AttackState.h"

/* Event */
#include "SceneChangeEvent.h"
ArrowScript::ArrowScript()
{
}

void ArrowScript::Initialize()
{
}

void ArrowScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer(); // �÷��̾�*
	Animator* pAni = pPlayer->GetAnimator(); // �÷��̾� �ִϸ��̼�
	Transform* pPlyer_Tr = pPlayer->GetTransform(); //�÷��̾� Ʈ������
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // �÷��̾� 8���� ���� �������°�
	mPlayerStateNum; //�÷��̾� ����FSM

	Transform* pTr = GetTransform(); // ȭ�� Ʈ������
	GameObject* pObj = GetGameObject(); // ȭ�� ������Ʈ


}

void ArrowScript::SetPlayerState(PlayerState _eStateNum)
{
}

Component* ArrowScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new ArrowScript);
}
