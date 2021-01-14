#pragma once
const enum BoarAnim {
	enIdle,                    //待機
	enWalk,                    //歩き
	enRun,                     //走り
	enScream,                  //咆哮
	enAttack,                  //攻撃
	enHornattack,              //角攻撃
	enGethit,                  //被ダメ
	enDie,                     //死亡
	enBoarAnimClip_num        //アニメーションクリップの数
};

class BoarAnimation : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	BoarAnimation();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~BoarAnimation();
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
	AnimationClip animClip[enBoarAnimClip_num];//アニメーションクリップ。
};



