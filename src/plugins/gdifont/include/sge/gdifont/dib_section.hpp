/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/gdifont/delete_object_deleter_fwd.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <fcppt/config/external_end.hpp>


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

	sge::image::const_raw_pointer
	data() const;

	sge::image::color::format::type
	format() const;

	HBITMAP
	handle();
private:
	VOID *data_;

	typedef fcppt::scoped_ptr<
		boost::remove_pointer<
			HBITMAP
		>::type,
		sge::gdifont::delete_object_deleter
	> hbitmap_scoped_ptr;

	hbitmap_scoped_ptr const hbitmap_;
};

}
}

#endif
