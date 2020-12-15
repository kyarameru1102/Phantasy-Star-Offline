#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnemyAnimation.h"
#include "EnBase.h"

/// <summary>
/// ドラゴンボアクラス
/// </summary>
class DrBoar : public EnBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DrBoar();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DrBoar();
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
	
private:
	/// <summary>
	/// エネミーのステート。
	/// </summary>
	enum {
		Idle_state,
		Move_state,
		Attack_state,
		Die_state
	};
	int					m_status = Idle_state;			//状態。
	int					changeTimer = 0;				//アニメーション変更タイマー。
	float				m_speedY = 0.0f;				//Y方向のスピード。
	int					m_animState = enIdle;			//アニメーションの状態。
	int					m_appearcolor = 0;				//配色No
	EnemyAnimation*		m_enemyAnim = nullptr;			//アニメーションのロード。
	std::vector<int>	boarcolor = { 1,2,3,4 };		//配色決定。
	bool				isAttack = false;				//攻撃しているか。
};

