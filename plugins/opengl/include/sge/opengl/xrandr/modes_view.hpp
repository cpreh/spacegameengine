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


#ifndef SGE_OPENGL_XRANDR_MODES_VIEW_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_MODES_VIEW_HPP_INCLUDED

#include <sge/opengl/xrandr/screen_resources_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class modes_view
{
public:
	explicit
	modes_view(
		sge::opengl::xrandr::screen_resources const &
	);

	typedef
	XRRModeInfo const *
	const_iterator;

	const_iterator
	begin() const;

	const_iterator
	end() const;
private:
	fcppt::reference<
		sge::opengl::xrandr::screen_resources const
	> resources_;
};

}
}
}

#endif
