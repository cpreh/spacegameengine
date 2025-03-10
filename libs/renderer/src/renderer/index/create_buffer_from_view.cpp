//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp> // IWYU pragma: keep
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/index/buffer.hpp> // IWYU pragma: keep
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/create_buffer_from_view.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

sge::renderer::index::buffer_unique_ptr sge::renderer::index::create_buffer_from_view(
    sge::renderer::device::core_ref const _device,
    sge::renderer::index::dynamic::const_view const &_view,
    sge::renderer::resource_flags_field const &_resource_flags)
{
  sge::renderer::index::buffer_unique_ptr buffer(
      _device.get().create_index_buffer(sge::renderer::index::buffer_parameters(
          _view.format(), sge::renderer::index::count(_view.size()), _resource_flags)));

  sge::renderer::index::scoped_lock const lock(
      fcppt::make_ref(*buffer), sge::renderer::lock_mode::writeonly);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(
      lock.value().data(),
      _view.data(),
      sge::renderer::index::dynamic::format_stride(_view.format()) * _view.size());
FCPPT_PP_POP_WARNING

  return buffer;
}
