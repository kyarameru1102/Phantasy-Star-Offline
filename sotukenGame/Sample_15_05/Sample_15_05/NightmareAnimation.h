#pragma once
const enum NightmareAnim {
	enIdle01,               //待機１
	enIdle02,               //待機２
	enWalk,                 //歩き
	enWalkBack,             //後ろ歩き
	enWalkLeft,             //左歩き
	enWalkRight,            //右歩き
	enRun,                  //走り
	enScream,               //咆哮
	enJump,                 //ジャンプ
	enBasicAttack,          //通常攻撃
	enClawAttack,            //爪攻撃
	enHornAttack,            //角攻撃
	enGetHit,                //被ダメ
	enDefend,                //防御
	enSleep,                 //睡眠
	enDie,                   //死亡
	enNightmareAnimClip_num  //アニメーションクリップの数
};

class NightmareAnimation : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	NightmareAnimation();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~NightmareAnimation();
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
private:
	AnimationClip animClip[enNightmareAnimClip_num];//アニメーションクリップ。

};



