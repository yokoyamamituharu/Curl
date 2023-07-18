#pragma once
#include "Sprite.h"
#include "ImageManager.h"
#include "TextDraw.h"
#include <sstream>

class MessageWindow
{
public: //静的メンバ関数
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static MessageWindow* Create();
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス生成</returns>
	static std::unique_ptr<MessageWindow> UniquePtrCreate();

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::string& fileName);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// スプライト描画処理
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// テキスト描画
	/// </summary>
	void TextMessageDraw();
	/// <summary>
	/// コマンド入力チェック」
	/// </summary>
	void CommandCheck();

private: //静的メンバ変数
	//ウィンドウ開放時間
	static const int32_t windowOpenTime = 120;
	//ウィンドウ閉鎖時間
	static const int32_t windowCloseTime = 120;

private: //メンバ変数
	//テキスト描画クラス
	std::unique_ptr<TextDraw> textDraw_;
	//テキストウィンドウスプライト
	std::unique_ptr<Sprite> textWindow_;
	//テキストウィンドウサイズ
	Vector2 textWindowSize_;
	//メッセージデータ更新待機フラグ
	bool isMessageUpdateWait_;
	//メッセージデータ待機タイマー
	int32_t messageWaitTimer_;
	//メッセージデータ描画完了フラグ
	bool isTextDrawComplete_;
	//メッセージデータ格納用文字列
	std::stringstream textData_;
	//メッセージ出力用文字列
	std::wstring drawMessage_;
	//メッセージ格納用文字列
	std::wstring message_;
	//プッシュコマンド格納用文字列
	std::wstring command_;
	//ウィンドウ開放タイマー
	int32_t windowOpenTimer_;
	//ウィンドウ閉鎖タイマー
	int32_t windowCloseTimer_;
	//テキストスピード
	int32_t textSpeed_;
	//テキスト数
	int32_t textCount_;
	//テキスト追加時間
	int32_t textAddTimer_;
	//ウィンドウ開閉フラグ
	bool isOpen_;
	//コマンド入力待機フラグ
	bool isCommand_;
};
