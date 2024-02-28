#pragma once

#include <Geode/modify/InfoLayer.hpp>

class NewInfoLayer : public geode::Modify<NewInfoLayer, InfoLayer>
{
public:
	bool init(GJGameLevel* gameLevel, GJUserScore* userScore, GJLevelList* levelList);

	void onTranslateButtonClick(cocos2d::CCObject* sender);
	void onClose(cocos2d::CCObject* sender);
};