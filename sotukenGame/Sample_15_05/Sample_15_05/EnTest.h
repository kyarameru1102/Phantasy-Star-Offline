#pragma once
/// <summary>
/// 敵テストクラス
/// </summary>
class EnTest : public IGameObject
{
public:
	EnTest();
	~EnTest();
	bool Start() override;

private:
	SkinModelRender* m_EnTestSkinModel = nullptr;
};

