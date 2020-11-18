#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <d3d12.h>
#include "RootSignature.h"
#include "PipelineState.h"


enum EnPrimitiveTopology {
	enPrimitiveTopology_TriangleList = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	enPrimitiveTopology_TriangleStrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	enPrimitiveTopology_Undex = 0xFFFFFFFF
};
class Primitive
{
public:
	/// <summary>
		/// 初期化。
		/// </summary>
		/// <param name="srcVertexData">頂点バッファのソースデータ。</param>
		/// <param name="vertexBufferSize">頂点バッファのサイズ。</param>
		/// <param name="vertexBufferStride">頂点バッファのストライド。</param>
		/// <param name="srcIndexData">インデックスバッファのソースデータ。</param>
		/// <param name="indexBufferSize">インデックスバッファのサイズ。</param>
		/// <param name="indexBufferStride">インデックスバッファのストライド。</param>
		/// <param name="enPrimTopology">プリミティブのトポロジー。</param>
		/// <returns></returns>
	void Init(
		void* srcVertexData,
		int vertexBufferSize,
		int vertexBufferStride,
		void* srcIndexData,
		int indexBufferSize,
		int indexBufferStride,
		D3D12_PRIMITIVE_TOPOLOGY enPrimTopology);
	//頂点バッファを取得
	VertexBuffer& GetVertexBuffer()
	{
		return m_vertexBuffer;
	}
	//インデックスバッファを取得
	IndexBuffer& GetIndexBuffer()
	{
		return m_indexBuffer;
	}
	//プリミティブのトポロジーを取得
	D3D12_PRIMITIVE_TOPOLOGY& GetPrimitiveTopology()
	{
		return m_topology;
	}
private:
	VertexBuffer m_vertexBuffer;		//頂点バッファ
	IndexBuffer m_indexBuffer;			//インデックスバッファ
	RootSignature m_rootSignature;	//ルートシグネチャ。
	PipelineState m_pipelineState;	//パイプラインステート。
	D3D12_PRIMITIVE_TOPOLOGY m_topology;	//トポロジー。
};