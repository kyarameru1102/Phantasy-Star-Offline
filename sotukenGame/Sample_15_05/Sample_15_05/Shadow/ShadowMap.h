#pragma once
#include "RenderTarget.h"
#include "RenderMode.h"

class Model;
class ShadowMap
{
public:
	ShadowMap();
	/// <summary>
	/// ���C�g�r���[�s����擾
	/// </summary>
	/// <returns></returns>
	Matrix GetLightViewMatrix()
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ���C�g�v���W�F�N�V�����s����擾
	/// </summary>
	/// <returns></returns>
	Matrix GetLightProjMatrix()
	{
		return m_lightProjMatrix;
	}
	/// <summary>
	/// ���C�g�r���[�s��⃉�C�g�v���W�F�N�V�����s����X�V
	/// </summary>
	/// <param name="lightCameraPos"></param>
	/// <param name="lightCameraTarget"></param>
	void UpdateFromLightTaraget(const Vector3& lightCameraPos, const Vector3& lightCameraTarget);
	/// <summary>
	/// �X�V(���C�g�J�����̌������w�肷��o�[�W����)
	/// </summary>
	/// <param name="lightCameraPos"></param>
	/// <param name="lightDir"></param>
	void UpdateFromLightDirection(const Vector3& lightCameraPos, const Vector3& lightDir);
	/// <summary>
	/// �V���h�E�}�b�v�ɃV���h�E�L���X�^�[�������_�����O
	/// </summary>
	void RenderToShadowMap(RenderContext& rc);
	/// <summary>
	/// �V���h�E�L���X�^�[��ǉ�
	/// </summary>
	/// <param name="shadowCaster"></param>
	void RegistShadowCaster(Model* shadowCaster)
	{
		m_shadowCaters.push_back(shadowCaster);
	}
	/// <summary>
	/// �V���h�E�}�b�v�̃e�N�X�`�����擾
	/// </summary>
	/// <returns></returns>
	Texture& GetShadowMapTexture()
	{
		return m_shadowMapRT.GetRenderTargetTexture();
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g���擾
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetRenderTarget()
	{
		return &m_shadowMapRT;
	}
private:
	Vector3 m_lightCameraPosition = Vector3(300.0f, 300.0f, -300.0f);		//���C�g�J�����̍��W	
	Vector3 m_lightCamerataraget = Vector3(0.0f, 0.0f, 0.0f);		//���C�g�J�����̒����_
	Matrix m_lightViewMatrix;			//���C�g�r���[�s��
	Matrix m_lightProjMatrix;			//���C�g�v���W�F�N�V�����s��
	RenderTarget m_shadowMapRT;			//�V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g
	std::vector<Model*> m_shadowCaters;		//�V���h�E�L���X�^�[�̃��X�g
};

