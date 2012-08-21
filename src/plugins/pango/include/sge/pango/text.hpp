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


#ifndef SGE_PANGO_TEXT_HPP_INCLUDED
#define SGE_PANGO_TEXT_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/pango/no_multi_line.hpp>
#include <sge/pango/pango_layout_scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class text
:
	public sge::font::text
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	text(
		sge::charconv::system &,
		PangoLayout &,
		sge::font::string const &,
		sge::font::text_parameters const &
	);

	~text();
private:
	void
	render(
		sge::font::view const &
	);

	sge::font::rect const
	rect();

	sge::pango::pango_layout_scoped_ptr const layout_;

	sge::pango::no_multi_line const no_multi_line_;

	sge::font::rect const ink_rect_;
};

}
}

#endif
