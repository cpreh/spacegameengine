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


#include "load_rect.hpp"
#include "load_offset.hpp"
#include <sge/font/bitmap/metrics.hpp>
#include <sge/font/bitmap/char_metric.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/font/char_not_available.hpp>
#include <sge/font/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/replace_extension.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <boost/foreach.hpp>
#include <utility>

sge::font::bitmap::metrics::metrics(
	fcppt::filesystem::path const &_path,
	sge::image2d::multi_loader &_loader
)
:
	image_(
		_loader.load(
			_path
		)
	),
	line_height_(),
	char_map_()
{
	fcppt::filesystem::path const json_file(
		fcppt::filesystem::replace_extension(
			_path,
			FCPPT_TEXT("json")
		)
	);

	sge::parse::json::object result;

	if(
		!parse::json::parse_file(
			json_file,
			result
		)
	)
		throw font::exception(
			fcppt::filesystem::path_to_string(
				json_file
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

	BOOST_FOREACH(
		parse::json::element_vector::const_reference elem,
		parse::json::find_member_exn<
			parse::json::array
		>(
			top_members,
			FCPPT_TEXT("glyphs")
		).elements
	)
	try
	{
		sge::parse::json::member_vector const &members(
			parse::json::get<
				parse::json::object
			>(
				elem
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

		if(name.size() != 1)
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

		char_map_.insert(
			std::make_pair(
				name[0],
				fcppt::make_shared_ptr<
					char_metric
				>(
					sge::image2d::view::checked_sub(
						image_->view(),
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
}

sge::font::bitmap::metrics::~metrics()
{}

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
