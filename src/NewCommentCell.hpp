#pragma once

#include <Geode/modify/CommentCell.hpp>

class NewCommentCell : public geode::Modify<NewCommentCell, CommentCell>
{
public:
	void loadFromComment(GJComment* p0);

	void onTranslateButtonClick(cocos2d::CCObject* sender);
};