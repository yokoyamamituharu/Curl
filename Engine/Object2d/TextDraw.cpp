#include "TextDraw.h"

const std::wstring TextDraw::defaultFont = L"���C���I";

void TextDraw::Initialize() {
	DirectXSetting::GetIns()->registerSolidColorBrush("white", D2D1::ColorF::White);
	DirectXSetting::GetIns()->registerSolidColorBrush("orange", D2D1::ColorF::Orange);
	DirectXSetting::GetIns()->registerTextFormat("meiryo", defaultFont, defaultFontSize);
}

void TextDraw::Draw(const std::string& textFormatKey, const std::string& solidColorBrushKey, const std::wstring& text, const D2D1_RECT_F& rect) {
	const auto textFormat = DirectXSetting::GetIns()->GetTextFormats().at(textFormatKey);
	const auto solidColorBrush = DirectXSetting::GetIns()->GetColorBrushes().at(solidColorBrushKey);

	DirectXSetting::GetIns()->GetD2DDeviceContext()->DrawTextW(text.c_str(),
		static_cast<UINT32>(text.length()), textFormat.Get(), &rect, solidColorBrush.Get());

}