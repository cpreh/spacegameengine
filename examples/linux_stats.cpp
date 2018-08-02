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
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/graph/axis_constraint.hpp>
#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline.hpp>
#include <sge/graph/color_schemes.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/object.hpp>
#include <sge/graph/optional_axis_constraint.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <array>
#include <example_main.hpp>
#include <exception>
#include <fstream>
#include <ios>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

class jiffies
{
public:
	typedef
	unsigned long
	value_type;

	FCPPT_MAKE_STRONG_TYPEDEF(
		value_type,
		total_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		value_type,
		work_type
	);

	jiffies(
		total_type const &_total,
		work_type const &_work
	)
	:
		total_(
			_total
		),
		work_(
			_work
		)
	{
	}

	total_type
	total() const
	{
		return
			total_;
	}

	work_type
	work() const
	{
		return
			work_;
	}

	jiffies
	operator-(
		jiffies const &_other
	) const
	{
		return
			jiffies(
				this->total() - _other.total(),
				this->work() - _other.work()
			);
	}

	template<
		typename Float
	>
	Float
	work_percentage() const
	{
		static_assert(
			std::is_floating_point<
				Float
			>::value,
			"Float must be a floating point type"
		);

		return
			total_.get()
			!=
			fcppt::literal<
				value_type
			>(
				0
			)
			?
				fcppt::cast::int_to_float<
					Float
				>(
					work_.get()
				)
				/
				fcppt::cast::int_to_float<
					Float
				>(
					total_.get()
				)
				*
				fcppt::literal<
					Float
				>(
					100
				)
			:
				fcppt::literal<
					Float
				>(
					0
				)
			;
	}
private:
	total_type total_;

	work_type work_;
};

// Source: http://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-c
jiffies
count_jiffies()
{
	std::ifstream cpuinfo{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::filesystem::open<
				std::ifstream
			>(
				"/proc/stat",
				std::ios_base::in
			)
		)
	};

	std::string first_word;

	cpuinfo >> first_word;

	FCPPT_ASSERT_ERROR(
		first_word == "cpu"
	);

	typedef
	std::array<
		jiffies::value_type,
		7u
	>
	jiffies_array;

	jiffies_array current_jiffies;

	// TODO: Use optionals
	for(
		auto &jiffie
		:
		current_jiffies
	)
		if(
			!(cpuinfo >> jiffie)
		)
			std::terminate();

	return
		jiffies(
			jiffies::total_type(
				std::accumulate(
					current_jiffies.begin(),
					current_jiffies.end(),
					0u
				)
			),
			jiffies::work_type(
				std::accumulate(
					current_jiffies.begin(),
					current_jiffies.begin() + 3,
					0u
				)
			)
		);
}

class graph_with_label
{
	FCPPT_NONCOPYABLE(
		graph_with_label
	);
public:
	graph_with_label(
		fcppt::unique_ptr<
			sge::graph::object
		> &&_graph,
		fcppt::unique_ptr<
			sge::font::draw::static_text
		> &&_label
	)
	:
		graph_(
			std::move(
				_graph
			)
		),
		label_(
			std::move(
				_label
			)
		)
	{
	}

	graph_with_label(
		graph_with_label &&
	) = default;

	graph_with_label &
	operator=(
		graph_with_label &&
	) = delete;

	~graph_with_label()
	{
	}

	sge::graph::object &
	get_graph() const
	{
		return
			*graph_;
	}

	sge::font::draw::static_text &
	get_label() const
	{
		return
			*label_;
	}
private:
	fcppt::unique_ptr<
		sge::graph::object
	> graph_;

	fcppt::unique_ptr<
		sge::font::draw::static_text
	> label_;
};

double
count_memory()
{
	std::ifstream meminfo(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::filesystem::open<
				std::ifstream
			>(
				"/proc/meminfo",
				std::ios_base::in
			)
		)
	);

	unsigned
		total{0},
		free{0},
		buffers{0},
		cached{0},
		slab{0};

	std::string first_word, last_word;

	unsigned value;

	// TODO: Use optionals
	while(
		(
			meminfo
			>>
			first_word
			>>
			value
		).ignore(
			std::numeric_limits<
				std::streamsize
			>::max(),
			'\n'
		)
	)
	{
		if(
			first_word == "MemTotal:"
		)
			total = value;
		else if(
			first_word == "MemFree:"
		)
			free = value;
		else if (
			first_word == "Buffers:"
		)
			buffers = value;
		else if(
			first_word == "Cached:"
		)
			cached = value;
		else if(
			first_word == "Slab:"
		)
			slab = value;
	}

	unsigned const used{
		total - free - buffers - cached - slab
	};

	FCPPT_ASSERT_ERROR(
		total > 0
	);

	return
		100.0
		*
		fcppt::cast::int_to_float<
			double
		>(
			used
		)
		/
		fcppt::cast::int_to_float<
			double
		>(
			total
		);
}

