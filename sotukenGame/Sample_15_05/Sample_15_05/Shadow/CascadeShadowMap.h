#pragma once
#include "RenderTarget.h"
#include "RenderMode.h"


class Model;
class CascadeShadowMap


{
public:
	CascadeShadowMap();
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
	/// �X�V
	/// </summary>
	void Update();
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
	Texture& GetShadowMapTexture(int number)
	{
		return m_shadowMapRT[number].GetRenderTargetTexture();
	}
	/// <summary>
	/// �����_�����O�^�[�Q�b�g���擾
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetRenderTarget(int number)
	{
		return &m_shadowMapRT[number];
	}
	/// <summary>
	/// ���C�g�̍���
	/// </summary>
	/// <param name="lightHeight"></param>
	void SetLightHeight(const float lightHeight)
	{
		m_lightHeight = lightHeight;
	}
	/// <summary>
	/// ���C�g�̕�����ݒ�
	/// </summary>
	/// <param name="lightDir"></param>
	void SetLightDirection(const Vector3& lightDir)
	{
		m_lightDir = lightDir;
	}
	/// <summary>
	/// ���C�g�r���[�v���W�F�N�V�����s����擾
	/// </summary>
	/// <returns></returns>
	Matrix& GetLightViewProjMatrix()
	{
		return m_lightVieProjMatrix[m_shadowMapNumber];
	}
	Matrix& GetLightViewProjMatrix(int number)
	{
		return m_lightVieProjMatrix[number];
	}
	/// <summary>
	/// �V���h�E�}�b�v�̔ԍ����擾�A0�����
	/// </summary>
	/// <returns></returns>
	int GetShadowMapNumber() const
	{
		return m_shadowMapNumber;
	}
	/// <summary>
	/// ���C�g�̕������擾
	/// </summary>
	/// <returns></returns>
	Vector3& GetLightDir()
	{
		return m_lightDir;
	}
	/// <summary>
	/// �e�V���h�E�}�b�v�̌��E�[�x�l���擾
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	float GetFar(const int number)
	{
		return m_farList[number];
	}
	static const int SHADOWMAP_NUM = 3;
private:
	Vector3 m_lightCameraPosition = Vector3(300.0f, 300.0f, -300.0f);		//���C�g�J�����̍��W	
	Vector3 m_lightCamerataraget = Vector3(0.0f, 0.0f, 0.0f);		//���C�g�J�����̒����_
	Matrix m_lightViewMatrix;			//���C�g�r���[�s��
	Matrix m_lightProjMatrix;			//���C�g�v���W�F�N�V�����s��
	RenderTarget m_shadowMapRT[SHADOWMAP_NUM];			//�V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g
	Matrix m_lightVieProjMatrix[SHADOWMAP_NUM];			//�e�V���h�E�}�b�v�̃r���[�v���W�F�N�V�����s��
	std::vector<Model*> m_shadowCaters;		//�V���h�E�L���X�^�[�̃��X�g
	Vector3 m_lightDir = Vector3(-0.6396f,-0.6396f,-0.4264f);
	float m_lightHeight = 2000.0f;
	int m_shadowMapNumber = 0;
	float m_farList[SHADOWMAP_NUM];
};


