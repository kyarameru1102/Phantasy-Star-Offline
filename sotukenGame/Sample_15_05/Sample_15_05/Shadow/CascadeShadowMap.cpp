#include "stdafx.h"
#include "CascadeShadowMap.h"
#include "Model.h"
#include <limits>


CascadeShadowMap::CascadeShadowMap()
{
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float resTbl[SHADOWMAP_NUM][2] = {
			{1024, 1024},
			{512,   512},
			{256,   256}
	};
	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		m_shadowMapRT[i].Create(
			resTbl[i][0],
			resTbl[i][1],
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

}

void CascadeShadowMap::UpdateFromLightDirection(const Vector3& lightCameraPos, const Vector3& lightDir)
{
	//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�
	Vector3 lightCameraUpAxis;

	if (fabsf(lightDir.y) > 0.999998f) {
		//�قڐ^��or�^���������Ă���̂ŁA1,0,0��������Ƃ���
		lightCameraUpAxis = Vector3::AxisX;
	}
	else {
		//����ȊO�̂Ƃ��́A0,1,0��������Ƃ���
		lightCameraUpAxis = Vector3::AxisY;
	}
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCamerataraget,
		lightCameraUpAxis
	);

	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		500,
		500,
		10.0f,
		1500.0f
	);
}

void CascadeShadowMap::UpdateFromLightTaraget(const Vector3& lightCameraPos,const Vector3& lightCameraTarget)
{
	m_lightCameraPosition = lightCameraPos;
	m_lightCamerataraget = lightCameraTarget;
	//���C�g�̕������v�Z����
	auto lightDir = m_lightCamerataraget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//���C�g�J�����̍��W�ƒ����_���߂�����̂ŃN���b�V��������
		std::abort();
	}

	//���K�����āA�����x�N�g���ɕϊ�����
	lightDir.Normalize();

	UpdateFromLightDirection(lightCameraPos, lightDir);
}

void CascadeShadowMap::Update()
{
	//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�
	Vector3 lightCameraUpAxis;
	if (fabsf(m_lightDir.y) > 0.999998f) {
		//�قڐ^��or�^���������Ă���̂ŁA1,0,0��������Ƃ���
		lightCameraUpAxis = Vector3::AxisX;
	}
	else {
		//����ȊO�̂Ƃ��́A0,1,0��������Ƃ���
		lightCameraUpAxis = Vector3::AxisY;
	}
	m_lightDir.Normalize();
	//Matrix lightViewMatrix;

	Matrix lightViewRot;
	{
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		auto cameraDir = g_camera3D->GetForward();
		if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
			//�قڐ^����ނ��Ă���B
			return;
		}
		//���C�g�r���[�s��̉�]�������v�Z����B
		Vector3 lightViewForward = m_lightDir;
		Vector3 lightViewUp;
		if (fabsf(lightViewForward.y) > 0.999f) {
			//�قڐ^��B
			lightViewUp.Cross(lightViewForward, Vector3::Right);
		}
		else {
			lightViewUp.Cross(lightViewForward, Vector3::Up);
		}
		lightViewUp.Normalize();
		Vector3 lgihtViewRight;
		lgihtViewRight.Cross(lightViewUp, lightViewForward);
		lgihtViewRight.Normalize();

		
		//���C�g�r���[�̉���ݒ肷��B
		lightViewRot.m[0][0] = lgihtViewRight.x;
		lightViewRot.m[0][1] = lgihtViewRight.y;
		lightViewRot.m[0][2] = lgihtViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��B
		lightViewRot.m[1][0] = lightViewUp.x;
		lightViewRot.m[1][1] = lightViewUp.y;
		lightViewRot.m[1][2] = lightViewUp.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��B
		lightViewRot.m[2][0] = lightViewForward.x;
		lightViewRot.m[2][1] = lightViewForward.y;
		lightViewRot.m[2][2] = lightViewForward.z;
		lightViewRot.m[2][3] = 0.0f;



	}
	/*lightViewMatrix.MakeLookAt(
		Vector3::Zero,
		m_lightDir,
		lightCameraUpAxis
	);*/

	Matrix inverseViewMatrix = g_camera3D->GetViewMatrix();
	inverseViewMatrix.Inverse();
	float nearClip = g_camera3D->GetNear();
	float shadowAreaTbl[4] = {
		m_lightHeight * 1.0f,
		m_lightHeight * 2.5f,
		m_lightHeight * 5.0f,
		0.0f
	};
	float farClip = shadowAreaTbl[0];
	float FOVX = g_camera3D->GetViewAngle();
	float FOVY = FOVX / g_camera3D->GetAspect();

	float lightHeight = g_camera2D->GetTarget().y + m_lightHeight;

	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		//�������8�̒��_�����߂�
		//x��y�����̍ő�ŏ������߂�
		float x1 = nearClip * tan(FOVX / 2);
		float x2 = farClip * tan(FOVX / 2);
		float y1 = nearClip * tan(FOVY / 2);
		float y2 = farClip * tan(FOVY / 2);

		//x��y��������ߕ��ʂ�4�̒��_�����߂�
		Vector3 pos[8];
		pos[0] = Vector3(x1, y1, nearClip);
		pos[1] = Vector3(-x1, y1, nearClip);
		pos[2] = Vector3(x1, -y1, nearClip);
		pos[3] = Vector3(-x1, -y1, nearClip);

		//�����ʂ�4�̒��_�����߂�
		pos[4] = Vector3(x2, y2, farClip);
		pos[5] = Vector3(-x2, y2, farClip);
		pos[6] = Vector3(x2, -y2, farClip);
		pos[7] = Vector3(-x2, -y2, farClip);

		Vector3 posSum = Vector3::Zero;
		for (int i = 0; i < 8; i++) {
			//�J�����̋t�r���[�s��������āA�J�����r���[���W�����[���h���W�ɕϊ�����
			inverseViewMatrix.Apply(pos[i]);
			posSum.Add(pos[i]);
			/*if (pos[i].y <= -2000.0f) {
				pos[i].y = -2000.0f;
 			}
			else if (pos[i].y >= 2000.0f) {
				pos[i].y = 2000.0f;
 			}*/
		}

		//�����̍��W�����߂Ă���
		Vector3 centerPos = posSum / 8;

		//������̒����̍��W�ƃ��C�g�̍��������Ƀ��C�g�̍��W�����߂Ă���
		//float scaler = (m_lightHeight - centerPos.y) / m_lightDir.y;
		//Vector3 lightPos = centerPos + m_lightDir * scaler;

		Vector3 topPos = centerPos;
		topPos.x = 0.0f;
		topPos.y = 8000.0f - centerPos.y;
		topPos.z = 0.0f;
		float s = m_lightDir.Dot(topPos);
		Vector3 lightPos = centerPos + m_lightDir * s;

		Matrix lightViewMatrix = lightViewRot;
		//���C�g�̍��W�������āA���C�g�r���[�s�񊮐�
		lightViewMatrix.m[3][0] = lightPos.x;
		lightViewMatrix.m[3][1] = lightPos.y;
		lightViewMatrix.m[3][2] = lightPos.z;
		lightViewMatrix.m[3][3] = 1.0f;
		lightViewMatrix.Inverse(lightViewMatrix);	//���C�g�r���[�����B

		Vector3 vectorMin = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		Vector3 vectorMax = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

		for (int i = 0; i < 8; i++) {
			//���C�g�r���[�s��������āA���[���h���W�����C�g�J�����r���[���W�ɕϊ�����
			lightViewMatrix.Apply(pos[i]);

			//�ő�ŏ������߂Ă���
			vectorMin.x = min(vectorMin.x, pos[i].x);
			vectorMax.x = max(vectorMax.x, pos[i].x);
			vectorMin.y = min(vectorMin.y, pos[i].y);
			vectorMax.y = max(vectorMax.y, pos[i].y);
			vectorMin.z = min(vectorMin.z, pos[i].z);
			vectorMax.z = max(vectorMax.z, pos[i].z);
		}

		float w = vectorMax.x - vectorMin.x;
		float h = vectorMax.y - vectorMin.y;

		//�v���W�F�N�V�����s��������Ă�����
		Matrix projMatrix;
		projMatrix.MakeOrthoProjectionMatrix(
			w,
			h,
			1.0f,
			vectorMax.z
		);

		//���C�g�r���[�v���W�F�N�V�����s������߂Ă������`
		m_lightVieProjMatrix[i] = lightViewMatrix * projMatrix;

		m_farList[i] = farClip;
		nearClip = farClip;
		farClip = shadowAreaTbl[i + 1];
		
	}
}

