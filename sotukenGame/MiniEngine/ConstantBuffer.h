#pragma once


class ConstantBuffer{
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~ConstantBuffer();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="size">�萔�o�b�t�@�̃T�C�Y�B</param>
	/// <param name="srcData">�\�[�X�f�[�^�Bnull���w�肷�邱�Ƃ��\�B</param>
	void Init(int size, void* srcData = nullptr);
	/// <summary>
	/// ���p�\�ȃo�b�t�@���ǂ����𔻒�B
	/// </summary>
	/// <returns></returns>
	bool IsValid() const
	{
		return m_isValid;
	}
	/// <summary>
	/// �f�[�^��VRAM�ɃR�s�[����B
	/// </summary>
	/// <param name="data"></param>
	void CopyToVRAM(void* data);
	template< class T>
	void CopyToVRAM(T& data)
	{
		CopyToVRAM(&data);
	}
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v��ConstantBufferView��o�^�B
	/// </summary>
	/// <param name="descriptorHandle"></param>
	void RegistConstantBufferView(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle);
	void RegistConstantBufferView(D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle, int bufferNo);
private:
	ID3D12Resource* m_constantBuffer[2] = {nullptr};//�萔�o�b�t�@�B
	void* m_constBufferCPU[2] = { nullptr };		//CPU������A�N�Z�X�ł��邷��萔�o�b�t�@�̃A�h���X�B
	int m_size = 0;									//�萔�o�b�t�@�̃T�C�Y�B
	int m_allocSize = 0;
	bool m_isValid = false;							//���p�\�H
};
