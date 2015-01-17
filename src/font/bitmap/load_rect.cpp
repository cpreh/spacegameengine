/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/exception.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/src/font/bitmap/load_rect.hpp>
#include <fcppt/text.hpp>


sge::image2d::rect const
sge::font::bitmap::load_rect(
	sge::parse::json::member_map const &_members
)
{
	sge::parse::json::element_vector const &elements(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			_members,
			FCPPT_TEXT("rect")
		).elements
	);

	if(
		elements.size() != 2
	)
		throw sge::font::exception(
			FCPPT_TEXT("Bogus rect detected")
		);

	sge::parse::json::element_vector const
		&first_elements(
			sge::parse::json::get<
				sge::parse::json::array
			>(
				elements[0]
			).elements
		),
		&second_elements(
			sge::parse::json::get<
				sge::parse::json::array
			>(
				elements[1]
			).elements
		);

	if(
		first_elements.size() != 2
		|| second_elements.size() != 2
	)
		throw sge::font::exception(
			FCPPT_TEXT("Bogus rect subelements detected")
		);

	return
		sge::image2d::rect(
			sge::image2d::rect::vector(
				static_cast<
					sge::image2d::rect::value_type
				>(
					sge::parse::json::get<
						sge::parse::json::int_type
					>(
						first_elements[0]
					)
				),
				static_cast<
					sge::image2d::rect::value_type
				>(
					sge::parse::json::get<
						sge::parse::json::int_type
					>(
						first_elements[1]
					)
				)
			),
			sge::image2d::rect::dim(
				static_cast<
					sge::image2d::rect::value_type
				>(
					sge::parse::json::get<
						sge::parse::json::int_type
					>(
						second_elements[0]
					)
				),
				static_cast<
					sge::image2d::rect::value_type
				>(
					sge::parse::json::get<
						sge::parse::json::int_type
					>(
						second_elements[1]
					)
				)
			)
		);
}
