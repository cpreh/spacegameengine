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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_element_vector.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::array::array()
:
	elements()
{
}

sge::parse::json::array::array(
	sge::parse::json::element_vector const &_elements
)
:
	elements(
		_elements
	)
{
}

sge::parse::json::array::array(
	sge::parse::json::element_vector &&_elements
)
:
	elements(
		std::move(
			_elements
		)
	)
{
}

sge::parse::json::array::array(
	sge::parse::json::optional_element_vector const &_elements
)
:
	elements(
		fcppt::optional::from(
			_elements,
			[]{
				return
					sge::parse::json::element_vector();
			}
		)
	)
{
}

sge::parse::json::array::array(
	sge::parse::json::optional_element_vector &&_elements
)
:
	elements(
		fcppt::optional::from(
			std::move(
				_elements
			),
			[]{
				return
					sge::parse::json::element_vector();
			}
		)
	)
{
}
