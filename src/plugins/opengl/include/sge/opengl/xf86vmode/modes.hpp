/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_XF86VMODE_MODES_HPP_INCLUDED
#define SGE_OPENGL_XF86VMODE_MODES_HPP_INCLUDED

#include <sge/opengl/xf86vmode/modes_fwd.hpp>
#include <awl/backends/x11/deleter.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/screen.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xf86vmode
{

class modes
{
	FCPPT_NONCOPYABLE(
		modes
	);
public:
	typedef std::size_t size_type;

	modes(
		awl::backends::x11::display &,
		awl::backends::x11::screen
	);

	~modes();

	XF86VidModeModeInfo const &
	operator[](
		size_type index
	) const;

	size_type
	size() const;

	awl::backends::x11::display &
	display() const;

	awl::backends::x11::screen const
	screen() const;
private:
	awl::backends::x11::display &display_;

	awl::backends::x11::screen const screen_;

	typedef fcppt::shared_ptr<
		XF86VidModeModeInfo *,
		awl::backends::x11::deleter
	> vidmode_ptr;

	vidmode_ptr modes_;

	size_type size_;
};

}
}
}

#endif
