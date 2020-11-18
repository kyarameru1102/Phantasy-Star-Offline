#pragma once
/// <summary>
/// 敵挙動確認クラス
/// </summary>
#include "EnTest.h"

class EnBehaviorTest : public IGameObject
{
public:
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
	EnTest* m_entest = nullptr;
};

