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


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/sizes.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::sizes::sizes(
	sge::opengl::xrandr::configuration const &_config
)
:
	size_{
		0
	},
	sizes_{
		::XRRConfigSizes(
			_config.get(),
			&size_
		)
	}
{
}

sge::opengl::xrandr::sizes::iterator
sge::opengl::xrandr::sizes::begin() const
{
	return
		sizes_;
}

sge::opengl::xrandr::sizes::iterator
sge::opengl::xrandr::sizes::end() const
{
	return
		sizes_
		+
		size_;
}

XRRScreenSize const &
sge::opengl::xrandr::sizes::operator[](
	sge::opengl::xrandr::mode_index const _index
) const
{
	return
		*(
			this->begin()
			+
			_index.get()
		);
}

sge::opengl::xrandr::mode_index
sge::opengl::xrandr::sizes::size() const
{
	return
		sge::opengl::xrandr::mode_index{
			size_
		};
}
