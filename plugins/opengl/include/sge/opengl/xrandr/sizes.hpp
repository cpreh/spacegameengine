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


#ifndef SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SIZES_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/sizes_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class sizes
{
public:
	explicit
	sizes(
		sge::opengl::xrandr::configuration const &
	);

	typedef
	XRRScreenSize const *
	iterator;

	typedef
	iterator
	const_iterator;

	iterator
	begin() const;

	iterator
	end() const;

	XRRScreenSize const &
	operator[](
		sge::opengl::xrandr::mode_index
	) const;

	sge::opengl::xrandr::mode_index
	size() const;
private:
	int size_;

	XRRScreenSize const *sizes_;
};

}
}
}

#endif
