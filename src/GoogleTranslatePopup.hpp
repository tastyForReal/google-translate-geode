#pragma once

#include <Geode/Geode.hpp>

class GoogleTranslatePopup : public geode::Popup<const std::string&>
{
protected:
	std::string m_externalLink;
	bool m_ableToClose = false;

    bool setup(const std::string& text) override;

    void onOpenBrowserButtonClick(cocos2d::CCObject* sender);
    void onClose(cocos2d::CCObject* sender) override;

public:
    static GoogleTranslatePopup* create(const std::string& text);
};