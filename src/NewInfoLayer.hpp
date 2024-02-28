#pragma once

#include <Geode/modify/InfoLayer.hpp>

class NewInfoLayer : public geode::Modify<NewInfoLayer, InfoLayer>
{
public:
	bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2);

	void onTranslateButtonClick(cocos2d::CCObject* sender);
	void onClose(cocos2d::CCObject* sender);
};