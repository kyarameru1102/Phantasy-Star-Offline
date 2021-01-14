#pragma once

#include "tkFile/TkmFile.h"
#include "MeshParts.h"
#include "Skeleton.h"

class IShaderResource;

/// <summary>
/// モデルの初期化データ
/// </summary>
struct ModelInitData {
	const char* m_tkmFilePath = nullptr;		//tkmファイルパス。
	const char* m_vsEntryPointFunc = "VSMain";	//頂点シェーダーのエントリーポイント。
	const char* m_psEntryPointFunc = "PSMain";	//ピクセルシェーダーのエントリーポイント。
	const char* m_fxFilePath = nullptr;			//.fxファイルのファイルパス。
	void* m_expandConstantBuffer = nullptr;		//ユーザー拡張の定数バッファ。
	int m_expandConstantBufferSize = 0;			//ユーザー拡張の定数バッファのサイズ。
	IShaderResource* m_expandShaderResoruceView = nullptr;	//ユーザー拡張のシェーダーリソース。
};
/// <summary>
/// モデルクラス。
/// </summary>
class Model {

public:
	
	/// <summary>
	/// tkmファイルから初期化。
	/// </summary>
	/// <param name="initData">初期化データ</param>
	void Init( const ModelInitData& initData );
	/// <summary>
	/// ワールド行列の更新。
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale);

	/// <summary>
	/// スケルトンを関連付ける。
	/// </summary>
	/// <param name="skeleton">スケルトン</param>
	void BindSkeleton()
	{
		m_meshParts.BindSkeleton(m_skeleton);
	}
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="renderContext">レンダリングコンテキスト</param>
	void Draw(RenderContext& renderContext, EnRenderMode renderMode = enRenderMode_Normal, int shadowMapNumber = 0);
	/// <summary>
	/// ワールド行列を取得。
	/// </summary>
	/// <returns></returns>
	const Matrix& GetWorldMatrix() const
	{
		return m_world;
	}
	/// <summary>
	/// tkmファイルを取得。
	/// </summary>
	/// <returns></returns>
	const TkmFile& GetTkmFile() const
	{
		return m_tkmFile;
	}
	/// <summary>
	/// メッシュに対して問い合わせを行う。
	/// </summary>
	/// <param name="queryFunc">問い合わせ関数</param>
	void QueryMeshs(std::function<void(const SMesh& mesh)> queryFunc)
	{
		m_meshParts.QueryMeshs(queryFunc);
	}
	/*void QueryMeshAndDescriptorHeap(std::function<void(const SMesh& mesh, const DescriptorHeap& ds)> queryFunc)
	{
		m_meshParts.QueryMeshAndDescriptorHeap(queryFunc);
	}*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;/**m_meshParts.GetSkeleton();*/
	}
	/// <summary>
	/// シャドウキャスターのフラグを設定
	/// </summary>
	/// <param name="isFlag"></param>
	void SetShadowCaster(bool isFlag)
	{
		m_isShadowCaster = isFlag;
	}
	/// <summary>
	/// シャドウキャスターかどうかを取得
	/// </summary>
	/// <returns></returns>
	bool GetShadowCaster()
	{
		return m_isShadowCaster;
	}
private:
	void InitSkeleton(const char* filePath);
private:

	Matrix m_world;			//ワールド行列。
	TkmFile m_tkmFile;		//tkmファイル。
	Skeleton m_skeleton;	//スケルトン。
	MeshParts m_meshParts;	//メッシュパーツ。
	bool m_isShadowCaster = true;
};
