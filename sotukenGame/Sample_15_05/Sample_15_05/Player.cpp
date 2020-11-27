#include "stdafx.h"
#include "Player.h"

const float MAX_SPEED_Y = 50.0f; //Y�����̃X�s�[�h�̍ő�l�B
const float FLAME_NUM = 40.0f;  //�t���[�����B
const float FLUCTUATION_VALUE_Y = MAX_SPEED_Y / FLAME_NUM; //Y�����̃X�s�[�h�̕ϓ��l�B
                                                           //Y�����̃X�s�[�h�̍ő�l���t���[�����Ŋ����āA
                                                           //1�t���[��������̕ϓ��l�����߂�B
Player::Player()
{
}
Player::~Player()
{
	DeleteGO(m_playerSkinModel);
	if (m_weapon[0] != nullptr) {
		DeleteGO(m_weapon[0]);
	}
	if (m_weapon[1] != nullptr) {
		DeleteGO(m_weapon[1]);
	}
	}
void Player::YDirMove()
{
	if (m_charaCon.IsOnGround() != false) {
		//�n�ʂ̏�ɂ���B
		if (g_pad[0]->IsPress(enButtonA)) {
			//A�{�^�����������B
			//�W�����v�t���O�𗧂Ă�B
			m_jumpFlag = true;
			//Y�X�s�[�h���ő�l�ɂ���B
			m_speedY = MAX_SPEED_Y;
			jumpStartTimer = 0;
		}
		else {
			//�t���O�������B
			m_jumpFlag = false;
			//Y�X�s�[�h��0�ɂ���B
			m_speedY = 0.0f;
		}
	}
	if (m_jumpFlag != false) {
		//�W�����v�������A�A�j���[�V�����𗬂��B
		jumpStartTimer++;
		if (jumpStartTimer <= 40) {
			m_complementaryTime = 10.0f;
				m_animState = enJumpStart_blad;
		}
	}
	if (m_charaCon.IsOnGround() != true) {
		//�W�����v���Ă���܂��́A�������Ă���B
		m_speedY -= FLUCTUATION_VALUE_Y;
		if (jumpStartTimer >= 40) {
			m_complementaryTime = 10.0f;
				m_animState = enStayInTheAir_blad;
		}
	}

	if (m_speedY <= -MAX_SPEED_Y) {
		//Y�X�s�[�h�̍Œ�l���Œ肷��B
		m_speedY = -MAX_SPEED_Y;
	}
	//���[�u�X�s�[�h��Y�X�s�[�h�����Z�B
	m_moveSpeed.y += m_speedY;

}
void Player::WeaponChange()
{
	if (m_changeAnimFlag != false) {
		m_complementaryTime = 10.0f;
		m_animState = enChange_blad;
		//����ύX���͓����Ȃ��B
		m_moveSpeed = Vector3::Zero;
		//�^�C�}�[�����Z�B
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//����ύX�̃A�j���[�V�������I������B
			//m_weaponState������ύX�O�̏�ԂŁA�ύX��̏�Ԃɂ���B
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
			}
			//�t���O��false�ɂ���B
			m_changeAnimFlag = false;
			//�^�C�}�[�����Z�b�g�B
			m_changeAnimTimer = 0;
		}
	}
}
void Player::SetWeaponTR()
{
	//�{�[�����畐��̍��W�A��]�A�X�P�[����ݒ�B
	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon01Num)->CalcWorldTRS(
		m_weaponPos,
		m_weaponRot,
		m_weaponScale
	);
	Quaternion weaponRot = Quaternion::Identity;
	weaponRot.SetRotationDegX(90.0f);
	weaponRot.Multiply(m_weaponRot);
	//���W�Ƀ��[�u�X�s�[�h�����Z�B
	m_weaponPos += m_moveSpeed;
	m_weapon[0]->SetPosition(m_weaponPos);
	m_weapon[0]->SetRtation(weaponRot);

	//�{�[�����畐��̍��W�A��]�A�X�P�[����ݒ�B
	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon02Num)->CalcWorldTRS(
		m_weaponPos,
		m_weaponRot,
		m_weaponScale
	);
	weaponRot = Quaternion::Identity;
	weaponRot.SetRotationDegX(90.0f);
	weaponRot.Multiply(m_weaponRot);
	//���W�Ƀ��[�u�X�s�[�h�����Z�B
	m_weaponPos += m_moveSpeed;
	m_weapon[1]->SetPosition(m_weaponPos);
	m_weapon[1]->SetRtation(weaponRot);

	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon03Num)->CalcWorldTRS(
		m_rootPos,
		m_rot,
		m_rootScale
	);
}
void Player::SetDirAndSpeed()
{
	//�J�������l�������v���C���[�̈ړ��������v�Z����B
	Vector3 cameraDir = m_gameCam->GetTarget() - m_gameCam->GetPosition();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	Vector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		Vector3::AxisY
	);
	//�v���C���[�̃��[�u�X�s�[�h���v�Z�B
	m_moveSpeed = cameraDirX * g_pad[0]->GetLStickXF() * -m_magnificationSpeed +
		cameraDir * g_pad[0]->GetLStickYF() * m_magnificationSpeed;

	if (fabs(m_moveSpeed.x) > 0.0f || fabs(m_moveSpeed.z) > 0.0f) {
		//�ړ����Ă���B
		if (g_pad[0]->IsPress(enButtonB)) {
			m_magnificationSpeed = 10.0f;
			m_animState = enRun_blad;
		}
		else {
			m_magnificationSpeed = 5.0f;
			m_animState = enWalk_blad;
		}
		m_complementaryTime = 10.0f;
	}
	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);
}
bool Player::Start()
{
	//����̃C���X�^���X�쐬�B
	m_weapon[0] = NewGO<Weapon>(0, "weapon_01");
	m_weapon[1] = NewGO<Weapon>(0, "weapon_02");
	//�v���C���[�̃A�j���[�V�����̃C���X�^���X�쐬�B
	m_playerAnim = NewGO<PlayerAnimation>(0, "playerAnim");
	//���f���̏������B
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init(
		"Assets/modelData/player/player.tkm",
		m_playerAnim->GetAnimationClip(),
		enAnimationClipNum,
		"Assets/shader/model.fx",
		SkinModelRender::YUp
		);
	//�L�����R���������B
	m_charaCon.Init(50.0f, 100.0f, m_position);
	//����̍��W�A��]��K��������{�[���̔ԍ��������B
	m_weapon01Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r");
	m_weapon02Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l");

	m_weapon03Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"root");
	//GameCamera�̃C���X�^���X�������B
	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	//�A�j���[�V������ҋ@��Ԃɐݒ�B
	m_animState = enStay_blad;

	//����̍��W�Ɖ�]��ݒ�B
	SetWeaponTR();

	//�����ƈړ��X�s�[�h��ݒ�B
	SetDirAndSpeed();

	//Y�����̈ړ��B
	YDirMove();

	//����ύX�B
	if (g_pad[0]->IsPress(enButtonLB1)) {
		//����ύX�̃t���O�𗧂Ă�B
		m_changeAnimFlag = true;
	}
	WeaponChange();
	if (m_attackFlag != true && g_pad[0]->IsPress(enButtonX)) {
		m_attackFlag = true;
	}
	if (m_attackFlag != false) {
		m_moveSpeed = Vector3::Zero;
		attackTimer++;
		m_animState = enAttack_blad;
		m_complementaryTime = 10.0f;
		int time = 120;
		if (m_weaponState == enSwordState) {
			time = 90;
		}
		if (attackTimer > time) {
			m_attackFlag = false;
			attackTimer = 0;
		}
	}
	
	if (m_weaponState == enSwordState) {
		//�\�[�h��ԂȂ�1�����ă\�[�h��Ԃ̃A�j���[�V�����𗬂��B
		m_animState++;
	}
	//�A�j���[�V�������Đ��B
		float aa = m_complementaryTime / 60.0f;
		m_playerSkinModel->PlayAnimation(m_animState, aa);

	//�Ƃ肠�����v���C���[��Y���W��-500�ȉ��ɂȂ�����߂�悤�ɂ���B
	if (m_charaCon.GetPosition().y <= -500.0f) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
	}

	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);
}