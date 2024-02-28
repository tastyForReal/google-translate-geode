#include "NewCommentCell.hpp"

#include "helpers.hpp"

void NewCommentCell::loadFromComment(GJComment* comment)
{
	const bool compactMode = m_height == 36.f;

	auto* translateButtonSpr = cocos2d::CCSprite::create("translateButton_small.png"_spr);

	auto* translateButton = CCMenuItemSpriteExtra::create(
		translateButtonSpr, this, static_cast<cocos2d::SEL_MenuHandler>(&NewCommentCell::onTranslateButtonClick));
	translateButtonSpr->setScale(compactMode ? 0.6f : 0.75f);
	translateButton->setID("translate-button"_spr);

	CommentCell::loadFromComment(comment);

	auto* menu = m_mainLayer->getChildByID("main-menu");
	if(menu != nullptr && !m_comment->m_isSpam)
	{
		auto* likeButton = menu->getChildByID("like-button");
		if(likeButton != nullptr)
		{
			translateButton->setPosition(
				{likeButton->getPositionX() - (compactMode ? 20.f : 24.f), likeButton->getPositionY()});
		}

		auto* deleteButton = menu->getChildByID("delete-button");
		if(deleteButton != nullptr)
		{
			translateButton->setPositionX(deleteButton->getPositionX() - (compactMode ? 20.f : 23.f));
		}

		auto* levelIdButton = menu->getChildByID("level-id-button");
		if(levelIdButton != nullptr)
		{
			levelIdButton->setPositionX(translateButton->getPositionX() - (compactMode ? 41.f : 56.f));
		}

		menu->addChild(translateButton);
	}
}

void NewCommentCell::onTranslateButtonClick(CCObject* sender)
{
	createGoogleTranslatePopup(m_comment->m_commentString);
}