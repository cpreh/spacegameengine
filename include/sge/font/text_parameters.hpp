/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_TEXT_PARAMETERS_HPP_INCLUDED
#define SGE_FONT_TEXT_PARAMETERS_HPP_INCLUDED

#include <sge/font/align_h.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/optional_unit.hpp>
#include <sge/font/symbol.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/unit.hpp>


namespace sge
{
namespace font
{

class text_parameters
{
public:
	// TODO:
	// - Add gravity for Japanese text
	SGE_FONT_SYMBOL
	explicit
	text_parameters(
		sge::font::align_h
	);

	SGE_FONT_SYMBOL
	sge::font::text_parameters &
	flags(
		sge::font::flags_field const &
	);

	SGE_FONT_SYMBOL
	sge::font::text_parameters &
	max_width(
		sge::font::unit
	);

	SGE_FONT_SYMBOL
	sge::font::align_h
	align_h() const;

	SGE_FONT_SYMBOL
	sge::font::flags_field const &
	flags() const;

	SGE_FONT_SYMBOL
	sge::font::optional_unit const &
	max_width() const;
private:
	sge::font::align_h align_h_;

	sge::font::flags_field flags_;

	sge::font::optional_unit max_width_;
};

}
}

#endif
