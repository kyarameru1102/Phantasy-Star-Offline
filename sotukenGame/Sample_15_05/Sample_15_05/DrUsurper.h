#pragma once
#include "Physics/Character/CharacterController.h"
#include "EnBase.h"
#include "Physics/GhostObject.h"
class DrUsurper : public EnBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DrUsurper();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DrUsurper();
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

};

