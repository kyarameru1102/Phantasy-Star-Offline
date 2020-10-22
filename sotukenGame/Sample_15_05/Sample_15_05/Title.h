#pragma once
/// <summary>
/// タイトルシーン。
/// </summary>
class Title : public GameObject
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
};

