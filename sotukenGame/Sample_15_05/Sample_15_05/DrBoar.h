#pragma once
/// <summary>
/// ドラゴンボアクラス
/// </summary>
class DrBoar : public IGameObject
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
	/// プレイヤーの座標を返す。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	enum EnAnimationClip {
		enIdle,
		enWalk,
		enRun,
		enScream,
		enAttack,
		enHornattack,
		enGethit,
		enDie,
		enAnimationClip_num
	};

	SkinModelRender* m_DrBoarSkinModel = nullptr;
	Vector3 m_position = Vector3::Zero;  //座標
	Vector3 m_scale = Vector3::One;      //拡大率
	Quaternion m_rotation = Quaternion::Identity; //回転
	int changeTimer = 0;       //アニメーション変更タイマー
	int m_animState = enIdle; //アニメーションの状態。
	AnimationClip m_animationClip[enAnimationClip_num];
};

