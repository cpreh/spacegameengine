#include <sge/opencl/single_device_system.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/loader.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/opencl/command_queue/dim2.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/all_extensions.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <iostream>
#include <ostream>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

int
main(
	int argc,
	char *argv[])
try
{
	if(argc == 1)
	{
		fcppt::io::cout << FCPPT_TEXT("This program creates an image in OpenCL and writes it to a png file on disk.\n\n");
		fcppt::io::cout << FCPPT_TEXT("Usage: ") << fcppt::from_std_string(argv[0]) << FCPPT_TEXT(" <png-image-file-name>\n");
		return EXIT_FAILURE;
	}

	fcppt::filesystem::path const target_file_name(
		fcppt::from_std_string(
			argv[1]));

	fcppt::io::cout << FCPPT_TEXT("Creating opencl system\n");

	sge::opencl::single_device_system opencl_system(
		0);

	fcppt::io::cout << FCPPT_TEXT("Done, creating planar image\n");

	cl_image_format image_format;
	image_format.image_channel_order = CL_RGBA;
	image_format.image_channel_data_type = CL_UNORM_INT8;

	std::size_t image_size = 64;

	sge::opencl::memory_object::image::planar image(
		opencl_system.context(),
		CL_MEM_READ_WRITE,
		image_format,
		sge::opencl::memory_object::dim2(
			image_size,
			image_size),
		sge::opencl::memory_object::image::planar_pitch(
			0));

	fcppt::io::cout << FCPPT_TEXT("Done, creating systems object\n");

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions)));

	fcppt::io::cout << FCPPT_TEXT("Done, creating program\n");

	sge::opencl::program::object main_program(
		opencl_system.context(),
		fcppt::assign::make_container<sge::opencl::program::source_string_sequence>(
			fcppt::io::stream_to_string(
				*fcppt::make_unique_ptr<fcppt::io::cifstream>(
					sge::config::media_path() / FCPPT_TEXT("kernels") / FCPPT_TEXT("texture.cl")))));

	fcppt::io::cout << FCPPT_TEXT("Program created, building the program...\n");

	main_program.build(
		sge::opencl::program::build_parameters());

	fcppt::io::cout << FCPPT_TEXT("Program built, now creating a kernel...\n");

	sge::opencl::kernel::object main_kernel(
		main_program,
		sge::opencl::kernel::name(
			"hello_kernel"));

	main_kernel.argument(
		sge::opencl::kernel::argument_index(
			0),
		image);

	fcppt::io::cout << FCPPT_TEXT("Kernel created, executing it\n");

	sge::opencl::command_queue::enqueue_kernel(
		opencl_system.queue(),
		main_kernel,
		fcppt::assign::make_array<sge::opencl::command_queue::dim2::value_type>
			(image_size)(image_size).container(),
		fcppt::assign::make_array<sge::opencl::command_queue::dim2::value_type>
			(static_cast<std::size_t>(1))(static_cast<std::size_t>(1)).container());

	fcppt::io::cout << FCPPT_TEXT("Done, now creating an image file from the image in memory...\n");

	std::cout << image.size() << "\n";

	sge::opencl::command_queue::scoped_planar_mapping scoped_image(
		opencl_system.queue(),
		image,
		CL_MAP_READ,
		sge::opencl::memory_object::rect(
			sge::opencl::memory_object::rect::vector::null(),
			image.size()));

	sys.image_loader().loaders().at(0)->create(
		sge::image2d::view::to_const(
			scoped_image.view()))->save(
		target_file_name);
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
