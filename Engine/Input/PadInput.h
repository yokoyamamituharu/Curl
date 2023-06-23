#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class PadInput final
{
public: //enum
	enum PadButton {
		Button_A,
		Button_B,
		Button_X,
		Button_Y,
		Button_LB,
		Button_RB,
		Button_View,
		Button_Menu,
		Button_LS,
		Button_RS,
		Stick_Up,
		Stick_Down,
		Stick_Left,
		Stick_Right,
		Button_Max,
	};

	enum PadCrossKey {
		CrossKey_Neutral = -1,
		CrossKey_Up = 0,
		CrossKey_UpperRight = 4500,
		CrossKey_Right = 9000,
		CrossKey_LowerRight = 13500,
		CrossKey_Lower = 18000,
		CrossKey_LowerLeft = 22500,
		CrossKey_Left = 27000,
		CrossKey_UpperLeft = 31500
	};

	enum ButtonState {
		ButtonStateNone,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	};

	//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
	struct DeviceEnumParameter
	{
		LPDIRECTINPUTDEVICE8* GamePadDevice;
		int FindCount;
	};

private: //�G�C���A�X
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PadInput() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PadInput() = default;

	/// <summary>
	/// �R�s�[�R���X�g���N�^���֎~
	/// </summary>
	PadInput(const PadInput& obj) = delete;

	static BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

	static BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device);

	static BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device);

	static BOOL StartGamePadControl();

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	PadInput& operator=(const PadInput& obj) = delete;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �{�^���������m
	/// </summary>
	bool PushButton(BYTE buttonNumber);

	/// <summary>
	/// �{�^�����������u�Ԃ̂݌��m
	/// </summary>
	bool TriggerButton(BYTE buttonNumber);

	/// <summary>
	/// �\���L�[�������m
	/// </summary>
	bool PushCrossKey(LONG crossKeyNumber);

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static PadInput* GetIns();

	float leftStickX();
	float leftStickY();

	float rightStickX();
	float rightStickY();

	static float getLeftX();
	static float getLeftY();

	static float getRightX();
	static float getRightY();

private: //�����o�ϐ�
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> dinput;
	//�R���g���[���̃f�o�C�X
	static LPDIRECTINPUTDEVICE8 devPad;
	//�R���g���[���̏��
	static DIJOYSTATE padState;
	DIJOYSTATE prePadState;
	ButtonState p_ButtonState[Button_Max];

	static LPDIRECTINPUT8 p_Interface;

	const int unresponsive_range = 200;

	//WindowsAPI
	static WinApp* winApp;
};


