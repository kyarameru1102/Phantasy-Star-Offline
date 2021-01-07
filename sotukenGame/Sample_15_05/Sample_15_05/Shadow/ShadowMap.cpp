#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_shadowMapRT.Create(
		4096,
		4096,
		1,
		1,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT,
		clearColor
	);
}

void ShadowMap::UpdateFromLightTaraget(const Vector3& lightCameraPos, const Vector3& lightCameraTarget)
{
	m_lightCameraPosition = lightCameraPos;
	m_lightCamerataraget = lightCameraTarget;
	//ライトの方向を計算する
	auto lightDir = m_lightCamerataraget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//ライトカメラの座標と注視点が近すぎるのでクラッシュさせる
		std::abort();
	}

	//正規化して、方向ベクトルに変換する
	lightDir.Normalize();

	UpdateFromLightDirection(lightCameraPos, lightDir);
}

void ShadowMap::UpdateFromLightDirection(const Vector3& lightCameraPos, const Vector3& lightDir)
{
	//ライトの方向によって、ライトカメラの上方向を決める
	Vector3 lightCameraUpAxis;

	if (fabsf(lightDir.y) > 0.999998f) {
		//ほぼ真上or真下を向いているので、1,0,0を上方向とする
		lightCameraUpAxis = Vector3::AxisX;
	}
	else {
		//それ以外のときは、0,1,0を上方向とする
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

	Matrix a = m_lightViewMatrix * m_lightProjMatrix;
}

void ShadowMap::RenderToShadowMap(RenderContext& rc)
{
	RenderTarget* rt[] = {
		&m_shadowMapRT
	};
	//シャドウマップのレンダリングターゲットを待機完了状態にする
	rc.WaitUntilToPossibleSetRenderTargets(1, rt);
	//rc.SetRenderTarget(g_graphicsEngine->GetDSVCpuDescriptorHandle(), m_shadowMapRT.GetRTVCpuDescriptorHandle());
	rc.SetRenderTargetAndViewport(m_shadowMapRT);
	//rc.SetRenderTargets(1, rt);
	rc.ClearRenderTargetViews(1, rt);
	//g_graphicsEngine->BeginDeferredRender();

	if (m_shadowCaters.size() >= 1) {
		for (auto caster : m_shadowCaters) {
			caster->Draw(rc, enRenderMode_CreateShadowMap);
		}
	}

	m_shadowCaters.clear();

	//g_graphicsEngine->EndModelDraw();

	//g_graphicsEngine->ChangeRenderTargetToFrameBuffer(g_graphicsEngine->GetRenderContext());
}
