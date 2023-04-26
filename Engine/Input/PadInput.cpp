#include "PadInput.h"

PadInput* PadInput::GetIns()
{
	static PadInput instance;
	return &instance;
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