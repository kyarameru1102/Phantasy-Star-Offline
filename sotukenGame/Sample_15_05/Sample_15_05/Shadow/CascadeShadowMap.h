#pragma once
#include "RenderTarget.h"
#include "RenderMode.h"


class Model;
class CascadeShadowMap


{
public:
	CascadeShadowMap();
	/// <summary>
	/// ライトビュー行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix GetLightViewMatrix()
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ライトプロジェクション行列を取得
	/// </summary>
	/// <returns></returns>
	Matrix GetLightProjMatrix()
	{
		return m_lightProjMatrix;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ライトビュー行列やライトプロジェクション行列を更新
	/// </summary>
	/// <param name="lightCameraPos"></param>
	/// <param name="lightCameraTarget"></param>
	void UpdateFromLightTaraget(const Vector3& lightCameraPos, const Vector3& lightCameraTarget);
	/// <summary>
	/// 更新(ライトカメラの向きを指定するバージョン)
	/// </summary>
	/// <param name="lightCameraPos"></param>
	/// <param name="lightDir"></param>
	void UpdateFromLightDirection(const Vector3& lightCameraPos, const Vector3& lightDir);
	/// <summary>
	/// シャドウマップにシャドウキャスターをレンダリング
	/// </summary>
	void RenderToShadowMap(RenderContext& rc);
	/// <summary>
	/// シャドウキャスターを追加
	/// </summary>
	/// <param name="shadowCaster"></param>
	void RegistShadowCaster(Model* shadowCaster)
	{
		m_shadowCaters.push_back(shadowCaster);
	}
	/// <summary>
	/// シャドウマップのテクスチャを取得
	/// </summary>
	/// <returns></returns>
	Texture& GetShadowMapTexture(int number)
	{
		return m_shadowMapRT[number].GetRenderTargetTexture();
	}
	/// <summary>
	/// レンダリングターゲットを取得
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetRenderTarget(int number)
	{
		return &m_shadowMapRT[number];
	}
	/// <summary>
	/// ライトの高さ
	/// </summary>
	/// <param name="lightHeight"></param>
	void SetLightHeight(const float lightHeight)
	{
		m_lightHeight = lightHeight;
	}
	/// <summary>
	/// ライトの方向を設定
	/// </summary>
	/// <param name="lightDir"></param>
	void SetLightDirection(const Vector3& lightDir)
	{
		m_lightDir = lightDir;
	}
	/// <summary>
	/// ライトビュープロジェクション行列を取得
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
	/// シャドウマップの番号を取得、0からよ
	/// </summary>
	/// <returns></returns>
	int GetShadowMapNumber() const
	{
		return m_shadowMapNumber;
	}
	/// <summary>
	/// ライトの方向を取得
	/// </summary>
	/// <returns></returns>
	Vector3& GetLightDir()
	{
		return m_lightDir;
	}
	/// <summary>
	/// 各シャドウマップの限界深度値を取得
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	float GetFar(const int number)
	{
		return m_farList[number];
	}
	static const int SHADOWMAP_NUM = 3;
private:
	Vector3 m_lightCameraPosition = Vector3(300.0f, 300.0f, -300.0f);		//ライトカメラの座標	
	Vector3 m_lightCamerataraget = Vector3(0.0f, 0.0f, 0.0f);		//ライトカメラの注視点
	Matrix m_lightViewMatrix;			//ライトビュー行列
	Matrix m_lightProjMatrix;			//ライトプロジェクション行列
	RenderTarget m_shadowMapRT[SHADOWMAP_NUM];			//シャドウマップのレンダリングターゲット
	Matrix m_lightVieProjMatrix[SHADOWMAP_NUM];			//各シャドウマップのビュープロジェクション行列
	std::vector<Model*> m_shadowCaters;		//シャドウキャスターのリスト
	Vector3 m_lightDir = Vector3(-0.6396f,-0.6396f,-0.4264f);
	float m_lightHeight = 2000.0f;
	int m_shadowMapNumber = 0;
	float m_farList[SHADOWMAP_NUM];
};


