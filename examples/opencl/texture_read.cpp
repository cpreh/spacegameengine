//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/media_path.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/dim2.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/scoped.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/single_device_system/object.hpp>
#include <sge/opencl/single_device_system/parameters.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

void main_program(std::filesystem::path const &_target_file_path)
{
  fcppt::io::cout() << FCPPT_TEXT("Creating systems object\n");

  sge::systems::instance<sge::systems::with_image2d> const sys(
      sge::systems::make_list(sge::systems::image2d(sge::media::all_extensions())));

  fcppt::io::cout() << FCPPT_TEXT("Done, creating opencl system\n");

  // Mind the extra parens
  sge::opencl::single_device_system::object opencl_system{
      sys.log_context(),
      sge::opencl::single_device_system::parameters().execution_mode(
          sge::opencl::command_queue::execution_mode::out_of_order)};

  fcppt::io::cout() << FCPPT_TEXT("Done, creating planar image\n");

  cl_image_format image_format;
  image_format.image_channel_order = CL_RGBA;
  image_format.image_channel_data_type = CL_UNORM_INT8;

  sge::opencl::dim2 const image_size(
      512U, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      512U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  sge::opencl::memory_object::image::planar image(
      fcppt::make_ref(opencl_system.context()),
      sge::opencl::memory_object::flags_field{
          sge::opencl::memory_object::flags::read, sge::opencl::memory_object::flags::write},
      image_format,
      image_size,
      sge::opencl::memory_object::image::planar_pitch(0U));

  fcppt::io::cout() << FCPPT_TEXT("Done, creating program\n");

  sge::opencl::program::object main_program(
      sys.log_context(),
      fcppt::make_ref(opencl_system.context()),
      sge::opencl::program::file_to_source_string_sequence(
          sge::config::media_path() / FCPPT_TEXT("kernels") / FCPPT_TEXT("texture.cl")),
      sge::opencl::program::optional_build_parameters());

  fcppt::io::cout() << FCPPT_TEXT("Program created, building the program...\n");

  main_program.build(sge::opencl::program::build_parameters());

  fcppt::io::cout() << FCPPT_TEXT("Program built, now creating a kernel...\n");

  sge::opencl::kernel::object main_kernel(
      fcppt::make_ref(main_program), sge::opencl::kernel::name("hello_kernel"));

  main_kernel.argument(
      sge::opencl::kernel::argument_index(0U),
      fcppt::reference_to_base<sge::opencl::memory_object::base>(fcppt::make_ref(image)));

  fcppt::io::cout() << FCPPT_TEXT("Kernel created, executing it\n");

  sge::opencl::command_queue::scoped scoped_queue(fcppt::make_ref(opencl_system.command_queue()));

  sge::opencl::event::sequence events{fcppt::container::make<sge::opencl::event::sequence>(
      sge::opencl::command_queue::enqueue_kernel(
          fcppt::make_ref(opencl_system.command_queue()),
          fcppt::make_ref(main_kernel),
          sge::opencl::command_queue::global_dim2(image_size),
          sge::opencl::event::sequence()))};

  fcppt::io::cout() << FCPPT_TEXT("Done, now creating an image file from the image in memory...\n");

  sge::opencl::command_queue::scoped_planar_mapping scoped_image(
      fcppt::make_ref(opencl_system.command_queue()),
      fcppt::make_ref(image),
      sge::opencl::command_queue::map_flags::read,
      sge::opencl::memory_object::rect(
          fcppt::math::vector::null<sge::opencl::memory_object::rect::vector>(), image.size()),
      events);

  sge::image2d::save_from_view(
      sys.image_system(), sge::image2d::view::to_const(scoped_image.view()), _target_file_path);

  opencl_system.update();
}

FCPPT_RECORD_MAKE_LABEL(path_label);

}

int FCPPT_MAIN(int argc, fcppt::args_char *argv[])
try
{
  auto const parser(fcppt::options::argument<path_label, fcppt::string>{
      fcppt::options::long_name{FCPPT_TEXT("png-image-file-path")},
      fcppt::options::optional_help_text{}});

  return fcppt::either::match(
      fcppt::options::parse(parser, fcppt::args_from_second(argc, argv)),
      [](fcppt::options::error const &_error)
      {
        fcppt::io::cerr() << FCPPT_TEXT("This program creates an image in OpenCL and writes it to "
                                        "a png file on disk.\n\n")
                          << _error << FCPPT_TEXT('\n');

        return EXIT_FAILURE;
      },
      [](fcppt::options::result_of<decltype(parser)> const &_result)
      {
        main_program(std::filesystem::path{fcppt::record::get<path_label>(_result)});

        return EXIT_SUCCESS;
      });
}
catch (fcppt::exception const &_error)
{
  fcppt::io::cerr() << _error.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cerr << _error.what() << '\n';

  return EXIT_FAILURE;
}
