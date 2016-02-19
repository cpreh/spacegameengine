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


#include <sge/font/dpi.hpp>
#include <sge/font/optional_dpi.hpp>
#include <sge/font/optional_family.hpp>
#include <sge/font/optional_ttf_size.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/optional_unit.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/string.hpp>


sge::font::parameters::parameters()
:
	dpi_(),
	ttf_size_(),
	family_(),
	weight_(),
	italic_(
		false
	)
{
}

sge::font::parameters &
sge::font::parameters::dpi(
	sge::font::dpi const &_dpi
)
{
	dpi_ =
		sge::font::optional_dpi(
			_dpi
		);

	return
		*this;
}

sge::font::parameters &
sge::font::parameters::ttf_size(
	sge::font::ttf_size const _ttf_size
)
{
	ttf_size_ =
		sge::font::optional_ttf_size(
			_ttf_size
		);

	return
		*this;
}

sge::font::parameters &
sge::font::parameters::family(
	fcppt::string const &_family
)
{
	family_ =
		sge::font::optional_family(
			_family
		);

	return
		*this;
}

sge::font::parameters &
sge::font::parameters::weight(
	sge::font::weight::unit const _weight
)
{
	weight_ =
		sge::font::weight::optional_unit(
			_weight
		);

	return
		*this;
}

sge::font::parameters &
sge::font::parameters::italic()
{
	italic_ =
		true;

	return
		*this;
}

sge::font::optional_dpi const &
sge::font::parameters::dpi() const
{
	return
		dpi_;
}

sge::font::optional_ttf_size const &
sge::font::parameters::ttf_size() const
{
	return
		ttf_size_;
}

sge::font::optional_family const &
sge::font::parameters::family() const
{
	return
		family_;
}

sge::font::weight::optional_unit const &
sge::font::parameters::weight() const
{
	return
		weight_;
}

bool
sge::font::parameters::italic() const
{
	return
		italic_;
}
