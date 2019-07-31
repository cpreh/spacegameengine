//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/first_person/action/backward.hpp>
#include <sge/camera/first_person/action/down.hpp>
#include <sge/camera/first_person/action/forward.hpp>
#include <sge/camera/first_person/action/left.hpp>
#include <sge/camera/first_person/action/right.hpp>
#include <sge/camera/first_person/action/up.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace first_person
{
namespace action
{
/**
\brief A mapping from camera "actions" to key codes
\ingroup sgecamera
*/
class mapping
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	mapping(
		action::left const &,
		action::right const &,
		action::up const &,
		action::down const &,
		action::forward const &,
		action::backward const &);

	SGE_CAMERA_DETAIL_SYMBOL
	action::left const &
	left() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::right const &
	right() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::up const &
	up() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::down const &
	down() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::forward const &
	forward() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::backward const &
	backward() const;
private:
	action::left left_;
	action::right right_;
	action::up up_;
	action::down down_;
	action::forward forward_;
	action::backward backward_;
};
}
}
}
}

#endif

