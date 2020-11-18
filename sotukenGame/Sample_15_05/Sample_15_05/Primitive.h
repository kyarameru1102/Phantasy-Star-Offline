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
		/// �������B
		/// </summary>
		/// <param name="srcVertexData">���_�o�b�t�@�̃\�[�X�f�[�^�B</param>
		/// <param name="vertexBufferSize">���_�o�b�t�@�̃T�C�Y�B</param>
		/// <param name="vertexBufferStride">���_�o�b�t�@�̃X�g���C�h�B</param>
		/// <param name="srcIndexData">�C���f�b�N�X�o�b�t�@�̃\�[�X�f�[�^�B</param>
		/// <param name="indexBufferSize">�C���f�b�N�X�o�b�t�@�̃T�C�Y�B</param>
		/// <param name="indexBufferStride">�C���f�b�N�X�o�b�t�@�̃X�g���C�h�B</param>
		/// <param name="enPrimTopology">�v���~�e�B�u�̃g�|���W�[�B</param>
		/// <returns></returns>
	void Init(
		void* srcVertexData,
		int vertexBufferSize,
		int vertexBufferStride,
		void* srcIndexData,
		int indexBufferSize,
		int indexBufferStride,
		D3D12_PRIMITIVE_TOPOLOGY enPrimTopology);
	//���_�o�b�t�@���擾
	VertexBuffer& GetVertexBuffer()
	{
		return m_vertexBuffer;
	}
	//�C���f�b�N�X�o�b�t�@���擾
	IndexBuffer& GetIndexBuffer()
	{
		return m_indexBuffer;
	}
	//�v���~�e�B�u�̃g�|���W�[���擾
	D3D12_PRIMITIVE_TOPOLOGY& GetPrimitiveTopology()
	{
		return m_topology;
	}
private:
	VertexBuffer m_vertexBuffer;		//���_�o�b�t�@
	IndexBuffer m_indexBuffer;			//�C���f�b�N�X�o�b�t�@
	RootSignature m_rootSignature;	//���[�g�V�O�l�`���B
	PipelineState m_pipelineState;	//�p�C�v���C���X�e�[�g�B
	D3D12_PRIMITIVE_TOPOLOGY m_topology;	//�g�|���W�[�B
};