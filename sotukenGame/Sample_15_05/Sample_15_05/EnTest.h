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
		enWalk,
		enRun,
		enScream,
		enAttack,
		enHornattack,
		enGethit,
		enDie,
		enAnimationClip_num
	};
	int changeTimer = 0;
	int m_animState = enIdle; //�A�j���[�V�����̏�ԁB
	AnimationClip m_animationClip[enAnimationClip_num];
};

