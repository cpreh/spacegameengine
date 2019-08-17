//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <sge/image2d/dim.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/store/l8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/log_settings.hpp>
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
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_input.hpp>
#include <fcppt/log/level_output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_result.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
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
#include <brigand/sequences/list.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
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

FCPPT_RECORD_MAKE_LABEL(
	log_level_label
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
	>,
	fcppt::record::element<
		log_level_label,
		fcppt::log::level
	>
>
argument_record;

void
render_text_main(
	argument_record const &_args
)
{
	sge::systems::instance<
		brigand::list<
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
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::record::get<
								log_level_label
							>(
								_args
							)
						}
					}
				)
			)
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

	sge::image2d::store::l8 store{
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
		sge::image2d::view::object(
			store.wrapped_view()
		)
	);

	sge::image2d::save_from_view(
		sys.image_system(),
		sge::image2d::view::const_object{
			store.const_wrapped_view()
		},
		std::filesystem::path{
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
			},
			fcppt::options::option<
				log_level_label,
				fcppt::log::level
			>{
				fcppt::options::optional_short_name{},
				fcppt::options::long_name{
					FCPPT_TEXT("log-level")
				},
				fcppt::options::make_default_value(
					fcppt::optional::make(
						fcppt::log::level::debug
					)
				),
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("The log level to use.")
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
