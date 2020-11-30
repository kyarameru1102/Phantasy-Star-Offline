#pragma once
class Random
{
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Random();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Random();
	/*!
	 * @brief	�������������B
	 *@param[in]	seed		�����_���V�[�h�B
	 */
	void Init(unsigned long seed);

private:
	static const unsigned long N = 624;
	static const unsigned long M = 397;
	static const unsigned long MATRIX_A = 0x9908b0dfUL;   /* constant vector a */
	static const unsigned long UPPER_MASK = 0x80000000UL; /* most significant w-r bits */
	static const unsigned long LOWER_MASK = 0x7fffffffUL; /* least significant r bits */
	unsigned long mt[N]; /* the array for the state vector  */
	int mti = N + 1; /* mti==N+1 means mt[N] is not initialized */
};

