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


#ifndef SGE_PANGO_FONT_DESCRIPTION_HPP_INCLUDED
#define SGE_PANGO_FONT_DESCRIPTION_HPP_INCLUDED

#include <sge/font/ttf_size.hpp>
#include <sge/font/weight.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-font.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class font_description
{
	FCPPT_NONCOPYABLE(
		font_description
	);
public:
	font_description();

	~font_description();

	void
	ttf_size(
		sge::font::ttf_size
	);

	void
	family(
		fcppt::string const &
	);

	void
	weight(
		sge::font::weight
	);

	void
	italic();

	PangoFontDescription *
	get();
private:
	PangoFontDescription *const impl_;
};

}
}

#endif
