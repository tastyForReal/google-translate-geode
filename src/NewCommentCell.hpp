#pragma once

#include <Geode/modify/CommentCell.hpp>

class NewCommentCell : public geode::Modify<NewCommentCell, CommentCell>
{
public:
	void loadFromComment(GJComment* comment);

	void onTranslateButtonClick(cocos2d::CCObject* sender);
};