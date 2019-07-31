//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/matching_color_format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::image::color::format
sge::renderer::vf::dynamic::matching_color_format(
	sge::image::color::format const _format,
	sge::renderer::vf::dynamic::color_format_vector const &_formats
)
{
	return
		fcppt::algorithm::contains(
			_formats,
			_format
		)
		?
			_format
		:
			*fcppt::optional::to_exception(
				fcppt::algorithm::find_if_opt(
					_formats,
					[
						_format
					](
						sge::renderer::vf::dynamic::color_format_vector::value_type const &_value
					)
					{
						return
							sge::image::color::format_stride(
								_format
							)
							==
							sge::image::color::format_stride(
								_value
							);
					}
				),
				[
					_format
				]{
					return
						sge::renderer::exception{
							FCPPT_TEXT("Unsupported vertex color ")
							+
							sge::image::color::format_to_string(
								_format
							)
						};
				}
			)
		;
}