void CascadeShadowMap::RenderToShadowMap(RenderContext& rc)
{
	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		m_shadowMapNumber = i;
		RenderTarget* rt[] = {
			&m_shadowMapRT[i]
		};
		//�V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g��ҋ@������Ԃɂ���
		rc.WaitUntilToPossibleSetRenderTargets(1, rt);
		//rc.SetRenderTarget(g_graphicsEngine->GetDSVCpuDescriptorHandle(), m_shadowMapRT.GetRTVCpuDescriptorHandle());
		rc.SetRenderTargetAndViewport(m_shadowMapRT[i]);
		//rc.SetRenderTargets(1, rt);
		rc.ClearRenderTargetViews(1, rt);
		//g_graphicsEngine->BeginDeferredRender();

		if (m_shadowCaters.size() >= 1) {
			for (auto caster : m_shadowCaters) {
				caster->Draw(rc, enRenderMode_CreateCascadeShadowMap);
			}
		}
		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRT[i]);
	}

	m_shadowCaters.clear();

	for (int i = 0; i < SHADOWMAP_NUM; i++) {
		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRT[i]);
	}

	/*RenderTarget* rt[] = {
		&m_shadowMapRT
	};
	//�V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g��ҋ@������Ԃɂ���
	rc.WaitUntilToPossibleSetRenderTargets(1, rt);
	//rc.SetRenderTarget(g_graphicsEngine->GetDSVCpuDescriptorHandle(), m_shadowMapRT.GetRTVCpuDescriptorHandle());
	rc.SetRenderTargetAndViewport(m_shadowMapRT);
	//rc.SetRenderTargets(1, rt);
	rc.ClearRenderTargetViews(1, rt);
	//g_graphicsEngine->BeginDeferredRender();

	if (m_shadowCaters.size() >= 1) {
		for (auto caster : m_shadowCaters) {
			caster->Draw(rc,enRenderMode_CreateShadowMap);
		}
	}

	m_shadowCaters.clear();

	//g_graphicsEngine->EndModelDraw();

	//g_graphicsEngine->ChangeRenderTargetToFrameBuffer(g_graphicsEngine->GetRenderContext());*/
}