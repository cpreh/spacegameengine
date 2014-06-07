/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/action/activate_pan.hpp>
#include <sge/camera/ortho_freelook/action/zoom_in.hpp>
#include <sge/camera/ortho_freelook/action/zoom_out.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
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
	SGE_CAMERA_SYMBOL
	explicit
	mapping(
		action::zoom_in const &,
		action::zoom_out const &,
		action::activate_pan const &);

	SGE_CAMERA_SYMBOL
	action::zoom_in const &
	zoom_in() const;

	SGE_CAMERA_SYMBOL
	action::zoom_out const &
	zoom_out() const;

	SGE_CAMERA_SYMBOL
	action::activate_pan const &
	activate_pan() const;
private:
	action::zoom_in zoom_in_;
	action::zoom_out zoom_out_;
	action::activate_pan activate_pan_;
};
}
}
}
}

#endif

