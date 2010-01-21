#include "../group.hpp"
#include "../shapes/base.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/null.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("group")));
}


sge::bullet::group::group(
	group_id const _category)
:
	category_(
		_category),
	collides_(
		fcppt::math::null<group_id>())
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Created a new group with category ")
			<< category_);
}

void 
sge::bullet::group::add(
	collision::shapes::base_ptr const s)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("A shape of type ")
			<< typeid(*s).name()
			<< FCPPT_TEXT(" was added to group with category: ")
			<< category_);
	dynamic_cast<shapes::base &>(*s).add_to_group(
		*this);
}

void 
sge::bullet::group::collides_with(
	group &other)
{
	collides_ |= other.category_;
}

sge::bullet::group_id 
sge::bullet::group::category() const
{
	return 
		category_;
}

sge::bullet::group_id 
sge::bullet::group::collides() const
{
	return 
		collides_;
}
