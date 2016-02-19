/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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

