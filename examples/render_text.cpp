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


#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/store/object.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_result.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	text_label
);

FCPPT_RECORD_MAKE_LABEL(
	output_file_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		text_label,
		fcppt::string
	>,
	fcppt::record::element<
		output_file_label,
		fcppt::string
	>
>
argument_record;

void
render_text_main(
	argument_record const &_args
)
{
	sge::systems::instance<
		boost::mpl::vector2<
			sge::systems::with_image2d,
			sge::systems::with_font
		>
	> const sys{
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::media::optional_extension_set()
			)
		)(
			sge::systems::font()
		)
	};

	sge::font::object_unique_ptr const font{
		sys.font_system().create_font(
			// TODO: Add options for this
			sge::font::parameters{}
		)
	};

	sge::font::text_unique_ptr const text{
		font->create_text(
			sge::font::from_fcppt_string(
				fcppt::record::get<
					text_label
				>(
					_args
				)
			),
			sge::font::text_parameters{
				sge::font::align_h::variant{
					sge::font::align_h::left{}
				}
			}
		)
	};

	sge::image2d::store::object store{
		fcppt::optional::from(
			font->preferred_color_format(),
			[]{
				return
					sge::image::color::format::a8;
			}
		),
		fcppt::math::dim::structure_cast<
			sge::image2d::dim,
			fcppt::cast::size_fun
		>(
			text->rect().size()
		),
		// TODO: Initialize with something?
		fcppt::no_init{}
	};

	text->render(
		sge::image2d::store::view(
			store
		)
	);

	sge::image2d::save_from_view(
		sys.image_system(),
		sge::image2d::view::to_const(
			sge::image2d::store::view(
				store
			)
		),
		boost::filesystem::path{
			fcppt::record::get<
				output_file_label
			>(
				_args
			)
		}
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	auto const parser{
		fcppt::options::apply(
			fcppt::options::argument<
				text_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("text")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("The text to render.")
					}
				}
			},
			fcppt::options::argument<
				output_file_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("output-file")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path to the output file.")
					}
				}
			}
		)
	};

	typedef
	fcppt::options::result_of<
		decltype(
			parser
		)
	>
	result_type;

	fcppt::options::help_result<
		result_type
	> const result{
		fcppt::options::parse_help(
			fcppt::options::default_help_switch(),
			parser,
			fcppt::args_from_second(
				argc,
				argv
			)
		)
	};

	return
		fcppt::variant::match(
			result,
			[](
				fcppt::options::result<
					result_type
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						{
							fcppt::io::cerr()
								<<
								_error
								<<
								FCPPT_TEXT('\n');

							return
								EXIT_FAILURE;
						},
						[](
							result_type const &_args
						)
						{
							render_text_main(
								fcppt::record::permute<
									argument_record
								>(
									_args
								)
							);

							return
								EXIT_SUCCESS;
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				fcppt::io::cout()
					<<
					_help_text
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
