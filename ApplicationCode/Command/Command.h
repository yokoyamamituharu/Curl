#pragma once
class Command
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Command() {}

public: //�����o�֐�
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	virtual void Excute() = 0;
};

