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


#include <sge/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/log/global.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/load_offset.hpp>
#include <sge/src/font/bitmap/load_one_file.hpp>
#include <sge/src/font/bitmap/load_rect.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::image2d::file_unique_ptr
sge::font::bitmap::load_one_file(
	boost::filesystem::path const &_stem,
	sge::parse::json::object const &_object,
	sge::image2d::system &_image_system,
	sge::font::bitmap::char_map &_char_map
)
{
	sge::parse::json::member_map const &top_members(
		_object.members
	);

	sge::image2d::file_unique_ptr return_file(
		_image_system.load(
			_stem
			/
			sge::parse::json::find_member_exn<
				fcppt::string
			>(
				top_members,
				FCPPT_TEXT("filename")
			)
		)
	);

	sge::parse::json::array const &glyph_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			top_members,
			FCPPT_TEXT("glyphs")
		)
	);

	for(
		sge::parse::json::element_vector::const_iterator elem_it(
			glyph_array.elements.begin()
		);
		elem_it != glyph_array.elements.end();
		++elem_it
	)
	try
	{
		sge::parse::json::member_map const &members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				*elem_it
			).members
		);

		fcppt::string const name(
			sge::parse::json::find_member_exn<
				fcppt::string
			>(
				members,
				FCPPT_TEXT("name")
			)
		);

		// TODO:!
		if(
			name.size() != 1
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Invalid character in bitmap font: \"")
					<< name
					<< FCPPT_TEXT("\"")
			);

			continue;
		}

		fcppt::container::ptr::insert_unique_ptr_map(
			_char_map,
			name[0],
			fcppt::make_unique_ptr<
				sge::font::bitmap::char_metric
			>(
				sge::image2d::view::checked_sub(
					return_file->view(),
					sge::font::bitmap::load_rect(
						members
					)
				),
				sge::font::bitmap::load_offset(
					members
				),
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					members,
					FCPPT_TEXT("x_advance")
				)
			)
		);
	}
	catch(
		sge::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Skipping character in bitmap font because \"")
				<< _exception.string()
				<< FCPPT_TEXT('"')
		);
	}

	return
		std::move(
			return_file
		);
}
