/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "load_one_file.hpp"
#include "load_rect.hpp"
#include "load_offset.hpp"
#include "char_metric.hpp"
#include <sge/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/log/global.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::image2d::file_ptr const
sge::font::bitmap::load_one_file(
	fcppt::filesystem::path const &_stem,
	sge::parse::json::object const &_object,
	sge::image2d::multi_loader &_loader,
	bitmap::char_map &_char_map
)
{
	sge::parse::json::member_vector const &top_members(
		_object.members
	);

	sge::image2d::file_ptr const return_file(
		_loader.load(
			_stem
			/
			parse::json::find_member_exn<
				fcppt::string
			>(
				top_members,
				FCPPT_TEXT("filename")
			)
		)
	);

	sge::parse::json::array const &glyph_array(
		parse::json::find_member_exn<
			parse::json::array
		>(
			top_members,
			FCPPT_TEXT("glyphs")
		)
	);

	for(
		parse::json::element_vector::const_iterator elem_it(
			glyph_array.elements.begin()
		);
		elem_it != glyph_array.elements.end();
		++elem_it
	)
	try
	{
		sge::parse::json::member_vector const &members(
			parse::json::get<
				parse::json::object
			>(
				*elem_it
			).members
		);

		fcppt::string const name(
			parse::json::find_member_exn<
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
			FCPPT_LOG_WARNING(
				log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Invalid character in bitmap font: \"")
					<< name
					<< FCPPT_TEXT("\"")
			);

			continue;
		}

		_char_map.insert(
			std::make_pair(
				name[0],
				fcppt::make_shared_ptr<
					char_metric
				>(
					sge::image2d::view::checked_sub(
						return_file->view(),
						font::bitmap::load_rect(
							members
						)
					),
					font::bitmap::load_offset(
						members
					),
					parse::json::find_member_exn<
						int
					>(
						members,
						FCPPT_TEXT("x_advance")
					)
				)
			)
		);
	}
	catch(
		sge::exception const &_exception
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Skipping character in bitmap font because \"")
				<< _exception.string()
				<< FCPPT_TEXT('"')
		);
	}

	return return_file;
}
