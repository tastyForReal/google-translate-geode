#pragma once

#include <Geode/Geode.hpp>

namespace geode {
namespace prelude {

class GoogleTranslatePopup : public Popup<const std::string&>
{
protected:
	std::string m_externalLink;
	bool m_ableToClose = false;

    bool setup(const std::string& text) override;

    void onOpenBrowserButtonClick(CCObject* sender);
    void onClose(CCObject* sender) override;

public:
    static GoogleTranslatePopup* create(const std::string& text);
};

} // namespace prelude
} // namespace geode