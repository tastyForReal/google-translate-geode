#pragma once

#include <Geode/modify/InfoLayer.hpp>

namespace geode {
namespace prelude {

class NewInfoLayer : public Modify<NewInfoLayer, InfoLayer>
{
public:
	bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2);

    void onTranslateButtonClick(CCObject* sender);
    void onClose(CCObject* sender);
};

} // namespace prelude
} // namespace geode