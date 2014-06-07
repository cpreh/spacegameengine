/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_FONT_PARAMETERS_HPP_INCLUDED
#define SGE_FONT_PARAMETERS_HPP_INCLUDED

#include <sge/font/dpi_fwd.hpp>
#include <sge/font/optional_dpi.hpp>
#include <sge/font/optional_family.hpp>
#include <sge/font/optional_ttf_size.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/symbol.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/optional_unit.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace font
{

class parameters
{
public:
	SGE_FONT_SYMBOL
	parameters();

	SGE_FONT_SYMBOL
	sge::font::parameters &
	dpi(
		sge::font::dpi const &
	);

	SGE_FONT_SYMBOL
	sge::font::parameters &
	ttf_size(
		sge::font::ttf_size
	);

	SGE_FONT_SYMBOL
	sge::font::parameters &
	family(
		fcppt::string const &
	);

	SGE_FONT_SYMBOL
	sge::font::parameters &
	weight(
		sge::font::weight::unit
	);

	SGE_FONT_SYMBOL
	sge::font::parameters &
	italic();

	SGE_FONT_SYMBOL
	sge::font::optional_dpi const &
	dpi() const;

	SGE_FONT_SYMBOL
	sge::font::optional_ttf_size const &
	ttf_size() const;

	SGE_FONT_SYMBOL
	sge::font::optional_family const &
	family() const;

	SGE_FONT_SYMBOL
	sge::font::weight::optional_unit const &
	weight() const;

	SGE_FONT_SYMBOL
	bool
	italic() const;
private:
	sge::font::optional_dpi dpi_;

	sge::font::optional_ttf_size ttf_size_;

	sge::font::optional_family family_;

	sge::font::weight::optional_unit weight_;

	bool italic_;
};

}
}

#endif