std::vector<
	std::string
>
network_devices()
{
	std::ifstream netinfo{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::filesystem::open<
				std::ifstream
			>(
				"/proc/net/dev",
				std::ios_base::in
			)
		)
	};

	// skip the first two lines
	netinfo.ignore(
		std::numeric_limits<
			std::streamsize
		>::max(),
		'\n'
	);

	netinfo.ignore(
		std::numeric_limits<
			std::streamsize
		>::max(),
		'\n'
	);

	std::string device;

	std::vector<
		std::string
	> result;

	// TODO: Use optionals
	while(
		(
			netinfo
			>>
			device
		).ignore(
			std::numeric_limits<
				std::streamsize
			>::max(),
			'\n'
		)
	)
	{
		if(
			device != "lo:"
		)
			result.push_back(
				device
			);
	}

	return
		result;
}

unsigned long
count_traffic(
	std::string const &_device
)
{
	std::ifstream netinfo{
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::filesystem::open<
				std::ifstream
			>(
				"/proc/net/dev",
				std::ios_base::in
			)
		)
	};

	std::vector<
		std::string
	> result;

	// skip the first two lines
	netinfo.ignore(
		std::numeric_limits<
			std::streamsize
		>::max(),
		'\n'
	);

	netinfo.ignore(
		std::numeric_limits<
			std::streamsize
		>::max(),
		'\n'
	);

	std::string device;

	unsigned long value;

	// TODO: Use optionals
	while(
		(
			netinfo
			>>
			device
			>>
			value
		).ignore(
			std::numeric_limits<
				std::streamsize
			>::max(),
			'\n'
		)
	)
	{
		if(
			device
			==
			_device + ':'
		)
			return
				value;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

FCPPT_RECORD_MAKE_LABEL(
	width_label
);

FCPPT_RECORD_MAKE_LABEL(
	height_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		width_label,
		sge::window::dim::value_type
	>,
	fcppt::record::element<
		height_label,
		sge::window::dim::value_type
	>
>
arg_type;

awl::main::exit_code
main_program(
	arg_type const &_args
)
{
	sge::window::dim const graph_dim{
		fcppt::record::get<
			width_label
		>(
			_args
		),
		fcppt::record::get<
			height_label
		>(
			_args
		)
	};

	std::vector<
		std::string
	> const devices {
		::network_devices()
	};

	std::map<
		std::string,
		unsigned long
	>
	device_totals;

	sge::systems::instance<
		brigand::list<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_font
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("linux stats example")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
	);

	sge::font::object_unique_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
			.family(
				FCPPT_TEXT(
					"monospace"))
		)
	);

	sge::font::draw::static_text cpu_label(
		sys.renderer_device_ffp(),
		*font,
		SGE_FONT_LIT(
			"cpu"
		),
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::left()
			)
		),
		sge::font::vector(
			0,
			0
		),
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::font::draw::static_text mem_label(
		sys.renderer_device_ffp(),
		*font,
		SGE_FONT_LIT(
			"mem"
		),
		sge::font::text_parameters(
			sge::font::align_h::variant(
				sge::font::align_h::left()
			)
		),
		sge::font::vector(
			0,
			fcppt::cast::size<
				sge::font::unit
			>(
				fcppt::cast::to_signed(
					graph_dim.h()
				)
			)
		),
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::graph::object cpugraph(
		sge::graph::position(
			sge::renderer::vector2(
				0.0f,
				0.0f
			)
		),
		fcppt::math::dim::structure_cast<
			sge::image2d::dim,
			fcppt::cast::size_fun
		>(
			graph_dim
		),
		sys.renderer_device_ffp(),
		sge::graph::baseline(
			50.0),
		sge::graph::optional_axis_constraint(
			sge::graph::axis_constraint(
				0.0,
				100.0
			)
		),
		sge::graph::color_schemes::default_()
	);

	sge::graph::object memgraph(
		sge::graph::position(
			sge::renderer::vector2(
				0.0f,
				fcppt::cast::int_to_float<
					sge::renderer::vector2::value_type
				>(
					graph_dim.h()
				)
			)
		),
		fcppt::math::dim::structure_cast<
			sge::image2d::dim,
			fcppt::cast::size_fun
		>(
			graph_dim
		),
		sys.renderer_device_ffp(),
		sge::graph::baseline(
			50.0
		),
		sge::graph::optional_axis_constraint(
			sge::graph::axis_constraint(
				0.0,
				100.0
			)
		),
		sge::graph::color_schemes::default_()
	);

	jiffies last_jiffies{
		count_jiffies()
	};

	typedef
	std::map<
		std::string,
		graph_with_label
	>
	device_to_graph;

	device_to_graph device_map;

	for(
		auto it(
			devices.begin()
		);
		it != devices.end();
		++it
	)
	{
		auto const &device(
			*it
		);

		sge::font::unit const y{
			fcppt::cast::size<
				sge::font::unit
			>(
				2 + it - devices.begin()
			)
			*
			fcppt::cast::size<
				sge::font::unit
			>(
				fcppt::cast::to_signed(
					graph_dim.h()
				)
			)
		};

		device_map.insert(
			std::make_pair(
				device,
				graph_with_label(
					fcppt::make_unique_ptr<
						sge::graph::object
					>(
						sge::graph::position(
							sge::renderer::vector2(
								0.0f,
								fcppt::cast::int_to_float<
									sge::renderer::scalar
								>(
									y
								)
							)
						),
						fcppt::math::dim::structure_cast<
							sge::image2d::dim,
							fcppt::cast::size_fun
						>(
							graph_dim
						),
						sys.renderer_device_ffp(),
						sge::graph::baseline(
							0.0),
						sge::graph::optional_axis_constraint(),
						sge::graph::color_schemes::bright()
					),
					fcppt::make_unique_ptr<
						sge::font::draw::static_text
					>(
						sys.renderer_device_ffp(),
						*font,
						sge::font::from_fcppt_string(
							fcppt::from_std_string(
								device
							)
						),
						sge::font::text_parameters(
							sge::font::align_h::variant(
								sge::font::align_h::left()
							)
						),
						sge::font::vector(
							0,
							y
						),
						sge::image::color::any::object{
							sge::image::color::predef::white()
						},
						sge::renderer::texture::emulate_srgb::yes
					)
				)
			)
		);

		device_totals[
			device
		] =
			::count_traffic(
				device
			);
	}

	auto const draw(
		[
			&cpugraph,
			&cpu_label,
			&device_map,
			&device_totals,
			&last_jiffies,
			&memgraph,
			&mem_label,
			&sys
		]{
			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			jiffies const current_jiffies{
				count_jiffies()
			};

			cpugraph.push(
				(
					current_jiffies
					-
					last_jiffies
				).work_percentage<
					sge::graph::scalar
				>()
			);

			last_jiffies =
				current_jiffies;

			cpugraph.render(
				scoped_block.get()
			);

			cpu_label.draw(
				scoped_block.get()
			);

			memgraph.push(
				count_memory()
			);

			memgraph.render(
				scoped_block.get()
			);

			mem_label.draw(
				scoped_block.get()
			);

			// network
			for(
				auto const &device
				:
				device_map
			)
			{
				unsigned long const traffic{
					::count_traffic(
						device.first
					)
				};

				device.second.get_graph().push(
					fcppt::cast::int_to_float<
						sge::graph::scalar
					>(
						traffic
						-
						device_totals[
							device.first
						]
					)
				);

				device_totals[
					device.first
				] = traffic;

				device.second.get_graph().render(
					scoped_block.get()
				);

				device.second.get_label().draw(
					scoped_block.get()
				);
			}
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
						}
					);
				}
			}
		);
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_function_context
)
try
{
	auto const parser(
		fcppt::options::apply(
			fcppt::options::argument<
				width_label,
				sge::window::dim::value_type
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("width")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("The graph width")
					}
				}
			},
			fcppt::options::argument<
				height_label,
				sge::window::dim::value_type
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("height")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("The graph height")
					}
				}
			}
		)
	);

	typedef
	decltype(
		parser
	)
	parser_type;

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				parser,
				fcppt::args_from_second(
					_function_context.argc(),
					_function_context.argv()
				)
			),
			[](
				fcppt::options::result<
					fcppt::options::result_of<
						parser_type
					>
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						-> awl::main::exit_code
						{
							awl::show_error(
								fcppt::output_to_fcppt_string(
									_error
								)
							);

							return
								awl::main::exit_failure();
						},
						[](
							fcppt::options::result_of<
								parser_type
							> const &_args
						)
						-> awl::main::exit_code
						{
							return
								main_program(
									fcppt::record::permute<
										arg_type
									>(
										_args
									)
								);
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				awl::show_message(
					fcppt::output_to_fcppt_string(
						_help_text
					)
				);

				return
					awl::main::exit_success();
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
