#pragma once

/// <summary>
/// �C���f�b�N�X�o�b�t�@�B
/// </summary>
class IndexBuffer {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~IndexBuffer(); 
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="size">�C���f�b�N�X�o�b�t�@�̃T�C�Y�B</param>
	/// <param name="stride">�X�g���C�h�B</param>
	void Init(int size, int stride) ;
	/// <summary>
	/// �C���f�b�N�X�f�[�^���C���f�b�N�X�o�b�t�@�ɃR�s�[�B
	/// </summary>
	/// <param name="srcIndecies">�R�s�[���̃C���f�b�N�X�f�[�^�B</param>
	void Copy(void* srcIndecies) ;
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�r���[���擾�B
	/// </summary>
	/// <returns></returns>
	D3D12_INDEX_BUFFER_VIEW& GetView()
	{
		return m_indexBufferView;
	}
	/// <summary>
	/// �C���f�b�N�X�̐����擾�B
	/// </summary>
	/// <returns>�C���f�b�N�X�̐��B</returns>
	int GetCount() const
	{
		return m_count;
	}
private:
	ID3D12Resource* m_indexBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@�B
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;	//�C���f�b�N�X�o�b�t�@�r���[�B
	int m_count = 0;							//�C���f�b�N�X�̐��B
};