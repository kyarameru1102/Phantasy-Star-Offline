#pragma once
#include "GameObject.h"


class SpriteRender : public IGameObject
{
public:
	/// <summary>
	/// 初期化関数。
	/// </summary>
	/// <param name="dds">ddsファイルのファイルパス</param>
	/// <param name="height">高さ</param>
	/// <param name="width">幅</param>
	/// <param name="fx">使用するシェーダーのファイルパス</param>
	/// 第4引数はシェーダーを変更しない場合書かなくてよい。
	void Init(const char* dds,float height, float width, const char* fx = "Assets/shader/sprite.fx");
	/// <summary>
	/// spriteを表示する座標を設定する関数。
	/// </summary>
	/// <param name="position">Vector3 position</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得する関数。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
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
	/// ピボットを設定する関数。
	/// </summary>
	/// <param name="pivot">Vector2 pivot</param>
	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
	}
	/// <summary>
	/// 乗算カラーを設定。
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const Vector4& mulColor)
	{
		m_sprite.SetMulColor(mulColor);
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	Vector4 GetMulColor()
	{
		return m_sprite.GetMulColor();
	}
	/// <summary>
/// a値の設定
/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_sprite.SetAlpha(alpha);
	}
	/// <summary>
	/// a値を取得
	/// </summary>
	float GetAlpha() const
	{
		return m_sprite.GetAlpha();
	}

	/// <summary>
	/// α値を変位させる
	/// </summary>
	/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(const float& delta)
	{
		m_sprite.DeltaAlpha(delta);
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
	void Render2D() override;
private:
	SpriteInitData		m_spriteInitData;
	Sprite				m_sprite;
	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion::Identity;
	Vector3				m_scale = Vector3::One;
	Vector2				m_pivot = { 0.5f, 0.5f };
};

