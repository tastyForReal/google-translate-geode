#pragma once

#include "GoogleTranslatePopup.hpp"

#include <algorithm>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

static void createGoogleTranslatePopup(const std::string& text)
{
	auto* popup = geode::prelude::GoogleTranslatePopup::create(text);
	popup->setZOrder(std::numeric_limits<int>::max());

	auto* scene = geode::prelude::CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(popup);
}

static bool isSafeChar(char c)
{
	return (c == '+' || c == '!' || c == '*' || c == '(' || c == ')' || c == '-' || c == '.' ||
			(c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

static std::string urlEncode(const std::string& str)
{
	std::stringstream ss;

	for(char c : str)
	{
		if(c == ' ')
		{
			ss << '+';
		}
		else if(isSafeChar(c))
		{
			ss << c;
		}
		else
		{
			ss << '%' << std::hex << (static_cast<unsigned int>(c) & 0xFF);
		}
	}

	return ss.str();
}

class LanguageHelper
{
public:
	static constexpr std::pair<const char*, const char*> languages[] = {{"af", "Afrikaans"}, {"ak", "Twi"},
		{"am", "Amharic"}, {"ar", "Arabic"}, {"as", "Assamese"}, {"auto", "Detect language"}, {"ay", "Aymara"},
		{"az", "Azerbaijani"}, {"be", "Belarusian"}, {"bg", "Bulgarian"}, {"bho", "Bhojpuri"}, {"bm", "Bambara"},
		{"bn", "Bengali"}, {"bs", "Bosnian"}, {"ca", "Catalan"}, {"ceb", "Cebuano"}, {"ckb", "Kurdish (Sorani)"},
		{"co", "Corsican"}, {"cs", "Czech"}, {"cy", "Welsh"}, {"da", "Danish"}, {"de", "German"}, {"doi", "Dogri"},
		{"dv", "Dhivehi"}, {"ee", "Ewe"}, {"el", "Greek"}, {"en", "English"}, {"eo", "Esperanto"}, {"es", "Spanish"},
		{"et", "Estonian"}, {"eu", "Basque"}, {"fa", "Persian"}, {"fi", "Finnish"}, {"fr", "French"}, {"fy", "Frisian"},
		{"ga", "Irish"}, {"gd", "Scots Gaelic"}, {"gl", "Galician"}, {"gn", "Guarani"}, {"gom", "Konkani"},
		{"gu", "Gujarati"}, {"ha", "Hausa"}, {"haw", "Hawaiian"}, {"hi", "Hindi"}, {"hmn", "Hmong"}, {"hr", "Croatian"},
		{"ht", "Haitian Creole"}, {"hu", "Hungarian"}, {"hy", "Armenian"}, {"id", "Indonesian"}, {"ig", "Igbo"},
		{"ilo", "Ilocano"}, {"is", "Icelandic"}, {"it", "Italian"}, {"iw", "Hebrew"}, {"ja", "Japanese"},
		{"jw", "Javanese"}, {"ka", "Georgian"}, {"kk", "Kazakh"}, {"km", "Khmer"}, {"kn", "Kannada"}, {"ko", "Korean"},
		{"kri", "Krio"}, {"ku", "Kurdish (Kurmanji)"}, {"ky", "Kyrgyz"}, {"la", "Latin"}, {"lb", "Luxembourgish"},
		{"lg", "Luganda"}, {"ln", "Lingala"}, {"lo", "Lao"}, {"lt", "Lithuanian"}, {"lus", "Mizo"}, {"lv", "Latvian"},
		{"mai", "Maithili"}, {"mg", "Malagasy"}, {"mi", "Maori"}, {"mk", "Macedonian"}, {"ml", "Malayalam"},
		{"mn", "Mongolian"}, {"mni-Mtei", "Meiteilon (Manipuri)"}, {"mr", "Marathi"}, {"ms", "Malay"},
		{"mt", "Maltese"}, {"my", "Myanmar (Burmese)"}, {"ne", "Nepali"}, {"nl", "Dutch"}, {"no", "Norwegian"},
		{"nso", "Sepedi"}, {"ny", "Chichewa"}, {"om", "Oromo"}, {"or", "Odia (Oriya)"}, {"pa", "Punjabi"},
		{"pl", "Polish"}, {"ps", "Pashto"}, {"pt", "Portuguese"}, {"qu", "Quechua"}, {"ro", "Romanian"},
		{"ru", "Russian"}, {"rw", "Kinyarwanda"}, {"sa", "Sanskrit"}, {"sd", "Sindhi"}, {"si", "Sinhala"},
		{"sk", "Slovak"}, {"sl", "Slovenian"}, {"sm", "Samoan"}, {"sn", "Shona"}, {"so", "Somali"}, {"sq", "Albanian"},
		{"sr", "Serbian"}, {"st", "Sesotho"}, {"su", "Sundanese"}, {"sv", "Swedish"}, {"sw", "Swahili"},
		{"ta", "Tamil"}, {"te", "Telugu"}, {"tg", "Tajik"}, {"th", "Thai"}, {"ti", "Tigrinya"}, {"tk", "Turkmen"},
		{"tl", "Filipino"}, {"tr", "Turkish"}, {"ts", "Tsonga"}, {"tt", "Tatar"}, {"ug", "Uyghur"}, {"uk", "Ukrainian"},
		{"ur", "Urdu"}, {"uz", "Uzbek"}, {"vi", "Vietnamese"}, {"xh", "Xhosa"}, {"yi", "Yiddish"}, {"yo", "Yoruba"},
		{"zh-CN", "Chinese (Simplified)"}, {"zh-TW", "Chinese (Traditional)"}, {"zu", "Zulu"}};

	static std::optional<std::string> getLanguage(const std::string& code, bool fullName = false)
	{
		auto it = std::find_if(
			std::begin(languages), std::end(languages), [&code](const auto& pair) { return pair.first == code; });

		if(it != std::end(languages))
		{
			return fullName ? it->second : it->first;
		}

		return std::nullopt;
	}
};