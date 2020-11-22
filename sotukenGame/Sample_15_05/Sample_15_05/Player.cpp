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
			if (m_weaponState == enSwordState) {
				m_changeAnimTime = 10.0f;
				m_animState = enJumpStart_sword;
			}
		}
	}
	if (m_charaCon.IsOnGround() != true) {
		//�W�����v���Ă���܂��́A�������Ă���B
		m_speedY -= FLUCTUATION_VALUE_Y;
		if (jumpStartTimer >= 40) {
			if (m_weaponState == enSwordState) {
				m_changeAnimTime = 10.0f;
				m_animState = enStayInTheAir_sword;
			}
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
		//����̏�Ԃɂ���ĕ���ύX�̃A�j���[�V���������߂�B
		if (m_weaponState == enBladState) {
			m_animState = enChange_blad;
		}
		else if (m_weaponState == enSwordState) {
			m_animState = enChange_sword;
		}
		//����ύX���͓����Ȃ��B
		m_moveSpeed = Vector3::Zero;
		//�^�C�}�[�����Z�B
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//����ύX�̃A�j���[�V�������I������B
			//m_weaponState������ύX�O�̏�ԂŁA�ύX��̏�Ԃɂ���B
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
				m_animState = enStay_sword;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
				m_animState = enStay_blad;
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
}
bool Player::Start()
{
	m_weapon[0] = NewGO<Weapon>(0, "weapon_01");
	m_weapon[1] = NewGO<Weapon>(0, "weapon_02");
	//�A�j���[�V���������[�h�B
	animClip[enStay_blad].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay_sword].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enChange_blad].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange_sword].Load("Assets/animData/player/sword/change_02.tka");
	animClip[enWalk_sword].Load("Assets/animData/player/sword/walk_02.tka");
	animClip[enRun_sword].Load("Assets/animData/player/sword/run_02.tka");

	animClip[enJumpStart_sword].Load("Assets/animData/player/sword/jumpStart_02.tka");
	animClip[enStayInTheAir_sword].Load("Assets/animData/player/sword/stayInTheAir_02.tka");
	animClip[enJumpEnd_sword].Load("Assets/animData/player/sword/jumpEnd_02.tka");

	animClip[enStay_blad].SetLoopFlag(true);
	animClip[enStay_sword].SetLoopFlag(true);
	animClip[enChange_blad].SetLoopFlag(true);
	animClip[enChange_sword].SetLoopFlag(true);
	animClip[enWalk_sword].SetLoopFlag(true);
	animClip[enRun_sword].SetLoopFlag(true);

	animClip[enJumpStart_sword].SetLoopFlag(true);
	animClip[enStayInTheAir_sword].SetLoopFlag(true);
	animClip[enJumpEnd_sword].SetLoopFlag(true);


	//���f���̏������B
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init("Assets/modelData/player/player.tkm", animClip, enAnimationClipNum);
	Quaternion qRot;
	qRot.SetRotationDegX(0.0f);
	m_playerSkinModel->SetRotation(qRot);
	m_position.y = 200.0f;
	m_playerSkinModel->SetPosition(m_position);
	m_charaCon.Init(50.0f, 100.0f, m_position);


	//����̍��W�A��]��K��������{�[���̔ԍ��������B
	m_weapon01Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r");
	m_weapon02Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l");

	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	SetWeaponTR();
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
			if (m_weaponState == enSwordState) {
				//�\�[�h��ԁB
				m_changeAnimTime = 10.0f;
				m_magnificationSpeed = 10.0f;
				m_animState = enRun_sword;
			}
		}
		else {
			if (m_weaponState == enSwordState) {
				m_changeAnimTime = 10.0f;
				m_magnificationSpeed = 5.0f;
				m_animState = enWalk_sword;
			}
		}
	}
	else if (m_weaponState == enSwordState){
		//�\�[�h��ԁB
		m_animState = enStay_sword;
	}
	//Y�����̈ړ��B
	YDirMove();

	//����ύX�B
	if (g_pad[0]->IsPress(enButtonX)) {
		//����ύX�̃t���O�𗧂Ă�B
		m_changeAnimFlag = true;
		m_changeAnimTime = 35;
	}
	WeaponChange();

	//�A�j���[�V�������Đ��B
	float aa = m_changeAnimTime / 60.0f;
	m_playerSkinModel->PlayAnimation(m_animState, aa);

	//�Ƃ肠�����v���C���[��Y���W��-500�ȉ��ɂȂ�����߂�悤�ɂ���B
	if (m_charaCon.GetPosition().y <= -500.0f) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
	}
	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);

	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);
}