/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../metrics.hpp"
#include "../char_metric.hpp"
#include "../load_rect.hpp"
#include "../load_offset.hpp"
#include <sge/parse/json/parse_file.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/filesystem/replace_extension.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/file.hpp>
#include <sge/image/loader.hpp>
#include <sge/font/char_not_available.hpp>
#include <sge/font/exception.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <sge/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <sge/exception.hpp>
#include <boost/foreach.hpp>
#include <utility>

sge::bitmapfont::metrics::metrics(
	filesystem::path const &path,
	sge::image::loader_ptr const loader)
:
	image_(
		loader->load(
			path
		)
	),
	line_height_(),
	char_map_()
{
	sge::filesystem::path const json_file(
		filesystem::replace_extension(
			path,
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
			json_file.string()
			+ FCPPT_TEXT(" contains errors!")
		);


	sge::parse::json::member_vector const &top_members(
		result.members
	);

	line_height_
	= parse::json::find_member<
		int
	>(
		top_members,
		FCPPT_TEXT("line_height")
	);

	BOOST_FOREACH(
		parse::json::element_vector::const_reference elem,
		parse::json::find_member<
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
			parse::json::find_member<
				string
			>(
				members,
				FCPPT_TEXT("name")
			)
		);

		if(name.size() != 1)
		{
			FCPPT_LOG_WARNING(
				log::global(),
				log::_
					<< FCPPT_TEXT("Invalid character in bitmap font: ")
					<< name
			);

			continue;
		}


		char_map_.insert(
			std::make_pair(
				name[0],
				make_shared_ptr<
					char_metric
				>(
					sge::image::view::sub(
						image_->view(),
						load_rect(
							members
						)
					),
					load_offset(
						members
					),
					parse::json::find_member<
						int
					>(
						members,
						FCPPT_TEXT("x_advance")
					)
				)
			)
		);
	}
	catch(exception const &e)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			log::_
				<< FCPPT_TEXT("Skipping character in bitmap font because \"")
				<< e.string()
				<< FCPPT_TEXT('"')
		);
	}
}

sge::bitmapfont::metrics::~metrics()
{}

sge::font::char_metric_ptr const
sge::bitmapfont::metrics::load_char(
	char_type const c)
{
	char_map::const_iterator const it(
		char_map_.find(
			c
		)
	);

	if(it == char_map_.end())
		throw font::char_not_available(
			c
		);

	return it->second;
}

sge::font::unit
sge::bitmapfont::metrics::line_height() const
{
	return line_height_;
}
