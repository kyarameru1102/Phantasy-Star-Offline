#pragma once
#include "GameObject.h"

/// <summary>
/// スキンモデルレンダー。
/// </summary>
/// モデルを表示しやすくするクラス。
/// GameObjectを継承しているからNewGOでインスタンスを作成する必要があるよおおおお。
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
	/// 初期化関数。
	/// </summary>
	/// <param name="tkm">tkmファイル</param>
	/// <param name="fx">使用するシェーダー</param>
	/// シェーダーを差し替えたい場合のみ第二引数を変更してください。
	/// シェーダーを変える気がないのであれば第二引数はいじらなくていい。
	void Init(const char *tkm,const char *fx = "Assets/shader/model.fx");
	/// <summary>
	/// モデルを表示する座標を設定する関数。
	/// </summary>
	/// <param name="position">Vector3 position</param>
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
	ModelInitData	m_modelInitData;						//初期化用データ。
	Model			m_model;								//モデル。
	Vector3			m_position = Vector3::Zero;				//座標。
	Quaternion		m_rotation = Quaternion::Identity;		//回転。
	Vector3			m_scale = Vector3::One;					//拡大率。
	bool			m_renderOn = true;						//描画されるかどうか。
	bool            m_renderOK = false;						//Updateの後にレンダーが呼ばれるようにするフラグ。
};

