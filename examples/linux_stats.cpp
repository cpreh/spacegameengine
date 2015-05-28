/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <array>
#include <example_main.hpp>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <type_traits>
#include <utility>
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
		total_type);

	FCPPT_MAKE_STRONG_TYPEDEF(
		value_type,
		work_type);

	jiffies(
		total_type const &_total,
		work_type const &_work)
	:
		total_(
			_total),
		work_(
			_work)
	{
	}

	total_type const
	total() const
	{
		return
			total_;
	}

	work_type const
	work() const
	{
		return
			work_;
	}

	jiffies const
	operator-(
		jiffies const &_other) const
	{
		return
			jiffies(
				this->total() - _other.total(),
				this->work() - _other.work());
	}

	template<typename Float>
	typename
	boost::enable_if
	<
		std::is_floating_point<Float>,
		Float
	>::type
	work_percentage() const
	{
		if(!total_.get())
			return
				static_cast<Float>(
					0.0f);

		return
			static_cast<Float>(
				work_.get()) /
			static_cast<Float>(
				total_.get()) *
			static_cast<Float>(
				100.0f);
	}
private:
	total_type total_;
	work_type work_;
};

// Source: http://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-c
jiffies const
count_jiffies()
{
	std::ifstream cpuinfo(
		"/proc/stat");

	FCPPT_ASSERT_ERROR(
		cpuinfo.is_open());

	std::string first_word;
	cpuinfo >> first_word;

	FCPPT_ASSERT_ERROR(
		first_word == "cpu");

	typedef
	std::array<jiffies::value_type,7u>
	jiffies_array;

	jiffies_array current_jiffies;

	for(
		auto &jiffie : current_jiffies
	)
		if(!(cpuinfo >> jiffie))
			std::terminate();

	return
		jiffies(
			jiffies::total_type(
				std::accumulate(
					current_jiffies.begin(),
					current_jiffies.end(),
					0u)),
			jiffies::work_type(
				std::accumulate(
					current_jiffies.begin(),
					current_jiffies.begin() + 3,
					0u)));
}

struct
graph_with_label
{

	graph_with_label(
		fcppt::unique_ptr<sge::graph::object> _graph,
		fcppt::unique_ptr<sge::font::draw::static_text> _label)
	:
	graph_(
		std::move(_graph)),
	label_(
		std::move(_label))
	{}

	sge::graph::object &
	get_graph() const
	{
		return *graph_;
	}

	sge::font::draw::static_text &
	get_label() const
	{
		return *label_;
	}

	fcppt::unique_ptr<sge::graph::object> graph_;
	fcppt::unique_ptr<sge::font::draw::static_text> label_;
};

double
count_memory()
{
	std::ifstream meminfo(
		"/proc/meminfo");

	FCPPT_ASSERT_ERROR(
		meminfo.is_open());

	unsigned
		total = 0,
		free = 0,
		buffers = 0,
		cached = 0,
		slab = 0;

	std::string first_word, last_word;
	unsigned value;

	while(
		(meminfo >> first_word >> value).ignore(
			std::numeric_limits<std::streamsize>::max(),
			'\n'))
	{
		if (first_word == "MemTotal:")
			total = value;
		else if (first_word == "MemFree:")
			free = value;
		else if (first_word == "Buffers:")
			buffers = value;
		else if (first_word == "Cached:")
			cached = value;
		else if (first_word == "Slab:")
			slab = value;
	}

	unsigned used = total - free - buffers - cached - slab;
	FCPPT_ASSERT_ERROR(
		total > 0);
	return
		100.0 *
		static_cast<double>(used) /
		static_cast<double>(total);
}

std::vector<
	std::string
>
network_devices()
{
	std::ifstream netinfo(
		"/proc/net/dev");

	FCPPT_ASSERT_ERROR(
		netinfo.is_open());

	std::vector<
		std::string
	> result;

	// skip the first two lines
	netinfo.ignore(
		std::numeric_limits<std::streamsize>::max(),
		'\n');
	netinfo.ignore(
		std::numeric_limits<std::streamsize>::max(),
		'\n');

	std::string device;
	while(
		(netinfo >> device).ignore(
			std::numeric_limits<std::streamsize>::max(),
			'\n'))
	{
		if (device != "lo:")
			result.push_back(
				std::string(device.begin(), device.end() - 1u));
	}

	return result;
}

