#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "AnimationClip.h"

/// <summary>
/// スキンモデルレンダー。
/// </summary>
/// モデルを表示しやすくするクラス。
/// GameObjectを継承しているからNewGOでインスタンスを作成する必要があるよおおおお。
//class Animation;
//class AnimationClip;
class SkinModelRender : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	SkinModelRender();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~SkinModelRender();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="filePath">モデルのファイルパス(tkm)</param>
	/// <param name="animationClips">アニメーションクリップ</param>
	/// <param name="numAnimationClips">アニメーションクリップの数</param>
	void Init(const char* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		const char* fx = "Assets/shader/model.fx"
	);
	//アニメーションの初期化
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 向いている方向を設定する関数。
	/// </summary>
	/// <param name="rotation">Quaternion rotation</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 大きさを設定する関数。
	/// </summary>
	/// <param name="scale">Vector3 scale</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// モデルをレンダリングするかどうかの関数。
	/// </summary>
	/// <param name="on">true レンダリングする。
	/// false レンダリングしない。</param>
	/// 要するにこの関数の引数にfalseを入れるとSkinModelRenderのインスタンスを。
	/// デリートすることなくモデルを消すことができる。
	/// 必要に応じて使ってもろて。
	void SetRenderOn(bool on)
	{
		m_renderOn = on;
	}
	
	void PlayAnimation(int animNo, float interpolateTime)
	{
		m_animation.Play(animNo, interpolateTime);
	}
private:
	/// <summary>
	/// 開始関数。
	/// </summary>
	/// <returns>true</returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画関数。
	/// </summary>
	void Render() override;
private:
	Animation m_animation;								//アニメーション
	AnimationClip* m_animationClip;						//アニメーションクリップ
	int m_numAnimationClips = 0;						//アニメーションクリップの数
	ModelInitData										m_modelInitData;						//初期化用データ。
	Model												m_model;								//モデル。
	Vector3												m_position = Vector3::Zero;				//座標。
	Quaternion											m_rotation = Quaternion::Identity;		//回転。
	Vector3												m_scale = Vector3::One;					//拡大率。
	bool												m_renderOn = true;						//描画されるかどうか。
	bool												m_renderOK = false;						//Updateの後にレンダーが呼ばれるようにするフラグ。
	Skeleton											m_skeleton;
	const char* m_filePath = nullptr;
	bool m_isInitAnimation = false;						//アニメーション初期化した？
};

