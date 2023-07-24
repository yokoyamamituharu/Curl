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
		//半角区切りで文字列を取得
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
	//ウィンドウサイズ(クローズ時)
	const float closeWindowSizeY = 0.0f;
	//ウィンドウサイズ(オープン時)
	const float openWindowSizeY = 160.0f;

	//メッセージウィンドウ座標
	float windowPosX = textWindow_->GetPosition().x;
	float windowPosY = textWindow_->GetPosition().y;

	//メッセージウィンドウ開閉処理
	//メッセージウィンドウ閉鎖処理
	if (!isOpen_) {
		windowOpenTimer_ = 0;
		windowCloseTimer_++;
		if (windowCloseTimer_ >= windowCloseTime) {
			windowCloseTimer_ = windowCloseTime;
		}
		//イーズインアウトでメッセージウィンドウを閉じる
		textWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, textWindowSize_.y);
	}
	//メッセージウィンドウ開放処理
	else if (isOpen_) {
		windowCloseTimer_ = 0;
		windowOpenTimer_++;
		if (windowOpenTimer_ >= windowOpenTime) {
			windowOpenTimer_ = windowOpenTime;
		}
		//イーズインアウトでメッセージウィンドウを開く
		textWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, textWindowSize_.y);
	}

	//メッセージウィンドウサイズを変更
	textWindow_->SetSize(textWindowSize_);

	//テキスト描画範囲
	D2D1_RECT_F textDrawPos = {
		windowPosX, windowPosY, windowPosX + 400.0f, windowPosY + 200.0f
	};

	//テキストを1文字ずつ指定時間ごとに追加する
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
		//読み込んだテキスト描画が完了したら
		if (textCount_ >= message_.size()) {
			isTextDrawComplete_ = true;
		}
	}
	//現在追加されている文字を全て描画する
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
