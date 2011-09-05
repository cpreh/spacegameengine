#include <sge/opencl/system.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/opengl/buffer/base_ptr.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/resource_flags_none.hpp>
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
#include <sge/renderer/opengl/glinclude.hpp>
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
			stream.widen('\n'));
		std::cerr << "before next iteration\n";
	}
	return result;
}

namespace vf
{
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(scalar_quantity)
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
			<< current_platform->name()
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("\tVendor: ")
			<< current_platform->vendor()
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

	fcppt::io::cout << FCPPT_TEXT("Context created, now creating a vertex buffer...\n");

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
			sge::renderer::resource_flags::none));

	fcppt::io::cout << FCPPT_TEXT("Vertex buffer created...Finishing up\n");

	glFinish();

	fcppt::io::cout << FCPPT_TEXT("Done, now creating OpenCL buffer from it\n");

	cl_int error_code;
	cl_mem cl_buffer =
		clCreateFromGLBuffer(
			main_context.impl(),
			CL_MEM_WRITE_ONLY,
			fcppt::dynamic_pointer_cast<sge::renderer::opengl::buffer::base>(
				vb)->id().get(),
			&error_code);

	fcppt::io::cout << FCPPT_TEXT("Done.\n");

	if(error_code != CL_SUCCESS)
		return EXIT_FAILURE;

	clReleaseMemObject(
		cl_buffer);
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
