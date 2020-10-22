#pragma once

/// <summary>
/// �f�B�X�N���v�^�q�[�v�B
/// </summary>
class DescriptorHeap {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~DescriptorHeap(); 
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* Get();
	/// <summary>
	/// �V�F�[�_�[���\�[�X���f�B�X�N���v�^�q�[�v�ɓo�^�B
	/// </summary>
	/// <param name="registerNo">���W�X�^�ԍ�</param>
	/// <param name="sr">�V�F�[�_�[���\�[�X</param>
	void RegistShaderResource(int registerNo, IShaderResource& sr)
	{
		if (registerNo < MAX_SHADER_RESOURCE) {
			m_shaderResources[registerNo] = &sr;
			if (m_numShaderResource < registerNo + 1) {
				m_numShaderResource = registerNo + 1;
			}
		}
		else {
			MessageBox(nullptr, L"DescriptorHeap::RegistShaderResource() ���W�X�^�ԍ����͈͊O�ł��B", L"�G���[", MB_OK );
			std::abort();
		}
	}
	/// <summary>
	/// �A���I�[�_�[�A�N�Z�X���\�[�X��o�^�B
	/// </summary>
	/// <param name="registerNo">���W�X�^�ԍ�</param>
	/// <param name="sr">�A���I�[�_�[���\�[�X</param>
	void RegistUnorderAccessResource(int registerNo, IUnorderAccessResrouce& sr)
	{
		if (registerNo < MAX_SHADER_RESOURCE) {
			m_uavResoruces[registerNo] = &sr;
			if (m_numUavResource < registerNo + 1) {
				m_numUavResource = registerNo + 1;
			}
		}
		else {
			MessageBox(nullptr, L"DescriptorHeap::RegistShaderResource() ���W�X�^�ԍ����͈͊O�ł��B", L"�G���[", MB_OK);
			std::abort();
		}
	}
	/// <summary>
	/// �萔�o�b�t�@���f�B�X�N���v�^�q�[�v�ɓo�^�B
	/// </summary>
	/// <param name="registerNo">���W�X�^�ԍ�</param>
	/// <param name="cb">�萔�o�b�t�@</param>
	void RegistConstantBuffer(int registerNo, ConstantBuffer& cb)
	{
		if (registerNo < MAX_CONSTANT_BUFFER) {
			m_constantBuffers[registerNo] = &cb;
			if (m_numConstantBuffer < registerNo + 1) {
				m_numConstantBuffer = registerNo + 1;
			}
		}
		else {
			MessageBox(nullptr, L"DescriptorHeap::RegistConstantBuffer() ���W�X�^�ԍ����͈͊O�ł��B", L"�G���[", MB_OK);
			std::abort();
		}
	}
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�ւ̓o�^���m��B
	/// </summary>
	void Commit();
	/// <summary>
	/// �萔�o�b�t�@�̃f�B�X�N���v�^�̊J�n�n���h�����擾�B
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetConstantBufferGpuDescritorStartHandle() const;
	/// <summary>
	/// �V�F�[�_�[���\�[�X�̃f�B�X�N���v�^�̊J�n�n���h�����擾�B
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetShaderResourceGpuDescritorStartHandle() const;
	D3D12_GPU_DESCRIPTOR_HANDLE GetUavResourceGpuDescritorStartHandle() const;
	/// <summary>
	/// �V�F�[�_�[���\�[�X����ł��o�^����Ă��邩����B
	/// </summary>
	/// <returns></returns>
	bool IsRegistShaderResource() const
	{
		return m_numShaderResource != 0;
	}
	bool IsRegistConstantBuffer() const
	{
		return m_numConstantBuffer != 0;
	}
	bool IsRegistUavResource() const
	{
		return m_numUavResource != 0;
	}
private:
	enum {
		MAX_SHADER_RESOURCE = 64,	//�V�F�[�_�[���\�[�X�̍ő吔�B
		MAX_CONSTANT_BUFFER = 64,	//�萔�o�b�t�@�̍ő吔�B
	};
	int m_numShaderResource = 0;	//�V�F�[�_�[���\�[�X�̐��B
	int m_numConstantBuffer = 0;	//�萔�o�b�t�@�̐��B
	int m_numUavResource = 0;
	ID3D12DescriptorHeap* m_descriptorHeap[2] = { nullptr };					//�f�B�X�N���v�^�q�[�v�B
	IShaderResource* m_shaderResources[MAX_SHADER_RESOURCE] = {nullptr};		//�V�F�[�_�[���\�[�X�B7
	IUnorderAccessResrouce* m_uavResoruces[MAX_SHADER_RESOURCE] = { nullptr };	//UAV���\�[�X�B
	ConstantBuffer* m_constantBuffers[MAX_CONSTANT_BUFFER] = { nullptr };	//�萔�o�b�t�@�B
	D3D12_GPU_DESCRIPTOR_HANDLE m_cbGpuDescriptorStart[2];					//�萔�o�b�t�@�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h���B
	D3D12_GPU_DESCRIPTOR_HANDLE m_srGpuDescriptorStart[2];					//�V�F�[�_�[���\�[�X�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h���B
	D3D12_GPU_DESCRIPTOR_HANDLE m_uavGpuDescriptorStart[2];					//UAV���\�[�X�̃f�B�X�N���v�^�q�[�v�̊J�n�n���h���B
};