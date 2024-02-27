#include "NewCommentCell.hpp"

#include "helpers.hpp"

namespace geode {
namespace prelude {

void NewCommentCell::loadFromComment(GJComment* p0)
{
	auto* translateButtonSpr = CCSprite::create("translateButton.png"_spr);
	translateButtonSpr->setScale(0.5f);

	auto* translateButton = CCMenuItemSpriteExtra::create(
		translateButtonSpr, this, static_cast<cocos2d::SEL_MenuHandler>(&NewCommentCell::onTranslateButtonClick));
	translateButton->setID("translate-button");
	translateButton->setPosition({315.f, 35.f});

	auto* container = CCMenu::create();
	container->setPosition({0, 0});
	container->addChild(translateButton);
	addChild(container);

	CommentCell::loadFromComment(p0);
}

void NewCommentCell::onTranslateButtonClick(CCObject* sender)
{
	createGoogleTranslatePopup(m_comment->m_commentString);
}

} // namespace prelude
} // namespace geode