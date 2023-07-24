#include "MessageWindow.h"
#include "ExternalFileLoader.h"
#include "Easing.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "Collision2d.h"

MessageWindow* MessageWindow::Create()
{
	MessageWindow* ins = new MessageWindow();
	return ins;
}

std::unique_ptr<MessageWindow> MessageWindow::UniquePtrCreate()
{
	std::unique_ptr<MessageWindow> ins = std::make_unique<MessageWindow>();
	return ins;
}

void MessageWindow::Initialize()
{
	textWindow_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::messageWindow, { 700.0f, 100.0f });
	textWindow_->SetAlpha(1.0f);
	textWindow_->SetUi(true);
	textWindowSize_ = textWindow_->GetSize();
	textWindowSize_.y = 0;

	textAddTimer_ = 0;
	textSpeed_ = 1;
	textCount_ = 0;
	isTextDrawComplete_ = false;
}

void MessageWindow::Update(Vector2 playerPos, float playerRadius)
{
	std::string line;
	std::string messageData;
	std::wstring messageDataW;
	Vector2 movePos;
	float radius;

	if (isCommand_) {
		CommandCheck();

		return;
	}
	if (isPointMove_) {
		PointMoveCheck(playerPos, playerRadius);

		return;
	}

	if (isMessageUpdateWait_) {
		if (isTextDrawComplete_) {
			messageWaitTimer_--;
		}
		if (messageWaitTimer_ <= 0) {
			isMessageUpdateWait_ = false;
			textCount_ = 0;
			message_.clear();
			drawMessage_.clear();
		}
		return;
	}

	while (getline(textData_, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//���p��؂�ŕ�������擾
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isOpen_ = true;
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
			message_ = messageDataW;
		}
		if (word == "IF") {
			line_stream >> messageData;
			messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
			if (messageDataW == L"PUSH") {
				line_stream >> messageData;
				messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
				command_ = messageDataW;
				line_stream >> messageWaitTimer_;
				isMessageUpdateWait_ = true;
				isCommand_ = true;
			}
			if (messageDataW == L"MOVE") {
				line_stream >> movePos.x;
				line_stream >> movePos.y;
				line_stream >> radius;
				movePoint_ = movePos;
				movePointRadius_ = radius;
				isMessageUpdateWait_ = true;
				isPointMove_ = true;
			}
		}
		if (word == "SPEED") {
			line_stream >> textSpeed_;
		}
		if (word == "WAIT") {
			isMessageUpdateWait_ = true;
			line_stream >> messageWaitTimer_;
			break;
		}
		if (word == "CLOSE") {
			isOpen_ = false;
		}
		if (word == "LOAD_END") {
			isLoadEnd_ = true;
		}
	}
}

void MessageWindow::SpriteDraw()
{
	textWindow_->Draw();
}

void MessageWindow::TextMessageDraw()
{
	//�E�B���h�E�T�C�Y(�N���[�Y��)
	const float closeWindowSizeY = 0.0f;
	//�E�B���h�E�T�C�Y(�I�[�v����)
	const float openWindowSizeY = 160.0f;

	//���b�Z�[�W�E�B���h�E���W
	float windowPosX = textWindow_->GetPosition().x;
	float windowPosY = textWindow_->GetPosition().y;

	//���b�Z�[�W�E�B���h�E�J����
	//���b�Z�[�W�E�B���h�E������
	if (!isOpen_) {
		windowOpenTimer_ = 0;
		windowCloseTimer_++;
		if (windowCloseTimer_ >= windowCloseTime) {
			windowCloseTimer_ = windowCloseTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E�����
		textWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, textWindowSize_.y);
	}
	//���b�Z�[�W�E�B���h�E�J������
	else if (isOpen_) {
		windowCloseTimer_ = 0;
		windowOpenTimer_++;
		if (windowOpenTimer_ >= windowOpenTime) {
			windowOpenTimer_ = windowOpenTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E���J��
		textWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, textWindowSize_.y);
	}

	//���b�Z�[�W�E�B���h�E�T�C�Y��ύX
	textWindow_->SetSize(textWindowSize_);

	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawPos = {
		windowPosX, windowPosY, windowPosX + 400.0f, windowPosY + 200.0f
	};

	//�e�L�X�g��1�������w�莞�Ԃ��Ƃɒǉ�����
	textAddTimer_++;
	isTextDrawComplete_ = false;
	if (textAddTimer_ >= textSpeed_) {
		textAddTimer_ = 0;
		if (textCount_ < message_.size()) {
			if (message_.substr(textCount_, 1) != L"/") {
				drawMessage_ += message_.substr(textCount_, 1);
			}
			else {
				drawMessage_ += L"\n";
			}
			textCount_++;
		}
		//�ǂݍ��񂾃e�L�X�g�`�悪����������
		if (textCount_ >= message_.size()) {
			isTextDrawComplete_ = true;
		}
	}
	//���ݒǉ�����Ă��镶����S�ĕ`�悷��
	textDraw_->Draw("meiryo_16", "white", drawMessage_, textDrawPos);
}

void MessageWindow::CommandCheck()
{
	if (command_ == L"W") {
		if (KeyInput::GetIns()->PushKey(DIK_W)) {
			isCommand_ = false;
		}
	}
	if (command_ == L"LCLICK") {
		if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
			isCommand_ = false;
		}
	}
	if (command_ == L"E") {
		if (KeyInput::GetIns()->PushKey(DIK_E)) {
			isCommand_ = false;
		}
	}
	if (command_ == L"Q") {
		if (KeyInput::GetIns()->PushKey(DIK_Q)) {
			isCommand_ = false;
		}
	}
}

void MessageWindow::PointMoveCheck(Vector2 playerPos, float playerRadius)
{
	if (Collision2d::GetIns()->CircleAndCircle(playerPos, movePoint_, playerRadius, movePointRadius_)) {
		isPointMove_ = false;
	}
}

void MessageWindow::LoadTextMessageData(const std::string& fileName)
{
	textData_ = ExternalFileLoader::GetIns()->ExternalFileOpen(fileName);
	textAddTimer_ = 0;
	textSpeed_ = 1;
	textCount_ = 0;
	isTextDrawComplete_ = false;
	isLoadEnd_ = false;
}
