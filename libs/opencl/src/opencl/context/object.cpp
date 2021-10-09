//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/config.hpp>
#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/platform/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/optional/maybe_void.hpp>
#if defined(SGE_OPENCL_HAVE_GLX)
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>
#elif defined(SGE_OPENCL_HAVE_WINDOWS)
#include <sge/src/include_windows.hpp>
#else
#error "Don't know what to include for opencl platform code"
#endif
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::opencl::context::object::object(opencl::context::parameters const &_params)
    : context_(nullptr), error_callback_(_params.error_callback())
{
  cl_int error_code{};

  fcppt::array::object<cl_context_properties, 7> props
  { // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(_params.platform().platform_id_),
        _params.shared_renderer().has_value() ? CL_GL_CONTEXT_KHR
                                              : static_cast<cl_context_properties>(0),
        _params.shared_renderer().has_value()
            ? reinterpret_cast<cl_context_properties>(
#if defined(SGE_OPENCL_HAVE_GLX)
                  // FIXME: This should not be here and must be returned from sge::opengl instead
                  glXGetCurrentContext()
#elif defined(SGE_OPENCL_HAVE_WINDOWS)
                  wglGetCurrentContext()
#else
#error "Don't know how to get the CL context"
#endif
                      )
            : static_cast<cl_context_properties>(0),
#if defined(SGE_OPENCL_HAVE_GLX)
        CL_GLX_DISPLAY_KHR,
        _params.shared_renderer().has_value()
            ? reinterpret_cast<cl_context_properties>(glXGetCurrentDisplay())
            : static_cast<cl_context_properties>(0),
#elif defined(SGE_OPENCL_HAVE_WINDOWS)
        CL_WGL_HDC_KHR,
        _params.shared_renderer().has_value()
            ? reinterpret_cast<cl_context_properties>(wglGetCurrentDC())
            : static_cast<cl_context_properties>(0),
#else
#error "Don't know how to get the CL display/hdc"
#endif
        0
  };

  using device_id_vector = std::vector<cl_device_id>;

  auto const devices(fcppt::algorithm::map<device_id_vector>(
      _params.device_refs(),
      [](fcppt::reference<sge::opencl::device::object> const _ref)
      { return _ref.get().device_id_; }));

  // TODO(philipp): Initialize this directly
  context_ = clCreateContext(
      props.data(),
      fcppt::cast::size<cl_uint>(devices.size()),
      devices.data(),
      &object::error_callback,
      // user data to the callback
      this,
      &error_code);

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateContext"));
}

cl_context sge::opencl::context::object::impl() const { return context_; }

sge::opencl::memory_object::image::format_sequence
sge::opencl::context::object::supported_planar_image_formats(cl_mem_flags const mem_flags) const
{
  cl_uint num_entries{};

  cl_int error_code = clGetSupportedImageFormats(
      context_, mem_flags, CL_MEM_OBJECT_IMAGE2D, 0, nullptr, &num_entries);

  opencl::impl::handle_error(
      error_code, FCPPT_TEXT("clGetSupportedImageFormats(number of formats)"));

  sge::opencl::memory_object::image::format_sequence result(
      static_cast<sge::opencl::memory_object::image::format_sequence::size_type>(num_entries));

  error_code = clGetSupportedImageFormats(
      context_, mem_flags, CL_MEM_OBJECT_IMAGE2D, num_entries, result.data(), nullptr);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetSupportedImageFormats(format list)"));

  return result;
}

sge::opencl::memory_object::image::format_sequence
sge::opencl::context::object::supported_volume_image_formats(cl_mem_flags const mem_flags) const
{
  cl_uint num_entries{};

  cl_int error_code = clGetSupportedImageFormats(
      context_, mem_flags, CL_MEM_OBJECT_IMAGE3D, 0, nullptr, &num_entries);

  opencl::impl::handle_error(
      error_code, FCPPT_TEXT("clGetSupportedImageFormats(number of formats)"));

  sge::opencl::memory_object::image::format_sequence result(
      static_cast<opencl::memory_object::image::format_sequence::size_type>(num_entries));

  error_code = clGetSupportedImageFormats(
      context_, mem_flags, CL_MEM_OBJECT_IMAGE3D, num_entries, result.data(), nullptr);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetSupportedImageFormats(format list)"));

  return result;
}

sge::opencl::context::object::~object()
{
  if (context_ == nullptr)
  {
    return;
  }

  cl_int const error_code = clReleaseContext(context_);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clReleaseContext"));
}

void sge::opencl::context::object::error_callback(
    char const *const _error_info_string,
    void const *const _bindata,
    size_t const _size_of_bindata,
    void *const _user_data)
{
  fcppt::optional::maybe_void(
      fcppt::cast::from_void_ptr<sge::opencl::context::object *>(_user_data)->error_callback_,
      [_error_info_string, _bindata, _size_of_bindata](
          sge::opencl::context::error_callback const &_error_callback)
      {
        _error_callback(
            sge::opencl::error_information_string(_error_info_string),
            sge::opencl::binary_error_data(
                fcppt::cast::from_void_ptr<unsigned char const *>(_bindata),
                fcppt::cast::from_void_ptr<unsigned char const *>(_bindata) + _size_of_bindata));
      });
}
