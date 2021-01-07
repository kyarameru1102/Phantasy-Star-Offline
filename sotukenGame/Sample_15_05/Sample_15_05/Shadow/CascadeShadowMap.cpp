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
}

void CascadeShadowMap::UpdateFromLightTaraget(const Vector3& lightCameraPos,const Vector3& lightCameraTarget)
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

void CascadeShadowMap::Update()
{
	//ライトの方向によって、ライトカメラの上方向を決める
	Vector3 lightCameraUpAxis;
	if (fabsf(m_lightDir.y) > 0.999998f) {
		//ほぼ真上or真下を向いているので、1,0,0を上方向とする
		lightCameraUpAxis = Vector3::AxisX;
	}
	else {
		//それ以外のときは、0,1,0を上方向とする
		lightCameraUpAxis = Vector3::AxisY;
	}
	m_lightDir.Normalize();
	//Matrix lightViewMatrix;

	Matrix lightViewRot;
	{
		//シーンをレンダリング使用としているカメラを使って、ライトカメラの回転を求める。
		auto cameraDir = g_camera3D->GetForward();
		if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
			//ほぼ真上をむいている。
			return;
		}
		//ライトビュー行列の回転成分を計算する。
		Vector3 lightViewForward = m_lightDir;
		Vector3 lightViewUp;
		if (fabsf(lightViewForward.y) > 0.999f) {
			//ほぼ真上。
			lightViewUp.Cross(lightViewForward, Vector3::Right);
		}
		else {
			lightViewUp.Cross(lightViewForward, Vector3::Up);
		}
		lightViewUp.Normalize();
		Vector3 lgihtViewRight;
		lgihtViewRight.Cross(lightViewUp, lightViewForward);
		lgihtViewRight.Normalize();

		
		//ライトビューの横を設定する。
		lightViewRot.m[0][0] = lgihtViewRight.x;
		lightViewRot.m[0][1] = lgihtViewRight.y;
		lightViewRot.m[0][2] = lgihtViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//ライトビューの上を設定する。
		lightViewRot.m[1][0] = lightViewUp.x;
		lightViewRot.m[1][1] = lightViewUp.y;
		lightViewRot.m[1][2] = lightViewUp.z;
		lightViewRot.m[1][3] = 0.0f;
		//ライトビューの前を設定する。
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
		//視錘台の8つの頂点を求める
		//xとy成分の最大最小を求める
		float x1 = nearClip * tan(FOVX / 2);
		float x2 = farClip * tan(FOVX / 2);
		float y1 = nearClip * tan(FOVY / 2);
		float y2 = farClip * tan(FOVY / 2);

		//xとy成分から近平面の4つの頂点を求める
		Vector3 pos[8];
		pos[0] = Vector3(x1, y1, nearClip);
		pos[1] = Vector3(-x1, y1, nearClip);
		pos[2] = Vector3(x1, -y1, nearClip);
		pos[3] = Vector3(-x1, -y1, nearClip);

		//遠平面の4つの頂点を求める
		pos[4] = Vector3(x2, y2, farClip);
		pos[5] = Vector3(-x2, y2, farClip);
		pos[6] = Vector3(x2, -y2, farClip);
		pos[7] = Vector3(-x2, -y2, farClip);

		Vector3 posSum = Vector3::Zero;
		for (int i = 0; i < 8; i++) {
			//カメラの逆ビュー行列をかけて、カメラビュー座標をワールド座標に変換する
			inverseViewMatrix.Apply(pos[i]);
			posSum.Add(pos[i]);
			/*if (pos[i].y <= -2000.0f) {
				pos[i].y = -2000.0f;
 			}
			else if (pos[i].y >= 2000.0f) {
				pos[i].y = 2000.0f;
 			}*/
		}

		//中央の座標を求めていく
		Vector3 centerPos = posSum / 8;

		//視推台の中央の座標とライトの高さを元にライトの座標を決めていく
		//float scaler = (m_lightHeight - centerPos.y) / m_lightDir.y;
		//Vector3 lightPos = centerPos + m_lightDir * scaler;

		Vector3 topPos = centerPos;
		topPos.x = 0.0f;
		topPos.y = 8000.0f - centerPos.y;
		topPos.z = 0.0f;
		float s = m_lightDir.Dot(topPos);
		Vector3 lightPos = centerPos + m_lightDir * s;

		Matrix lightViewMatrix = lightViewRot;
		//ライトの座標を代入して、ライトビュー行列完成
		lightViewMatrix.m[3][0] = lightPos.x;
		lightViewMatrix.m[3][1] = lightPos.y;
		lightViewMatrix.m[3][2] = lightPos.z;
		lightViewMatrix.m[3][3] = 1.0f;
		lightViewMatrix.Inverse(lightViewMatrix);	//ライトビュー完成。

		Vector3 vectorMin = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		Vector3 vectorMax = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

		for (int i = 0; i < 8; i++) {
			//ライトビュー行列をかけて、ワールド座標をライトカメラビュー座標に変換する
			lightViewMatrix.Apply(pos[i]);

			//最大最小を求めていく
			vectorMin.x = min(vectorMin.x, pos[i].x);
			vectorMax.x = max(vectorMax.x, pos[i].x);
			vectorMin.y = min(vectorMin.y, pos[i].y);
			vectorMax.y = max(vectorMax.y, pos[i].y);
			vectorMin.z = min(vectorMin.z, pos[i].z);
			vectorMax.z = max(vectorMax.z, pos[i].z);
		}

		float w = vectorMax.x - vectorMin.x;
		float h = vectorMax.y - vectorMin.y;

		//プロジェクション行列をつくっていくぅ
		Matrix projMatrix;
		projMatrix.MakeOrthoProjectionMatrix(
			w,
			h,
			1.0f,
			vectorMax.z
		);

		//ライトビュープロジェクション行列を求めていくぅ～
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
		//シャドウマップのレンダリングターゲットを待機完了状態にする
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
	//シャドウマップのレンダリングターゲットを待機完了状態にする
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