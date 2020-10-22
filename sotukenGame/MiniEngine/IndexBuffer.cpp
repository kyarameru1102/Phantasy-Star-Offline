#include "stdafx.h"
#include "IndexBuffer.h"


IndexBuffer::~IndexBuffer()
{
	if (m_indexBuffer) {
		m_indexBuffer->Release();
	}
}
void IndexBuffer::Init(int size, int stride)
{
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(size),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_indexBuffer));
	
	//�C���f�b�N�X�o�b�t�@�̃r���[���쐬�B
	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.SizeInBytes = size;
	if (stride == 2) {
		//�X�g���C�h���Q�o�C�g�B
		m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
	}
	else if (stride == 4) {
		//�X�g���C�h���S�o�C�g�B
		m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	}
	m_count = size / stride;
}
void IndexBuffer::Copy(void* srcIndecies)
{
	auto device = g_graphicsEngine->GetD3DDevice();
	DirectX::ResourceUploadBatch re(device);
	re.Begin();
	D3D12_SUBRESOURCE_DATA subResourceData;
	subResourceData.pData = srcIndecies;
	subResourceData.RowPitch = m_indexBufferView.SizeInBytes;
	subResourceData.SlicePitch = 1;
	re.Upload(
		m_indexBuffer,
		0,
		&subResourceData,
		1);

	re.End(g_graphicsEngine->GetCommandQueue());
}