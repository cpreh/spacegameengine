//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/context.hpp>
#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/make_hardware.hpp>
#include <sge/opengl/buffer/make_software.hpp>
#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/context/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::pbo_context::pbo_context(sge::opengl::context::object_ref const _context)
    : sge::opengl::context::base(),
      buffers_(fcppt::optional::maybe( // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
          sge::opengl::context::use<sge::opengl::buffer::context>(_context, _context.get().info())
              .hardware_config(),
          [] { return sge::opengl::buffer::make_software<buffer_array>(); },
          [&_context](sge::opengl::buffer::hardware_config const &_config)
          {
            sge::opengl::info::context const &info(_context.get().info());

            return sge::opengl::info::
                           version_at_least( // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
                               info.version(),
                               sge::opengl::info::major_version{2U},
                               sge::opengl::info::minor_version{1U})
                       ? sge::opengl::buffer::make_hardware(
                             fcppt::make_cref(_config),
                             GL_PIXEL_PACK_BUFFER,
                             GL_PIXEL_UNPACK_BUFFER)
                   : sge::opengl::info::
                           extension_supported( // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
                               info.extensions(),
                               sge::opengl::info::extension{"GL_ARB_pixel_buffer_object"})
                       ? sge::opengl::buffer::make_hardware(
                             fcppt::make_cref(_config),
                             GL_PIXEL_PACK_BUFFER_ARB,
                             GL_PIXEL_UNPACK_BUFFER_ARB)
                       : sge::opengl::buffer::make_software<buffer_array>();
          }))
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::pbo_context::~pbo_context() = default;

sge::opengl::buffer::base &sge::opengl::buffer::pbo_context::pack_buffer() const
{
  return *fcppt::array::get<0>(buffers_);
}

sge::opengl::buffer::base &sge::opengl::buffer::pbo_context::unpack_buffer() const
{
  return *fcppt::array::get<1>(buffers_);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::buffer::pbo_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
