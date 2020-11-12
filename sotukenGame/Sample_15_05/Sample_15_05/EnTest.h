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
	int a=0;
private:
	SkinModelRender* m_EnTestSkinModel = nullptr;
};

