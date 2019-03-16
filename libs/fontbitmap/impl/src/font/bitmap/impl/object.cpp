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


#include <sge/font/exception.hpp>
#include <sge/font/height.hpp>
#include <sge/font/log_location.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <sge/font/bitmap/impl/load_one_file.hpp>
#include <sge/font/bitmap/impl/log_name.hpp>
#include <sge/font/bitmap/impl/object.hpp>
#include <sge/font/bitmap/impl/text.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::impl::object::object(
	fcppt::log::context &_log_context,
	boost::filesystem::path const &_path,
	sge::image2d::system &_image_system
)
:
	object(
		_log_context,
		_path,
		_image_system,
		sge::parse::json::parse_file_exn(
			_path
		)
	)
{
}

sge::font::bitmap::impl::object::~object()
{
}

sge::font::bitmap::impl::object::object(
	fcppt::log::context &_log_context,
	boost::filesystem::path const &_path,
	sge::image2d::system &_image_system,
	sge::parse::json::start const &_start
)
:
	log_{
		_log_context,
		sge::font::log_location(),
		sge::log::default_parameters(
			sge::font::bitmap::impl::log_name()
		)
	},
	line_height_(
		sge::parse::json::convert::to_int<
			sge::font::unit
		>(
			sge::parse::json::find_member_value_exn(
				_start.object().members,
				"line_height"
			)
		)
	),
	char_map_(),
	images_(
		fcppt::algorithm::map<
			image_vector
		>(
			sge::parse::json::find_member_exn<
				sge::parse::json::array
			>(
				_start.object().members,
				"textures"
			).elements,
			[
				&_path,
				&_image_system,
				this
			](
				fcppt::recursive<
					sge::parse::json::value
				> const &_element
			)
			{
				return
					sge::font::bitmap::impl::load_one_file(
						log_,
						_path.parent_path(),
						sge::parse::json::get_exn<
							sge::parse::json::object
						>(
							_element.get()
						),
						_image_system,
						char_map_
					);
			}
		)
	),
	color_format_(
		fcppt::algorithm::fold(
			images_,
			sge::image::color::optional_format(),
			[](
				sge::image2d::file_unique_ptr const &_file,
				sge::image::color::optional_format const _state
			)
			{
				sge::image::color::format const current_format(
					sge::image2d::view::format(
						_file->view()
					)
				);

				fcppt::optional::maybe_void(
					_state,
					[
						current_format
					](
						sge::image::color::format const _last_format
					)
					{
						if(
							_last_format
							!=
							current_format
						)
							throw
								sge::font::exception{
									FCPPT_TEXT("Bitmapfont images can't differ in color formats! ")
									FCPPT_TEXT(" The color formats are: ")
									+
									sge::image::color::format_to_string(
										_last_format
									)
									+
									FCPPT_TEXT(" and ")
									+
									sge::image::color::format_to_string(
										current_format
									)
								};
					}
				);

				return
					sge::image::color::optional_format(
						current_format
					);
			}
		)
	)
{
}

sge::font::text_unique_ptr
sge::font::bitmap::impl::object::create_text(
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::font::text
		>(
			fcppt::make_unique_ptr<
				sge::font::bitmap::impl::text
			>(
				log_,
				char_map_,
				_string,
				_text_parameters,
				line_height_
			)
		);
}

sge::image::color::optional_format
sge::font::bitmap::impl::object::preferred_color_format() const
{
	return
		color_format_;
}

sge::font::metrics
sge::font::bitmap::impl::object::metrics() const
{
	return
		sge::font::metrics(
			sge::font::height(
				line_height_.get()
			)
		);
}
