#pragma once

#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
#include "EnBase.h"
#include "Physics/GhostObject.h"
#include "Physics/CapsuleCollider.h"

class BossBoar : public EnBase
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	BossBoar();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~BossBoar();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数。
	/// </summary>
	/// <returns></returns>
	void Update();

	/// <summary>
	/// プレイヤーに向かっていく関数。
	/// </summary>
	void Move();
	/// <summary>
	/// プレイヤーの方向に体を向ける関数。
	/// </summary>
	void Turn();
	/// <summary>
	/// 攻撃関数。
	/// </summary>
	void Attack();
	/// <summary>
	/// 死。
	/// </summary>
	void Die();
	void ReceiveDamage(int damage) override
	{
		m_hp -= damage;
		m_status = GetDamage_state;
	}
private:
	/// <summary>
	/// エネミーのステート。
	/// </summary>
	enum {
		Idle_state,
		Walk_state,
		Run_state,
		Attack_state,
		GetDamage_state,
		Die_state
	};
	int					m_status = Idle_state;			//状態。
	int					changeTimer = 0;				//アニメーション変更タイマー。
	float				m_speedY = 0.0f;				//Y方向のスピード。
	int					m_animState = enIdle;			//アニメーションの状態。
	int					m_appearcolor = 0;				//配色No
	EnemyAnimation*		m_enemyAnim = nullptr;			//アニメーションのロード。
	std::vector<int>	boarcolor = { 1,2,3,4 };		//配色決定。
	bool				m_isAttack = false;				//攻撃しているか。
	bool				m_ATKoff = false;				//一回の攻撃でダメージを一回だけ入れるためのフラグ。
	int					m_count = 0;					//攻撃が入るまでのカウント。
	GhostObject			m_ghostObj;						//ゴースト。
};

