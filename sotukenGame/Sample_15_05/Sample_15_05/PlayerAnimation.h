#pragma once
const enum PlayerAnim {
	enStay_blad,            //ブレイド状態。
	enStay_sword,            //ソード状態。
	enWalk_blad,           //ブレイド状態で歩く。
	enWalk_sword,           //ソード状態で歩く。
	enRun_blad,            //ブレイド状態で走る。
	enRun_sword,            //ソード状態で走る。
	enJumpStart_blad,       //ブレイド状態でジャンプする。
	enJumpStart_sword,      //ソード状態でジャンプする。
	enStayInTheAir_blad,   //ブレイド状態で滞空。
	enStayInTheAir_sword,  //ソード状態で滞空。
	enChange_blad,          //ブレイドからソードに変更。
	enChange_sword,         //ソードからブレイドに変更。
	enAttack01_blad,         //ブレイド状態の攻撃1
	enAttack01_sword,        //ソード状態の攻撃1
	enAttack02_blad,         //ブレイド状態の攻撃2
	enAttack02_sword,         //ソード状態の攻撃2
	enAttack03_blad,         //ブレイド状態の攻撃3
	enAttack03_sword,         //ソード状態の攻撃3
	enAttack04_blad,         //ブレイド状態の攻撃4
	enAttack04_sword,         //ソード状態の攻撃4
	enAttack05_blad,         //ブレイド状態の攻撃5
	enAttack05_sword,         //ソード状態の攻撃5
	enAnimationClipNum, //アニメーションクリップの数。
};
const enum AttackAnimTime {
	enAttackTime01_blad,
	enAttackTime02_blad,
	enAttackTime03_blad,
	enAttackTime04_blad,
	enAttackTime05_blad,
	enAttackTime01_sword,
	enAttackTime02_sword,
	enAttackTime03_sword,
	enAttackTime04_sword,
	enAttackTime05_sword,
	enAttackTimeNum
};
class PlayerAnimation : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	PlayerAnimation();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~PlayerAnimation();
	/// <summary>
	/// 攻撃アニメーションの時間を設定。
	/// </summary>
	void SetAttackAnimationTime();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// アニメーションクリップを返す。
	/// </summary>
	/// <returns></returns>
	AnimationClip* GetAnimationClip()
	{
		return animClip;
	}
	int* GetAttackAnimationTime()
	{
		return m_attackAnimationTime;
	}
private:
	int m_attackAnimationTime[enAttackTimeNum];//攻撃アニメーションの時間を設定する配列。
	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
};