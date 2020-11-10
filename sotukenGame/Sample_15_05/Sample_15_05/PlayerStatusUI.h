#pragma once
/// <summary>
/// �v���C���[�X�e�[�^�X��UI�N���X�B
/// </summary>
class PlayerStatusUI : public IGameObject
{
public:
	PlayerStatusUI();
	~PlayerStatusUI();

	/// <summary>
	/// �X�V�֐����Ă΂��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��B</returns>
	bool Start();

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Update();

private:

	const enum {
		en_playerUIHP,			//�v���C���[HP��UI�B
		en_playerUIPP,			//�v���C���[PP��UI�B
		en_playerUIHPBer,		//HPBer��UI�B
		en_playerUIPPBer,		//PPBer��UI�B
		en_playerUIStatus,		//�X�e�[�^�X��UI�B
		en_playerUINum			//�v���C���[UI�̐��B
	};

	SpriteRender* m_statusSprite = nullptr;		//�v���C���[�X�e�[�^�X�̃X�v���C�g�����_�[�B
	SpriteRender* m_hpSprite =  nullptr;		//�v���C���[HP�̃X�v���C�g�����_�[�B
	SpriteRender* m_ppSprite = nullptr;			//�v���C���[PP�̃X�v���C�g�����_�[�B
	SpriteRender* m_hpBerSprite = nullptr;		//HPBer�̃X�v���C�g�����_�[�B
	SpriteRender* m_ppBerSprite = nullptr;		//PPBer�̃X�v���C�g�����_�[�B

	Vector3 m_spritePosition[en_playerUINum] = { Vector3::Zero };	//�X�v���C�g�̍��W�B
	Vector3 m_spriteScale[en_playerUINum] = { Vector3::One };		//�X�v���C�g�̊g�嗦�B
	Vector2 m_spritePivot[en_playerUINum] = { { 0.5f, 0.5f } };		//�X�v���C�g�̃s�{�b�g�B
};

