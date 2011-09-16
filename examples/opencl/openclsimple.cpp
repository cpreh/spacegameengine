/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opencl/system.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <sge/opencl/command_queue/dim1.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/memory_object/image/format_output.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/memory_object/vertex_buffer.hpp>
#include <sge/opencl/memory_object/base_ref_sequence.hpp>
#include <sge/opencl/memory_object/scoped_objects.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/opengl/buffer/base_ptr.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/window.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/window/dim.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <limits>
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
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(scalar_quantity);
}

typedef
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector<sge::renderer::scalar,2>,
	tags::scalar_quantity
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
}

int
main()
try
{

	sge::opencl::system opencl_system;

	fcppt::io::cout << FCPPT_TEXT("Querying the number of available platforms...\n");

	sge::opencl::platform::object_sequence &platforms(
		opencl_system.platforms());

	if(platforms.empty())
	{
		fcppt::io::cerr << FCPPT_TEXT("Couldn't find any OpenCL platforms on your system.\n");
		return EXIT_FAILURE;
	}

	fcppt::io::cout << FCPPT_TEXT("Number of OpenCL platforms: ") << platforms.size() << FCPPT_TEXT("\n");
	fcppt::io::cout << FCPPT_TEXT("Platform listing begin:\n");
	fcppt::io::cout << FCPPT_TEXT("-----------------------\n");

	sge::opencl::platform::object_sequence::size_type platform_index = 0;
	for(
		sge::opencl::platform::object_sequence::const_iterator current_platform =
			platforms.begin();
		current_platform != platforms.end();
		++current_platform)
	{
		fcppt::io::cout << FCPPT_TEXT("\tPlatform ") << platform_index << FCPPT_TEXT(":\n");
		fcppt::io::cout
			<< FCPPT_TEXT("\tName: ")
			<< fcppt::from_std_string(
				current_platform->name()
			)
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("\tVendor: ")
			<< fcppt::from_std_string(
				current_platform->vendor()
			)
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("Profile type: ")
			<<
				(current_platform->profile() == sge::opencl::profile_type::full
				?
					fcppt::string(FCPPT_TEXT("full"))
				:
					fcppt::string(FCPPT_TEXT("embedded")))
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("\tVersion: ")
			<< current_platform->version().major_part()
			<< FCPPT_TEXT(".")
			<< current_platform->version().minor_part()
			<< FCPPT_TEXT("\n");

		if(!current_platform->version().platform_specific().empty())
			fcppt::io::cout
				<< FCPPT_TEXT("\tPlatform specific version info: ")
				<< fcppt::from_std_string(current_platform->version().platform_specific())
				<< FCPPT_TEXT("\n");

		fcppt::io::cout << FCPPT_TEXT("\tExtension list begin:\n");
		fcppt::io::cout << FCPPT_TEXT("\t*********************\n");
		fcppt::io::cout
			<< FCPPT_TEXT("\t\t")
			<<
				fcppt::from_std_string(
					boost::algorithm::join(
						current_platform->extensions(),
						std::string("\n\t\t")));
		fcppt::io::cout << FCPPT_TEXT("\r\t*********************\n");
		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
	}

	fcppt::io::cout << FCPPT_TEXT("Platform listing end\n");

	sge::opencl::platform::object_sequence::size_type chosen_platform_index;
	if(platforms.size() == 1)
	{
		chosen_platform_index = 0;
	}
	else
	{
		fcppt::io::cout << FCPPT_TEXT("Your choice: ");
		do
			chosen_platform_index =
				query_value_from_user<sge::opencl::platform::object_sequence::size_type>(
					fcppt::io::cin);
		while(chosen_platform_index >= platforms.size());
	}

	fcppt::io::cout << FCPPT_TEXT("List devices with properties? [y/n] ");

	fcppt::char_type list_devices;
	do
		list_devices =
			query_value_from_user<fcppt::char_type>(
				fcppt::io::cin);
	while(list_devices != FCPPT_TEXT('y') && list_devices != FCPPT_TEXT('n'));

	sge::opencl::platform::object &chosen_platform =
		platforms[chosen_platform_index];

	if(list_devices == FCPPT_TEXT('y'))
	{
		fcppt::io::cout
			<< FCPPT_TEXT("Number of devices on this platform: ")
			<< chosen_platform.devices().size()
			<< FCPPT_TEXT("\n");
		fcppt::io::cout << FCPPT_TEXT("Device listing begin:\n");
		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");

		for(
			sge::opencl::device::object_sequence::const_iterator current_device =
				chosen_platform.devices().begin();
			current_device != chosen_platform.devices().end();
			++current_device)
		{
			current_device->output_info(
				std::cout);
			fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
		}

		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
		fcppt::io::cout << FCPPT_TEXT("Device listing end\n");
	}

	fcppt::io::cout << FCPPT_TEXT("Creating sge::systems object...\n");

	sge::window::dim window_dim(1024,768);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("Simple OpenCL example"),
					window_dim)).dont_show())
		(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::center_on_resize(
					window_dim))));

	fcppt::io::cout << FCPPT_TEXT("Done. Creating a context with all devices on this platform...\n");

	sge::opencl::device::object_ref_sequence device_refs;
	for(
		sge::opencl::device::object_sequence::iterator current_device =
			chosen_platform.devices().begin();
		current_device != chosen_platform.devices().end();
		++current_device)
		device_refs.push_back(
			&(*current_device));

	sge::opencl::context::object main_context(
		sge::opencl::context::parameters(
			chosen_platform,
			device_refs)
			.share_with(
				sys.renderer())
			.error_callback(
				&opencl_error_callback));

	fcppt::io::cout << FCPPT_TEXT("Context created, listing available planar image formats (read/write)\n");

	sge::opencl::memory_object::image::format_sequence const planar_image_formats =
		main_context.supported_planar_image_formats(
			CL_MEM_READ_WRITE);

	for(
		sge::opencl::memory_object::image::format_sequence::const_iterator it =
			planar_image_formats.begin();
		it != planar_image_formats.end();
		++it)
	{
		sge::opencl::memory_object::image::format_output(
			std::cout,
			*it);

		std::cout << "\n";
	}

	fcppt::io::cout << FCPPT_TEXT("Listing available volume image formats (read/write)...\n");

	sge::opencl::memory_object::image::format_sequence const volume_image_formats =
		main_context.supported_volume_image_formats(
			CL_MEM_READ_WRITE);

	for(
		sge::opencl::memory_object::image::format_sequence::const_iterator it =
			volume_image_formats.begin();
		it != volume_image_formats.end();
		++it)
	{
		sge::opencl::memory_object::image::format_output(
			std::cout,
			*it);
		std::cout << "\n";
	}

	fcppt::io::cout << FCPPT_TEXT("Done, now creating a program...");

	sge::opencl::program::object main_program(
		main_context,
		fcppt::assign::make_container<sge::opencl::program::source_string_sequence>(
			std::string(
				"__kernel void hello_kernel("
				"__global float *input)"
				"{"
				"int gid = get_global_id(0);"
				"int lid = get_local_id(0);"
				"input[gid] = lid;"
				"}")));

	fcppt::io::cout << FCPPT_TEXT("Program created, building the program...\n");

	main_program.build(
		sge::opencl::program::build_parameters());

	fcppt::io::cout << FCPPT_TEXT("Program built, now creating a kernel...\n");

	sge::opencl::kernel::object main_kernel(
		main_program,
		sge::opencl::kernel::name(
			"hello_kernel"));

	fcppt::io::cout << FCPPT_TEXT("Kernel created, now creating a vertex buffer...\n");

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::renderer::vertex_buffer_ptr const vb(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::part_index(
				0u),
			static_cast<sge::renderer::size_type>(
				6),
			sge::renderer::resource_flags::readable));

	fcppt::io::cout << FCPPT_TEXT("Done, now creating OpenCL buffer from it\n");

	sge::opencl::memory_object::vertex_buffer cl_vb(
		main_context,
		*vb,
		sge::opencl::memory_object::renderer_buffer_lock_mode::write_only);

	main_kernel.argument(
		sge::opencl::kernel::argument_index(
			0u),
		cl_vb);

	fcppt::io::cout << FCPPT_TEXT("Done, now creating a command queue\n");

	sge::opencl::command_queue::object main_queue(
		*device_refs[0],
		main_context,
		sge::opencl::command_queue::execution_mode::in_order,
		sge::opencl::command_queue::profiling_mode::disabled);

	sge::opencl::memory_object::base_ref_sequence mem_objects;
	mem_objects.push_back(
		&cl_vb);

	fcppt::io::cout << FCPPT_TEXT("Done, now enqueueing kernel and running it\n");

	{
		sge::opencl::memory_object::scoped_objects scoped_vb(
			main_queue,
			mem_objects);

		sge::opencl::command_queue::dim1 global_dim;
		global_dim[0] = vb->size() * 2;

		sge::opencl::command_queue::dim1 local_dim;
		local_dim[0] = 2;

		sge::opencl::command_queue::enqueue_kernel(
			main_queue,
			main_kernel,
			global_dim,
			local_dim);
	}

	fcppt::io::cout << FCPPT_TEXT("Now locking the vb for reading and printing the values\n");

	{
		sge::renderer::scoped_vertex_lock scoped_vb(
			*vb,
			sge::renderer::lock_mode::readwrite);

		typedef
		sge::renderer::vf::view<vf::part>
		vertex_view;

		vertex_view const vertices(
			scoped_vb.value());

		for(
			vertex_view::iterator vb_it(
				vertices.begin());
			vb_it != vertices.end();
			vb_it++)
		{
			fcppt::io::cout << vb_it->get<vf::scalar_quantity>() << FCPPT_TEXT("\n");
		}
	}
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("fcppt::exception caught: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "std::exception caught: " << e.what() << "\n";
	return EXIT_FAILURE;
}
