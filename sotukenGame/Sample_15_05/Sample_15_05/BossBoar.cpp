#include "stdafx.h"
#include "BossBoar.h"
#include "Player.h"

BossBoar::BossBoar()
{
}

BossBoar::~BossBoar()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_enemyAnim);
}

bool BossBoar::Start()
{
	//プレイヤーのアニメーションのインスタンス作成。
	m_enemyAnim = NewGO<EnemyAnimation>(0, "enemyAnim");
	
	//モデルの初期化
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
	
	//キャラコン初期化。
	m_charaCon.Init(400.0f, 200.0f, m_position);
	Vector3 ghostPos = m_position;
	m_ghostObj.CreateBox(ghostPos, m_rotation, Vector3(50.0f, 50.0f, 50.0f));

	m_player = FindGO<Player>("player");
	m_hp = 500;

	//ボスは体がでかいのでコライダー二つ目用意。
	//当たり判定用の初期化。
	//m_charaConFace.Init(500.0f, 200.0f, m_position);
	return true;
}

void BossBoar::Update()
{
	//毎フレーム距離はかる。
	m_toPlayer = m_player->GetPosition() - m_position;

	//プレイヤーに近づく。
	if (m_status != GetDamage_state) {
		if (m_status != Attack_state && m_status != Die_state) {
			Move();
			Turn();
		}

		//距離が近づくと。
		Attack();
	}
	//体力がゼロになると
	Die();

	switch (m_status)
	{
	case Idle_state:
		m_animState = enIdle;
		break;
	case Walk_state:
		m_animState = enWalk;
		break;
	case Attack_state:
		m_animState = enAttack;
		m_count++;
		m_isAttack = true;
		if (!m_skinModelRender->GetisAnimationPlaing()) {
			m_status = Idle_state;
			m_isAttack = false;
			m_ATKoff = false;
			m_count = 0;
			m_animState = enIdle;
			m_skinModelRender->PlayAnimation(m_animState, 0.0f);
		}
		break;
	case GetDamage_state:
		m_animState = enGethit;
		m_isAttack = false;
		m_ATKoff = false;
		m_count = 0;
		if (!m_skinModelRender->GetisAnimationPlaing()) {
			m_status = Idle_state;
			m_animState = enIdle;
			m_skinModelRender->PlayAnimation(m_animState, 0.0f);
		}
		break;
	case Die_state:
		m_animState = enDie;
		break;
	default:
		break;
	}

	m_ghostObj.SetPosition(m_ghostPos);
	m_ghostObj.SetRotation(m_rotation);
	m_skinModelRender->SetScale({ 150.0, 150.0, 150.0 });
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->PlayAnimation(m_animState, 1.0f / 60.0f);
	//デバッグ用。
	printf_s("AnimationState_%d\n", m_animState);
	printf_s("EnemyHP_%d\n", m_hp);
}

void BossBoar::Move()
{
	m_status = Walk_state;
	Vector3 playerLen = m_toPlayer;
	playerLen.Normalize();
	m_movespeed = playerLen * 1.2f;
	m_movespeed.y = m_speedY;
	if (m_movespeed.Length() >= 0.0f) {
		m_dir = m_movespeed;
		m_dir.Normalize();
		m_dir *= 500.0f;
	}
	m_ghostPos = m_position + m_dir;
	//facePos = m_position + dir;
	//m_charaConFace.Execute(1.0f,m_movespeed);
	m_position = m_charaCon.Execute(1.0f, m_movespeed);
}

void BossBoar::Turn()
{
	Vector3 playerLen = m_player->GetPosition() - m_position;
	float angle = atan2(playerLen.x, playerLen.z);
	m_rotation.SetRotation(Vector3::AxisY, angle);
}

void BossBoar::Attack()
{
	if (m_toPlayer.Length() <= 500.0f)
	{
		m_status = Attack_state;
		CharacterController& charaCon = *m_player->GetCharacterController();
		g_physics.ContactTestCharaCon(charaCon, [&](const btCollisionObject& collisionObject) {
			if (m_ghostObj.IsSelf(collisionObject) == true) {
				if (m_isAttack && !m_ATKoff) {
					if (m_count >= 40 && m_count <= 60) {
						m_player->ReceiveDamage(10);
						m_ATKoff = true;
						printf_s("Enemy_KOUGEKI\n");
					}
				}
			}
		});
	}
}

void BossBoar::Die()
{
	if (m_hp <= 0)
	{
		m_status = Die_state;
		m_charaCon.RemoveRigidBoby();
		if (!m_skinModelRender->GetisAnimationPlaing()) {
			m_player->GetExperiencePoint(10);
			SetIsDead();
		}
	}
}
