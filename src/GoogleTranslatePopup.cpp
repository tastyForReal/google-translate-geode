#include "GoogleTranslatePopup.hpp"

#include "helpers.hpp"

#include <Geode/ui/TextArea.hpp>
#include <Geode/utils/web.hpp>

bool GoogleTranslatePopup::setup(const std::string& text)
{
	setTitle("Google Translate");

	const auto size = m_buttonMenu->getContentSize();

	auto* inputLanguage = cocos2d::CCLabelBMFont::create("Detect Language", "goldFont.fnt");
	auto* outputLanguage = cocos2d::CCLabelBMFont::create("English", "goldFont.fnt");
	auto* inputTextArea = geode::SimpleTextArea::create(text, "chatFont.fnt", 1, 248);
	auto* outputTextArea = geode::SimpleTextArea::create("Getting translation...", "chatFont.fnt", 1, 248);

	auto* openInTranslateBtnSpr =
		ButtonSprite::create("Open in Google Translate", "bigFont.fnt", "GJ_button_05.png", 0.5f);

	auto* openInTranslateButton = CCMenuItemSpriteExtra::create(openInTranslateBtnSpr, this,
		static_cast<cocos2d::SEL_MenuHandler>(&GoogleTranslatePopup::onOpenBrowserButtonClick));

	inputLanguage->setAnchorPoint({0.f, 0.5f});
	inputLanguage->setPosition({16.f, 160.f});
	inputLanguage->setScale(1.f / 3.f);
	inputLanguage->setID("input-language"_spr);

	inputTextArea->setAnchorPoint({0.f, 0.5f});
	inputTextArea->setPosition({16.f, 133.f});
	inputTextArea->setWrappingMode(geode::WrappingMode::WORD_WRAP);
	inputTextArea->setMaxLines(3);
	inputTextArea->setScale(2.f / 3.f);
	inputTextArea->setID("input-text-area"_spr);

	outputLanguage->setAnchorPoint({0.f, 0.5f});
	outputLanguage->setPosition({16.f, 95.5f});
	outputLanguage->setScale(1.f / 3.f);
	outputLanguage->setID("output-language"_spr);

	outputTextArea->setAnchorPoint({0.f, 0.5f});
	outputTextArea->setPosition({16.f, 68.f});
	outputTextArea->setWrappingMode(geode::WrappingMode::WORD_WRAP);
	outputTextArea->setMaxLines(3);
	outputTextArea->setScale(2.f / 3.f);
	outputTextArea->setID("output-text-area"_spr);

	openInTranslateBtnSpr->setScale(0.5f);
	openInTranslateButton->setPosition({size.width / 2.f, 24.f});
	openInTranslateButton->setEnabled(false);
	openInTranslateButton->setID("open-in-translate-button"_spr);

	m_buttonMenu->addChild(inputLanguage);
	m_buttonMenu->addChild(inputTextArea);
	m_buttonMenu->addChild(outputLanguage);
	m_buttonMenu->addChild(outputTextArea);
	m_buttonMenu->addChild(openInTranslateButton);

	const std::string url = fmt::format(
		"https://translate.googleapis.com/translate_a/"
		"single?client=gtx&sl=auto&tl=en&hl=en-US&dt=t&dt=bd&dj=1&q={}",
		urlEncode(text));

	geode::utils::web::AsyncWebRequest()
		.contentType("application/json; charset=utf-8")
		.timeout(std::chrono::seconds(10))
		.get(url)
		.json()
		.then(
			[=](const geode::utils::web::SentAsyncWebRequest& req, const matjson::Value& json)
			{
				if(!req.finished())
				{
					return;
				}

				const std::string output = json["sentences"][0]["trans"].as_string();
				const std::string src = json["src"].as_string();
				const std::string detectedLang =
					fmt::format("{} - Detected", LanguageHelper::getLanguage(src, true).value());

				inputLanguage->setString(detectedLang.c_str());
				outputTextArea->setText(output);
				openInTranslateButton->setEnabled(true);

				m_externalLink = fmt::format("https://translate.google.com/?source=gtx_m#{}/en/{}",
					LanguageHelper::getLanguage(src).value(), urlEncode(text));

				m_ableToClose = true;
			})
		.expect(
			[=](const std::string& message, int code)
			{
				auto* notification =
					geode::Notification::create(fmt::format("{} ({})", message, code), geode::NotificationIcon::Error);

				notification->setTime(2.f);
				notification->show();

				outputTextArea->setText("Failed to translate.");

				m_ableToClose = true;
			});

	return true;
}

void GoogleTranslatePopup::onOpenBrowserButtonClick(cocos2d::CCObject* sender)
{
	geode::utils::web::openLinkInBrowser(m_externalLink);
}

void GoogleTranslatePopup::onClose(cocos2d::CCObject* sender)
{
	// The popup should not be closed during translation.
	// Without this, a game may crash if closed before translation is complete.
	if(m_ableToClose)
	{
		geode::Popup<const std::string&>::onClose(sender);
	}
}

GoogleTranslatePopup* GoogleTranslatePopup::create(const std::string& text)
{
	auto* ret = new GoogleTranslatePopup();

	if(ret != nullptr && ret->initAnchored(280, 210, text))
	{
		ret->autorelease();
		return ret;
	}

	if(ret != nullptr)
	{
		delete ret;
		ret = nullptr;
	}

	return nullptr;
}