#pragma once

#include <Geode/Geode.hpp>

class GoogleTranslatePopup : public geode::prelude::Popup<const std::string&>
{
protected:
	std::string m_externalLink;
	bool m_ableToClose = false;

    bool setup(const std::string& text) override;

    void onOpenBrowserButtonClick(geode::prelude::CCObject* sender);
    void onClose(geode::prelude::CCObject* sender) override;

public:
    static GoogleTranslatePopup* create(const std::string& text);
};