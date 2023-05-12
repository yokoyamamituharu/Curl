#pragma once
#include "KeyInput.h"
#include "MouseInput.h"
#include "PlayerCommand.h"
#include "LeftMoveCommand.h"
#include "RightMoveCommand.h"
#include "UpMoveCommand.h"
#include "DownMoveCommand.h"
//#include "Player.h"

class KeyInputHandler
{
public: //�񋓌^

	enum class Commands {
		LeftMove,
		RightMove,
		UpMove,
		DownMove,
		None
	};

public: //�����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	KeyInputHandler() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~KeyInputHandler();

	/// <summary>
	/// ������
	/// </summary>
	//void Initialize(Player* player);

	/// <summary>
	/// �v���C���[�֘A�̃L�[���͎�t
	/// </summary>
	void PlayerHandleInput();

	/// <summary>
	/// W�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_W(Commands command);

	/// <summary>
	/// A�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_A(Commands command);

	/// <summary>
	/// S�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_S(Commands command);

	/// <summary>
	/// D�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_D(Commands command);

	/// <summary>
	/// ���N���b�N���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_LeftClick(Commands command);

	/// <summary>
	/// �E�N���b�N���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_RightClick(Commands command);

	/// <summary>
	/// R�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_R(Commands command);

	/// <summary>
	/// Space�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_Space(Commands command);

	/// <summary>
	/// ��Shift�L�[���蓖�ĕύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	void KeyBindChange_LShift(Commands command);

private: //�����o�֐�
	/// <summary>
	/// �L�[�o�C���h�ύX
	/// </summary>
	/// <param name="command">���蓖�Ă�R�}���h</param>
	PlayerCommand* KeyBindChange (Commands command);

private: //�����o�ϐ�
	//�v���C���[
	//Player* player_;

	//W�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* wKey_;
	//A�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* aKey_;
	//S�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* sKey_;
	//D�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* dKey_;
	//���N���b�N�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* leftClick_;
	//�E�N���b�N�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* rightClick_;
	//��Shift�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* leftShiftKey_;
	//R�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* rKey_;
	//Space�L�[�Ɋ��蓖�ĂĂ���R�}���h
	PlayerCommand* spaceKey_;

};
