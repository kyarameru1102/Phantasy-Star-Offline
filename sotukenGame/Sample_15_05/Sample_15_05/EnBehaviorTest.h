#pragma once
//敵挙動確認クラス
class EnBehaviorTest : public IGameObject
{
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnBehaviorTest();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnBehaviorTest();
	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
};

