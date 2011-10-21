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
#include "metrics.hpp"
#include <sge/font/char_not_available.hpp>
#include <sge/font/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/remove_filename.hpp>


sge::font::bitmap::metrics::metrics(
	fcppt::filesystem::path const &_path,
	sge::image2d::multi_loader &_loader
)
:
	images_(),
	line_height_(),
	char_map_()
{
	sge::parse::json::object result;

	if(
		!parse::json::parse_file(
			_path,
			result
		)
	)
		throw font::exception(
			fcppt::filesystem::path_to_string(
				_path
			)
			+ FCPPT_TEXT(" contains errors!")
		);


	sge::parse::json::member_vector const &top_members(
		result.members
	);

	line_height_
		= parse::json::find_member_exn<
			int
		>(
			top_members,
			FCPPT_TEXT("line_height")
		);

	fcppt::filesystem::path const stem(
		fcppt::filesystem::remove_filename(
			_path
		)
	);

	sge::parse::json::array const &textures_array(
		parse::json::find_member_exn<
			parse::json::array
		>(
			top_members,
			FCPPT_TEXT("textures")
		)
	);

	for(
		sge::parse::json::element_vector::const_iterator elem_it(
			textures_array.elements.begin()
		);
		elem_it != textures_array.elements.end();
		++elem_it
	)
		images_.push_back(
			font::bitmap::load_one_file(
				stem,
				parse::json::get<
					parse::json::object
				>(
					*elem_it
				),
				_loader,
				char_map_
			)
		);
}

sge::font::bitmap::metrics::~metrics()
{
}

sge::font::char_metric_ptr const
sge::font::bitmap::metrics::load_char(
	font::char_type const _ch
)
{
	char_map::const_iterator const it(
		char_map_.find(
			_ch
		)
	);

	if(
		it == char_map_.end()
	)
		throw font::char_not_available(
			_ch
		);

	return it->second;
}

sge::font::unit
sge::font::bitmap::metrics::line_height() const
{
	return line_height_;
}