unsigned long
count_traffic(
	std::string const &_device)
{
	std::ifstream netinfo(
		"/proc/net/dev");

	FCPPT_ASSERT_ERROR(
		netinfo.is_open());

	std::vector<
		std::string
	> result;

	// skip the first two lines
	netinfo.ignore(
		std::numeric_limits<std::streamsize>::max(),
		'\n');
	netinfo.ignore(
		std::numeric_limits<std::streamsize>::max(),
		'\n');

	std::string device;
	unsigned long value;
	while(
		(netinfo >> device >> value).ignore(
			std::numeric_limits<std::streamsize>::max(),
			'\n'))
	{
		if (device == _device + ':')
			return value;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context)
try
{
	count_memory();
	if(_context.argc() <= 3)
	{
		std::cerr
			<< "Usage: "
			<<
				_context.argv()[0]
			<<
				" <frames-per-second> <width> <height>\n";

		return
			awl::main::exit_failure();
	}

	sge::timer::scoped_frame_limiter::ticks_per_second const desired_fps(
		fcppt::extract_from_string_exn<sge::timer::scoped_frame_limiter::ticks_per_second>(
			std::string(
				_context.argv()[1])));

	sge::window::dim const graph_dim(
		fcppt::extract_from_string_exn<sge::window::dim::value_type>(
			std::string(
				_context.argv()[2])),
		fcppt::extract_from_string_exn<sge::window::dim::value_type>(
			std::string(
				_context.argv()[3])));

	std::vector<std::string> devices = ::network_devices();
	std::size_t network_device_count = devices.size();

	std::map<std::string, unsigned long> device_totals;

	sge::systems::instance<
		boost::mpl::vector3<
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
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("linux stats example")
					)
				).size_hints(
					sge::window::size_hints{}
					.minimum_size_hint(
						sge::window::dim{
							graph_dim.w(),
							static_cast<
								sge::window::dim::value_type
							>(
								2u + network_device_count
							) * graph_dim.h()
						}
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
				sge::viewport::fill_on_resize()
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
			sge::font::align_h::left()
		),
		sge::font::vector(
			0,
			0
		),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::font::draw::static_text mem_label(
		sys.renderer_device_ffp(),
		*font,
		SGE_FONT_LIT(
			"mem"
		),
		sge::font::text_parameters(
			sge::font::align_h::left()
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
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::yes
	);

	sge::graph::object cpugraph(
		sge::graph::position(
			sge::renderer::vector2(
				0.0f,
				0.0f)),
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
				100.0)),
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
			50.0),
		sge::graph::optional_axis_constraint(
			sge::graph::axis_constraint(
				0.0,
				100.0)),
		sge::graph::color_schemes::default_()
	);

	jiffies last_jiffies =
		count_jiffies();

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

		sge::font::unit y(
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
		);

		device_map.insert(
			std::make_pair(
				device,
				graph_with_label(
					fcppt::make_unique_ptr_fcppt<
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
					fcppt::make_unique_ptr_fcppt<
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
							sge::font::align_h::left()
						),
						sge::font::vector(
							0,
							y
						),
						sge::image::color::predef::white(),
						sge::renderer::texture::emulate_srgb::yes
					)
				)
			)
		);

		device_totals[device] =
			::count_traffic(device);
	}

	while(
		sys.window_system().poll()
	)
	{
		sge::timer::scoped_frame_limiter limiter(
			desired_fps);

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		jiffies const current_jiffies =
			count_jiffies();
		cpugraph.push(
			(current_jiffies - last_jiffies).work_percentage<sge::graph::scalar>());
		last_jiffies =
			current_jiffies;
		cpugraph.render(
			scoped_block.get()
		);
		cpu_label.draw(
			scoped_block.get()
		);

		memgraph.push(
			count_memory());
		memgraph.render(
			scoped_block.get()
		);
		mem_label.draw(
			scoped_block.get()
		);

		// network
		for (
			auto const &device
			:
			device_map
		)
		{
			unsigned long traffic = ::count_traffic(device.first);

			(device.second).get_graph().push(
				static_cast<double>(
					traffic -
					device_totals[device.first]
				)
			);

			device_totals[device.first] = traffic;

			(device.second).get_graph().render(
				scoped_block.get());

			(device.second).get_label().draw(
				scoped_block.get());
		}

	}

	return sys.window_system().exit_code();
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr() << e.string() << FCPPT_TEXT("\n");
	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr << _error.what() << '\n';
	return awl::main::exit_failure();
}
