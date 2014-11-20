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


#include <sge/log/global_context.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/dim1.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/command_queue/scoped.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/base_ref_sequence.hpp>
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <sge/opencl/memory_object/scoped_objects.hpp>
#include <sge/opencl/memory_object/image/format_output.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/platform/profile_type.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/title.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/activate_levels_recursive.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename T,typename Char,typename Traits>
T const
query_value_from_user(
	std::basic_istream<Char,Traits> &stream)
{
	T result;
	while(!(stream >> result))
	{
		if(stream.eof())
			throw fcppt::exception(FCPPT_TEXT("Couldn't read value, EOF was reached first."));
		stream.clear();
		stream.ignore(
			std::numeric_limits<std::streamsize>::max(),
			Traits::to_int_type(
				stream.widen('\n')));
		std::cerr << "before next iteration\n";
	}
	return result;
}

namespace vf
{
typedef
sge::renderer::vf::pos
<
	sge::renderer::scalar,
	2u
>
scalar_quantity;

typedef
sge::renderer::vf::part
<
	boost::mpl::vector1<vf::scalar_quantity>
>
part;

typedef
sge::renderer::vf::format
<
	boost::mpl::vector1<vf::part>
>
format;
}

void
opencl_error_callback(
	sge::opencl::error_information_string const &errinfo,
	sge::opencl::binary_error_data const &)
{
	std::cerr << "Got an OpenCL error: " << errinfo << "\n";
}

void
program_build_finished(
	volatile bool &finished)
{
	std::cerr << "Program build finished\n";
	finished = true;
}
}

