#pragma once
/// <summary>
/// �G�e�X�g�N���X
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

