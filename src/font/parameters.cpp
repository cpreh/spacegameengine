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


#include <sge/font/optional_family.hpp>
#include <sge/font/optional_ttf_size.hpp>
#include <sge/font/optional_weight.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight.hpp>
#include <fcppt/string.hpp>


sge::font::parameters::parameters()
:
	ttf_size_(),
	family_(),
	weight_(),
	italic_(
		false
	)
{
}

sge::font::parameters &
sge::font::parameters::ttf_size(
	sge::font::ttf_size const _ttf_size
)
{
	ttf_size_ = _ttf_size;

	return *this;
}

sge::font::parameters &
sge::font::parameters::family(
	fcppt::string const &_family
)
{
	family_ = _family;

	return *this;
}

sge::font::parameters &
sge::font::parameters::weight(
	sge::font::weight const _weight
)
{
	weight_ = _weight;

	return *this;
}

sge::font::parameters &
sge::font::parameters::italic()
{
	italic_ = true;

	return *this;
}

sge::font::optional_ttf_size const &
sge::font::parameters::ttf_size() const
{
	return ttf_size_;
}

sge::font::optional_family const &
sge::font::parameters::family() const
{
	return family_;
}

sge::font::optional_weight const &
sge::font::parameters::weight() const
{
	return weight_;
}

bool
sge::font::parameters::italic() const
{
	return italic_;
}