int
main()
try
{
	fcppt::log::activate_levels_recursive(
		sge::log::global_context(),
		sge::opencl::log_location(),
		fcppt::log::level::verbose);

	sge::opencl::system opencl_system;

	fcppt::io::cout()
		<< FCPPT_TEXT("Querying the number of available platforms...\n");

	sge::opencl::platform::object_sequence &platforms(
		opencl_system.platforms());

	if(platforms.empty())
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Couldn't find any OpenCL platforms on your system.\n");
		return EXIT_FAILURE;
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Number of OpenCL platforms: ") << platforms.size() << FCPPT_TEXT("\n")
		<< FCPPT_TEXT("Platform listing begin:\n")
		<< FCPPT_TEXT("-----------------------\n");

	sge::opencl::platform::object_sequence::size_type platform_index = 0;
	for(
		sge::opencl::platform::object const &current_platform
		:
		platforms
	)
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("\tPlatform ")
			<< platform_index++
			<< FCPPT_TEXT(":\n")
			<< FCPPT_TEXT("\tName: ")
			<< fcppt::from_std_string(
				current_platform.name()
			)
			<< FCPPT_TEXT("\n")
			<< FCPPT_TEXT("\tVendor: ")
			<< fcppt::from_std_string(
				current_platform.vendor()
			)
			<< FCPPT_TEXT("\n")
			<< FCPPT_TEXT("Profile type: ")
			<<
				(current_platform.profile() == sge::opencl::platform::profile_type::full
				?
					fcppt::string(FCPPT_TEXT("full"))
				:
					fcppt::string(FCPPT_TEXT("embedded")))
			<< FCPPT_TEXT("\n")
			<< FCPPT_TEXT("\tVersion: ")
			<< current_platform.version().major_part()
			<< FCPPT_TEXT(".")
			<< current_platform.version().minor_part()
			<< FCPPT_TEXT("\n");

		if(!current_platform.version().platform_specific().empty())
			fcppt::io::cout()
				<< FCPPT_TEXT("\tPlatform specific version info: ")
				<< fcppt::from_std_string(current_platform.version().platform_specific())
				<< FCPPT_TEXT("\n");

		fcppt::io::cout()
			<< FCPPT_TEXT("\tExtension list begin:\n")
			<< FCPPT_TEXT("\t*********************\n")
			<< FCPPT_TEXT("\t\t")
			<<
				fcppt::from_std_string(
					boost::algorithm::join(
						current_platform.extensions(),
						std::string("\n\t\t")))
			<< FCPPT_TEXT("\r\t*********************\n")
			<< FCPPT_TEXT("-----------------------\n");
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Platform listing end\n");

	sge::opencl::platform::object_sequence::size_type chosen_platform_index;
	if(platforms.size() == 1)
	{
		chosen_platform_index = 0;
	}
	else
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("Your choice: ");
		do
			chosen_platform_index =
				query_value_from_user<sge::opencl::platform::object_sequence::size_type>(
					fcppt::io::cin());
		while(chosen_platform_index >= platforms.size());
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("List devices with properties? [y/n] ");

	fcppt::char_type list_devices;
	do
		list_devices =
			query_value_from_user<fcppt::char_type>(
				fcppt::io::cin());
	while(list_devices != FCPPT_TEXT('y') && list_devices != FCPPT_TEXT('n'));

	sge::opencl::platform::object &chosen_platform =
		platforms[chosen_platform_index];

	if(list_devices == FCPPT_TEXT('y'))
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("Number of devices on this platform: ")
			<< chosen_platform.devices().size()
			<< FCPPT_TEXT('\n')
			<< FCPPT_TEXT("Device listing begin:\n")
			<< FCPPT_TEXT("-----------------------\n");

		for(
			sge::opencl::device::object const &current_device
			:
			chosen_platform.devices()
		)
		{
			current_device.output_info(
				std::cout);
			fcppt::io::cout()
				<< FCPPT_TEXT("-----------------------\n");
		}

		fcppt::io::cout()
			<< FCPPT_TEXT("-----------------------\n")
			<< FCPPT_TEXT("Device listing end\n");
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Creating sge::systems object...\n");

	sge::window::dim const window_dim(1024,768);

	sge::systems::instance<
		boost::mpl::vector2<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::core
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::original_window(
					sge::window::title(
						FCPPT_TEXT("Simple OpenCL example")
					)
				)
			).dont_show())
		(sge::systems::renderer(
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
				sge::viewport::center_on_resize(
					window_dim))));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done. Creating a context with all devices on this platform...\n");

	sge::opencl::device::object_ref_sequence device_refs;
	for(
		sge::opencl::device::object &current_device
		:
		chosen_platform.devices()
	)
		device_refs.push_back(
			&current_device);

	sge::opencl::context::object main_context(
		sge::opencl::context::parameters(
			chosen_platform,
			device_refs)
			.share_with(
				sys.renderer_device_core())
			.error_callback(
				&opencl_error_callback));

	fcppt::io::cout()
		<< FCPPT_TEXT("Context created, listing available planar image formats (read/write)\n");

	sge::opencl::memory_object::image::format_sequence const planar_image_formats =
		main_context.supported_planar_image_formats(
			CL_MEM_READ_WRITE);

	for(
		auto const format
		:
		planar_image_formats
	)
	{
		sge::opencl::memory_object::image::format_output(
			std::cout,
			format
		);

		std::cout << '\n';
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Listing available volume image formats (read/write)...\n");

	sge::opencl::memory_object::image::format_sequence const volume_image_formats =
		main_context.supported_volume_image_formats(
			CL_MEM_READ_WRITE);

	for(
		auto const format
		:
		volume_image_formats
	)
	{
		sge::opencl::memory_object::image::format_output(
			std::cout,
			format
		);

		std::cout << '\n';
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, now creating a program...");

	sge::opencl::program::object main_program(
		main_context,
		sge::opencl::program::source_string_sequence{
			std::string(
				"__kernel void hello_kernel("
				"float const multiplier,"
				"__global float *input)"
				"{"
				"int gid = get_global_id(0);"
				"int lid = get_local_id(0);"
				"input[gid] = lid * multiplier;"
				"}"
			)
		},
		sge::opencl::program::optional_build_parameters());

	fcppt::io::cout()
		<< FCPPT_TEXT("Program created, building the program...\n");

	volatile bool build_finished =
		false;

	main_program.build(
		sge::opencl::program::build_parameters()
			.notification_callback(
				std::bind(
					&program_build_finished,
					std::ref(
						build_finished))));

	std::cout << "Waiting for build completion\n";
	while(!build_finished)
		std::cout << "Build not finished yet\n";

	fcppt::io::cout()
		<< FCPPT_TEXT("Program built, now creating a kernel...\n");

	sge::opencl::kernel::object main_kernel(
		main_program,
		sge::opencl::kernel::name(
			"hello_kernel"));

	fcppt::io::cout()
		<< FCPPT_TEXT("Kernel created, now creating a vertex buffer...\n");

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_core().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<vf::format>())));

	sge::renderer::vertex::buffer_unique_ptr const vb(
		sys.renderer_device_core().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					vf::format,
					vf::part
				>(),
				sge::renderer::vertex::count(
					6u),
				sge::renderer::resource_flags_field{
					sge::renderer::resource_flags::readable})));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, now creating OpenCL buffer from it\n");

	sge::opencl::memory_object::buffer cl_vb(
		main_context,
		*vb,
		sge::opencl::memory_object::renderer_buffer_lock_mode::write_only);

	main_kernel.argument(
		sge::opencl::kernel::argument_index(
			1u),
		cl_vb);

	main_kernel.argument(
		sge::opencl::kernel::argument_index(
			0u),
		static_cast<cl_float>(
			2.0));

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, now creating a command queue\n");

	sge::opencl::command_queue::object main_queue(
		*device_refs[0],
		main_context,
		sge::opencl::command_queue::execution_mode::out_of_order,
		sge::opencl::command_queue::profiling_mode::disabled);

	fcppt::io::cout()
		<< FCPPT_TEXT("Done, now enqueueing kernel and running it\n");

	{
		sge::opencl::memory_object::scoped_objects scoped_vb(
			main_queue,
			sge::opencl::memory_object::base_ref_sequence{
				(&cl_vb)
			}
		);

		sge::opencl::command_queue::enqueue_kernel(
			main_queue,
			main_kernel,
			sge::opencl::command_queue::global_dim1(
				sge::opencl::dim1(
					vb->size().get() * 2u)),
			sge::opencl::command_queue::local_dim1(
				sge::opencl::dim1(
					2u)),
			sge::opencl::event::sequence());
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Now locking the vb for reading and printing the values\n");

	{
		sge::renderer::vertex::scoped_lock const scoped_vb(
			*vb,
			sge::renderer::lock_mode::readwrite);

		typedef
		sge::renderer::vf::view<vf::part>
		vertex_view;

		vertex_view const vertices(
			scoped_vb.value());

		for(
			auto const &vertex
			:
			vertices
		)
		{
			fcppt::io::cout()
				<< vertex.get<vf::scalar_quantity>()
				<< FCPPT_TEXT('\n');
		}
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("Done\n");
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
