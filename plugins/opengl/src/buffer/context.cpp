//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/buffer/context.hpp>
#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/is_native.hpp>
#include <sge/opengl/buffer/optional_hardware_config.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::context::context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      hardware_config_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{
                  5U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              })
              ? sge::opengl::buffer::optional_hardware_config(sge::opengl::buffer::hardware_config(
                    sge::opengl::buffer::is_native{true},
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLGENBUFFERSPROC>(
                            _info.load_function("glGenBuffers"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLDELETEBUFFERSPROC>(
                            _info.load_function("glDeleteBuffers"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBINDBUFFERPROC>(
                            _info.load_function("glBindBuffer"))),
                    sge::opengl::deref_fun_ptr(sge::opengl::info::cast_function<PFNGLMAPBUFFERPROC>(
                        _info.load_function("glMapBuffer"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLUNMAPBUFFERPROC>(
                            _info.load_function("glUnmapBuffer"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBUFFERDATAPROC>(
                            _info.load_function("glBufferData"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBUFFERSUBDATAPROC>(
                            _info.load_function("glBufferSubData"))),
                    sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range(
                        sge::opengl::deref_fun_ptr(
                            sge::opengl::info::cast_function<PFNGLMAPBUFFERRANGEPROC>(
                                _info.load_function("glMapBufferRange"))))))
          : sge::opengl::info::extension_supported(
                _info.extensions(), sge::opengl::info::extension{"GL_ARB_vertex_buffer_object"})
              ? sge::opengl::buffer::optional_hardware_config(sge::opengl::buffer::hardware_config(
                    sge::opengl::buffer::is_native{false},
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLGENBUFFERSPROC>(
                            _info.load_function("glGenBuffersARB"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLDELETEBUFFERSPROC>(
                            _info.load_function("glDeleteBuffersARB"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBINDBUFFERPROC>(
                            _info.load_function("glBindBufferARB"))),
                    sge::opengl::deref_fun_ptr(sge::opengl::info::cast_function<PFNGLMAPBUFFERPROC>(
                        _info.load_function("glMapBufferARB"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLUNMAPBUFFERPROC>(
                            _info.load_function("glUnmapBufferARB"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBUFFERDATAPROC>(
                            _info.load_function("glBufferDataARB"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBUFFERSUBDATAPROC>(
                            _info.load_function("glBufferSubDataARB"))),
                    sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range()))
              : sge::opengl::buffer::optional_hardware_config())
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::context::~context() = default;

sge::opengl::buffer::optional_hardware_config const &
sge::opengl::buffer::context::hardware_config() const
{
  return hardware_config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::buffer::context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
