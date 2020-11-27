#pragma once
/// <summary>
/// 敵の群れを生成するクラス
/// </summary>
class EnArmyGenerator : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnArmyGenerator();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnArmyGenerator();
	void Update()override;
};

