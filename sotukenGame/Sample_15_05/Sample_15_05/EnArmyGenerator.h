#pragma once
#include "Random.h"
/// <summary>
/// 敵の群れを生成するクラス
/// </summary>
class Random;
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
	Random m_random;
};

