#include "NewInfoLayer.hpp"

#include "helpers.hpp"

bool NewInfoLayer::init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2)
{
	if(!InfoLayer::init(p0, p1, p2))
	{
		return false;
	}

	p0->retain();
	m_level = p0;

	auto* translateButtonSpr = cocos2d::CCSprite::create("translateButton.png"_spr);
	translateButtonSpr->setScale(2.f / 3.f);

	auto* translateButton = CCMenuItemSpriteExtra::create(
		translateButtonSpr, this, static_cast<cocos2d::SEL_MenuHandler>(&NewInfoLayer::onTranslateButtonClick));
	translateButton->setID("translate-button");
	translateButton->setPosition({194.f, 52.f});

	m_buttonMenu->addChild(translateButton);

	return true;
}

void NewInfoLayer::onTranslateButtonClick(CCObject* sender)
{
	createGoogleTranslatePopup(m_level->getUnpackedLevelDescription());
}

void NewInfoLayer::onClose(CCObject* sender)
{
	if(m_level != nullptr)
	{
		m_level->release();
	}
	InfoLayer::onClose(sender);
}