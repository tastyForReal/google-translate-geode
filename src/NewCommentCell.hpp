#pragma once

#include <Geode/modify/CommentCell.hpp>

namespace geode {
namespace prelude {

class NewCommentCell : public Modify<NewCommentCell, CommentCell>
{
public:
	void loadFromComment(GJComment* p0);

	void onTranslateButtonClick(CCObject* sender);
};

} // namespace prelude
} // namespace geode