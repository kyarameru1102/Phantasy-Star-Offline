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
	void Update() override;
private:
	SkinModelRender* m_EnTestSkinModel = nullptr;
	Quaternion m_rotation = Quaternion::Identity;
	enum EnAnimationClip {
		enIdle,
		enAnimationClip_num
	};
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	AnimationClip m_animationClip[enAnimationClip_num];
};

