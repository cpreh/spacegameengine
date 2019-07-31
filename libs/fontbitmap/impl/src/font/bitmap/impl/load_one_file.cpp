//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/core/exception.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/exception.hpp>
#include <sge/font/from_std_wstring.hpp>
#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <sge/font/bitmap/impl/load_offset.hpp>
#include <sge/font/bitmap/impl/load_one_file.hpp>
#include <sge/font/bitmap/impl/load_rect.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::image2d::file_unique_ptr
sge::font::bitmap::impl::load_one_file(
	fcppt::log::object &_log,
	boost::filesystem::path const &_stem,
	sge::parse::json::object const &_object,
	sge::image2d::system &_image_system,
	sge::font::bitmap::impl::char_map &_char_map
)
{
	sge::parse::json::member_map const &top_members(
		_object.members
	);

	sge::image2d::file_unique_ptr return_file(
		sge::image2d::load_exn(
			_image_system,
			_stem
			/
			sge::parse::json::find_member_exn<
				sge::charconv::utf8_string
			>(
				top_members,
				"filename"
			)
		)
	);

	// TODO: map_optional
	for(
		auto const &elem
		:
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			top_members,
			"glyphs"
		).elements
	)
	try
	{
		sge::parse::json::member_map const &members(
			sge::parse::json::get_exn<
				sge::parse::json::object
			>(
				elem.get()
			).members
		);

		sge::font::string const name{
			sge::font::from_std_wstring(
				sge::charconv::convert<
					sge::charconv::encoding::wchar,
					sge::charconv::encoding::utf8
				>(
					sge::parse::json::find_member_exn<
						sge::charconv::utf8_string
					>(
						members,
						"name"
					)
				)
			)
		};

		// TODO: maybe_front!
		if(
			name.size() != 1
		)
		{
			FCPPT_LOG_ERROR(
				_log,
				fcppt::log::out
					<<
					FCPPT_TEXT("Invalid character in bitmap font: \"")
					<<
					fcppt::optional::from(
						sge::font::to_fcppt_string(
							name
						),
						[]{
							return
								fcppt::string{
									FCPPT_TEXT("CONVERSION_FAILURE")
								};
						}
					)
					<<
					FCPPT_TEXT("\"")
			)

			continue;
		}

		sge::font::char_type const element{
			name[0]
		};

		if(
			!_char_map.insert(
				std::make_pair(
					element,
					sge::font::bitmap::impl::char_metric{
						sge::image2d::view::checked_sub(
							return_file->view(),
							sge::font::bitmap::impl::load_rect(
								members
							)
						),
						sge::font::bitmap::impl::load_offset(
							members
						),
						sge::parse::json::convert::to_int<
							sge::font::unit
						>(
							sge::parse::json::find_member_value_exn(
								members,
								"x_advance"
							)
						)
					}
				)
			).second
		)
			throw
				sge::font::exception{
					FCPPT_TEXT("Double insert of '")
					+
					fcppt::optional::from(
						sge::font::to_fcppt_string(
							sge::font::string{
								element
							}
						),
						[]{
							return
								fcppt::string{
									FCPPT_TEXT("CONVERSION_FAILURE")
								};
						}
					)
					+
					FCPPT_TEXT(" in bitmap font")
				};
	}
	catch(
		sge::core::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::out
				<< FCPPT_TEXT("Skipping character in bitmap font because \"")
				<< _exception.string()
				<< FCPPT_TEXT('"')
		)
	}

	return
		return_file;
}
