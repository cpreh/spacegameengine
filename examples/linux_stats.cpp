/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/graph/background_color.hpp>
#include <sge/graph/baseline.hpp>
#include <sge/graph/foreground_color.hpp>
#include <sge/graph/object.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/log/global.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <example_main.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <numeric>
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
		boost::is_floating_point<Float>,
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
	fcppt::container::array<jiffies::value_type,7u>
	jiffies_array;

	jiffies_array current_jiffies;

	for(
		jiffies_array::iterator it =
			current_jiffies.begin();
		it != current_jiffies.end();
		++it)
		if(!(cpuinfo >> (*it)))
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
}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_context)
try
{
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

	sge::window::dim const window_dim(
		fcppt::extract_from_string_exn<sge::window::dim::value_type>(
			std::string(
				_context.argv()[2])),
		fcppt::extract_from_string_exn<sge::window::dim::value_type>(
			std::string(
				_context.argv()[3])));

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("graph example")
					),
					window_dim)))
		(sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()))
	);

	sge::graph::object graph(
		sge::graph::position(
			sge::renderer::vector2(
				0.0f,
				0.0f)),
		fcppt::math::dim::structure_cast<sge::image2d::dim>(
			window_dim),
		sys.renderer(),
		sge::graph::foreground_color(
			sge::image::colors::white()),
		sge::graph::background_color(
			sge::image::colors::darkslategray()),
		sge::graph::baseline(
			50.0),
		sge::graph::optional_axis_constraint(
			sge::graph::axis_constraint(
				0.0,
				100.0)));

	jiffies last_jiffies =
		count_jiffies();


	while(
		sys.window_system().poll()
	)
	{
		sge::timer::scoped_frame_limiter limiter(
			desired_fps);

		sge::renderer::context::scoped const scoped_block(
			sys.renderer(),
			sys.renderer().onscreen_target()
		);

		jiffies const current_jiffies =
			count_jiffies();
		graph.push(
			(current_jiffies - last_jiffies).work_percentage<sge::graph::scalar>());
		last_jiffies =
			current_jiffies;

		graph.render(
			scoped_block.get()
		);

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
