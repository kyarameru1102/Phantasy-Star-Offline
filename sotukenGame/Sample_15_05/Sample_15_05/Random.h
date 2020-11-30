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

private:
	static const unsigned long N = 624;
	static const unsigned long M = 397;
	static const unsigned long MATRIX_A = 0x9908b0dfUL;   /* constant vector a */
	static const unsigned long UPPER_MASK = 0x80000000UL; /* most significant w-r bits */
	static const unsigned long LOWER_MASK = 0x7fffffffUL; /* least significant r bits */

};

