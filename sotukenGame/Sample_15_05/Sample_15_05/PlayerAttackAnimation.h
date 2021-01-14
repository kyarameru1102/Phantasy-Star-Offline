#pragma once
const enum AttackAnimTime {
	enAttackTime01_blad,
	enAttackTime02_blad,
	enAttackTime03_blad,
	enAttackTime04_blad,
	enAttackTime05_blad,
	enAttackTime06_blad,
	enAttackTime07_blad,
	enAttackTime08_blad,
	enAttackTime09_blad,
	enAttackTime01_sword,
	enAttackTime02_sword,
	enAttackTime03_sword,
	enAttackTime04_sword,
	enAttackTime05_sword,
	enAttackTime06_sword,
	enAttackTime07_sword,
	enAttackTime08_sword,
	enAttackTime09_sword,
	enAttackTimeNum
};
class Player;
class PlayerAnimation;
class PlayerAttackAnimation : public IGameObject
{
public:
	PlayerAttackAnimation();
	~PlayerAttackAnimation();
	/// <summary>
	/// 攻撃アニメーションの時間を設定。
	/// </summary>
	void SetAttackAnimationTime();
	/// <summary>
	/// 通常攻撃。
	/// </summary>
	void NormalAttack();
	/// <summary>
	/// ブレイド状態の特殊攻撃。
	/// </summary>
	void SpecialAttackStateBlad();
	/// <summary>
	/// ソード状態の特殊攻撃。
	/// </summary>
	void SpecialAttackStateSword();
	/// <summary>
	/// 特殊攻撃の終わり。
	/// </summary>
	void SpecialAttackEnd();
	void AttackFlag(int attackTime01_blad, int* attackAnimNum, int attackTime01_sword);
	/// 攻撃終了関数。
	/// </summary>
	void AttackEnd();
	/// <summary>
	/// 攻撃。
	/// </summary>
	void Attack();

	bool Start() override;

	void Update() override;

	/// <summary>
	/// 攻撃番号を返す。
	/// </summary>
	/// <returns></returns>
	const int GetAttackNum() const
	{
		return m_attackNum;
	}
private:
	Player* m_player = nullptr;
	PlayerAnimation* m_playerAnim = nullptr;
	int attackTimer = 0;
	int m_attackAnimNum = 0; //XボタンかYボタンの攻撃アニメーションの数。
	int m_attackAnimationTimeNum = 0; //攻撃アニメーションの時間を入れた配列の番号。
	int m_totalAttackAnimationTime = 0; //攻撃アニメーションの合計の時間。
	int m_continuousAttackTime = 0;  //連撃する際のアニメーションの合計の時間。
	int m_attackNum = 0; //攻撃番号。
	int m_attackAnimationTime[enAttackTimeNum];//攻撃アニメーションの時間を設定する配列。
	int m_switchAttackTime[enAttackTimeNum];//攻撃の切り替えの時間を設定する配列。
	bool m_specialAttackStartFlag = false;//特殊攻撃のスタートフラグ。
	float m_speed = 50.0f;
	int m_timer = 0;
	
};

