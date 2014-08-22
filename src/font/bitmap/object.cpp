/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/load_one_file.hpp>
#include <sge/src/font/bitmap/object.hpp>
#include <sge/src/font/bitmap/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::object::object(
	boost::filesystem::path const &_path,
	sge::image2d::system &_image_system
)
:
	images_(),
	line_height_(),
	char_map_(),
	color_format_()
{
	sge::parse::json::start const result(
		sge::parse::json::parse_file_exn(
			_path
		)
	);

	sge::parse::json::member_map const &top_members(
		result.object().members
	);

	line_height_
		=
		sge::parse::json::convert::to_int<
			sge::font::unit
		>(
			sge::parse::json::find_member_value_exn(
				top_members,
				FCPPT_TEXT("line_height")
			)
		);

	boost::filesystem::path const parent_path(
		_path.parent_path()
	);

	for(
		auto const &elem
		:
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			top_members,
			FCPPT_TEXT("textures")
		).elements
	)
		images_.push_back(
			sge::font::bitmap::load_one_file(
				parent_path,
				sge::parse::json::get<
					sge::parse::json::object
				>(
					elem
				),
				_image_system,
				char_map_
			)
		);

	sge::image::color::format const current_format(
		sge::image2d::view::format(
			images_.back()->view()
		)
	);

	if(
		!color_format_
	)
		color_format_ =
			sge::image::color::optional_format(
				current_format
			);
	else if(
		*color_format_
		!=
		current_format
	)
		throw sge::font::exception(
			FCPPT_TEXT("Bitmapfont images can't differ in color formats! ")
			FCPPT_TEXT(" The color formats are: ")
			+
			sge::image::color::format_to_string(
				*color_format_
			)
			+
			FCPPT_TEXT(" and ")
			+
			sge::image::color::format_to_string(
				current_format
			)
		);
}

sge::font::bitmap::object::~object()
{
}

sge::font::text_unique_ptr
sge::font::bitmap::object::create_text(
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sge::font::bitmap::text
		>(
			char_map_,
			_string,
			_text_parameters,
			line_height_
		);
}

sge::image::color::optional_format const
sge::font::bitmap::object::color_format() const
{
	return
		color_format_;
}

sge::font::metrics const
sge::font::bitmap::object::metrics() const
{
	return
		sge::font::metrics(
			sge::font::height(
				line_height_
			)
		);
}
