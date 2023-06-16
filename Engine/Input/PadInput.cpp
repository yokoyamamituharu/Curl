#include "PadInput.h"

WinApp* PadInput::winApp = nullptr;
LPDIRECTINPUTDEVICE8 PadInput::devPad = nullptr;
DIJOYSTATE PadInput::padState = {};
LPDIRECTINPUT8 PadInput::p_Interface = nullptr; 

PadInput* PadInput::GetIns()
{
	static PadInput instance;
	return &instance;
}

BOOL PadInput::DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	// ���ɔ������Ă���Ȃ�I��
	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	// �f�o�C�X����
	HRESULT hr = p_Interface->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// ���̓t�H�[�}�b�g�̎w��
	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// �v���p�e�B�̐ݒ�
	if (SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	// �������x���̐ݒ�
	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	// ���������J�E���g
	parameter->FindCount++;

	return DIENUM_CONTINUE;
}
BOOL PadInput::SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Z���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Z;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// RX���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_RX;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// RY���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_RY;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// RZ���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_RZ;
	auto hr = device->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))
	{
		return true;
	}

	return true;
}
BOOL PadInput::SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	//�������[�h�̐ݒ�
	if (FAILED(device->SetCooperativeLevel(
		winApp->GetHwnd(),
		DISCL_EXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		return false;
	}

	return true;
}
BOOL PadInput::StartGamePadControl()
{
	// �f�o�C�X����������ĂȂ�
	if (devPad == nullptr)
	{
		return false;
	}

	// ����J�n
	if (FAILED(devPad->Acquire()))
	{
		return false;
	}

	DIDEVCAPS cap;
	devPad->GetCapabilities(&cap);
	// �|�[�����O����
	if (cap.dwFlags & DIDC_POLLEDDATAFORMAT)
	{
		DWORD error = GetLastError();
		// �|�[�����O�J�n
		/*
			Poll��Acquire�̑O�ɍs���Ƃ���Ă������A
			Acquire�̑O�Ŏ��s����Ǝ��s�����̂�
			��Ŏ��s����悤�ɂ���
		*/
		if (FAILED(devPad->Poll()))
		{
			return false;
		}
	}

	return true;
}

float PadInput::leftStickX()
{
	if (padState.lX < -unresponsive_range)
	{
		return padState.lX / 1000.0f;
		//is_push[ButtonKind::LeftButton] = true;
	}
	else if (padState.lX > unresponsive_range)
	{
		return padState.lX / 1000.0f;
		//is_push[ButtonKind::RightButton] = true;
	}

	return 0.0f;
}
float PadInput::leftStickY()
{
	if (padState.lY < -unresponsive_range)
	{
		return padState.lY / 1000.0f;
		//is_push[ButtonKind::UpButton] = true;
	}
	else if (padState.lY > unresponsive_range)
	{
		return padState.lY / 1000.0f;
		//is_push[ButtonKind::DownButton] = true;
	}

	return 0.0f;
}
float PadInput::rightStickX()
{
	if (padState.lRx < -unresponsive_range)
	{
		return padState.lRx / 1000.0f;
		//is_push[ButtonKind::LeftButton] = true;
	}
	else if (padState.lRx > unresponsive_range)
	{
		return padState.lRx / 1000.0f;
		//is_push[ButtonKind::RightButton] = true;
	}

	return 0.0f;
}
float PadInput::rightStickY()
{
	if (padState.lRy < -unresponsive_range)
	{
		return padState.lRy / 1000.0f;
		//is_push[ButtonKind::UpButton] = true;
	}
	else if (padState.lRy > unresponsive_range)
	{
		return padState.lRy / 1000.0f;
		//is_push[ButtonKind::DownButton] = true;
	}

	return 0.0f;
}

float PadInput::getLeftX()
{
	return padState.lX / 1000.0f;
}
float PadInput::getLeftY()
{
	return padState.lY / 1000.0f;
}
float PadInput::getRightX()
{
	return padState.lRx / 1000.0f;
}
float PadInput::getRightY()
{
	return padState.lRy / 1000.0f;
}

void PadInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	//�p�b�h�f�o�C�X����
	result = dinput->CreateDevice(GUID_Joystick, &devPad, NULL);
	if (devPad != nullptr) {
		//���̓f�[�^�`���̃Z�b�g
		result = devPad->SetDataFormat(&c_dfDIJoystick);
		//�r�����䃌�x���̃Z�b�g
		result = devPad->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}

	// �C���^�[�t�F�[�X�쐬
	result = DirectInput8Create(
		GetModuleHandle(nullptr),	// �C���X�^���X�n���h��
		DIRECTINPUT_VERSION,		// DirectInput�̃o�[�W����
		IID_IDirectInput8,			// �g�p����@�\
		(void**)&p_Interface,	// �쐬���ꂽ�C���^�[�t�F�[�X����p
		NULL						// NULL�Œ�
	);

	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &devPad;

	// GAMEPAD�𒲂ׂ�
	p_Interface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,			// ��������f�o�C�X�̎��
		DeviceFindCallBack,			// �������Ɏ��s����֐�
		&parameter,					// �֐��ɓn���l
		DIEDFL_ATTACHEDONLY			// �������@
	);

	// JOYSTICK�𒲂ׂ�
	p_Interface->EnumDevices(
		DI8DEVTYPE_JOYSTICK,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY
	);

	// �ǂ���������邱�Ƃ��o���Ȃ������玸�s
	if (parameter.FindCount == 0)
	{
		return;
	}

	int count = 0;
	// ����J�n
	while (StartGamePadControl() == false)
	{
		Sleep(100);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	// ���͏��̏�����
	for (int i = 0; i < PadButton::Button_Max; i++)
	{
		p_ButtonState[i] = ButtonState::ButtonStateNone;
	}
}
void PadInput::Update() {
	HRESULT result;

	if (devPad != nullptr) {
		//�O��̃p�b�h�̃{�^��������ۑ�
		prePadState = padState;
		//�p�b�h���̍X�V
		result = devPad->Acquire();
		//�p�b�h�̓��͏����擾����
		result = devPad->GetDeviceState(sizeof(DIJOYSTATE), &padState);

		if (FAILED(result)) {

			if (FAILED(devPad->Acquire())) {
				for (int i = 0; i <Button_Max; i++)
				{
					p_ButtonState[i] = ButtonState::ButtonStateNone();
				}
				devPad->Poll();
			}
			return;
		}
	}

	bool is_push[PadButton::Button_Max] = { false };
	// �X�e�B�b�N����
	//int unresponsive_range = 200;
	if (padState.lX < -unresponsive_range)
	{
		is_push[PadButton::Stick_Left] = true;
	}
	else if (padState.lX > unresponsive_range)
	{
		is_push[PadButton::Stick_Right] = true;
	}

	if (padState.lY < -unresponsive_range)
	{
		is_push[PadButton::Stick_Up] = true;
	}
	else if (padState.lY > unresponsive_range)
	{
		is_push[PadButton::Stick_Down] = true;
	}

}

bool PadInput::PushButton(BYTE buttonNumber) {
	//�w��L�[�������Ă����true��Ԃ�
	if (padState.rgbButtons[buttonNumber] & (0x80)) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}
bool PadInput::TriggerButton(BYTE buttonNumber) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!prePadState.rgbButtons[buttonNumber] && padState.rgbButtons[buttonNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}
bool PadInput::PushCrossKey(LONG crossKeyNumber) {
	if (padState.rgdwPOV[0] != 0xFFFFFFFF) {
		//�w��L�[�������Ă����true��Ԃ�
		if (padState.rgdwPOV[0] == crossKeyNumber) {
			return true;
		}
	}
	//�����łȂ��Ȃ�false��Ԃ�
	return false;
}