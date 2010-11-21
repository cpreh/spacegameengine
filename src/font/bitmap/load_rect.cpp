/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "load_rect.hpp"
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/font/exception.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::image::rect const
sge::font::bitmap::load_rect(
	sge::parse::json::member_vector const &_members
)
{
	parse::json::element_vector const &elements(
		parse::json::find_member_exn<
			parse::json::array
		>(
			_members,
			FCPPT_TEXT("rect")
		).elements
	);

	if(elements.size() != 2)
		throw sge::font::exception(
			FCPPT_TEXT("Bogus rect detected")
		);

	parse::json::element_vector const
		&first_elements(
			parse::json::get<
				parse::json::array
			>(
				elements[0]
			).elements
		),
		&second_elements(
			parse::json::get<
				parse::json::array
			>(
				elements[1]
			).elements
		);

	if(first_elements.size() != 2 || second_elements.size() != 2)
		throw sge::font::exception(
			FCPPT_TEXT("Bogus rect subelements detected")
		);

	return image::rect(
		image::rect::vector(
			parse::json::get<
				int
			>(
				first_elements[0]
			),
			parse::json::get<
				int
			>(
				first_elements[1]
			)
		),
		image::rect::dim(
			parse::json::get<
				int
			>(
				second_elements[0]
			),
			parse::json::get<
				int
			>(
				second_elements[1]
			)
		)
	);
}
