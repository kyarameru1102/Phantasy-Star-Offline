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
	enAnimationClipNum, //アニメーションクリップの数。
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

	AnimationClip animClip[enAnimationClipNum];//アニメーションクリップ。
};