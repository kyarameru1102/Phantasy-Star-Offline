#pragma once
/// <summary>
/// タイトルシーン。
/// </summary>
class Title : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Title();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Title();
	/// <summary>
	/// 開始関数。
	/// </summary>
	bool Start()override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update()override;
private:
	SkinModelRender* m_ladySkinModelRender = nullptr;
	SkinModelRender* m_bgSkinModelRender = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	Vector3	m_spritePosition = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	float addRot = 0.0f;
	bool m_ok = false;
};

