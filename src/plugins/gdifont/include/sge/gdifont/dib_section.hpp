/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_GDIFONT_DIB_SECTION_HPP_INCLUDED
#define SGE_GDIFONT_DIB_SECTION_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/hbitmap_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gdifont
{

class dib_section
{
	FCPPT_NONCOPYABLE(
		dib_section
	);
public:
	dib_section(
		sge::gdifont::device_context const &,
		sge::image2d::dim const &
	);

	~dib_section();

	sge::image2d::view::object const
	view();

	sge::image2d::view::const_object const
	const_view() const;

	HBITMAP
	handle();
private:
	VOID *data_;

	sge::gdifont::hbitmap_unique_ptr const hbitmap_;

	BITMAP const bitmap_;
};

}
}

#endif
