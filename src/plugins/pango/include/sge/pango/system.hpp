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


#ifndef SGE_PANGO_SYSTEM_HPP_INCLUDED
#define SGE_PANGO_SYSTEM_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <sge/pango/glib_deleter_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-fontmap.h>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class system
:
	public sge::font::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		sge::charconv::system &
	);

	~system();
private:
	sge::font::object_unique_ptr
	create_font(
		sge::font::parameters const &
	);

	sge::charconv::system &charconv_system_;

	typedef fcppt::scoped_ptr<
		PangoFontMap,
		sge::pango::glib_deleter
	> font_map_scoped_ptr;

	font_map_scoped_ptr const font_map_;

	typedef fcppt::scoped_ptr<
		PangoContext,
		sge::pango::glib_deleter
	> context_scoped_ptr;

	context_scoped_ptr const context_;
};

}
}

#endif
