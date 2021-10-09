//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_view.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

sge::renderer::vertex::buffer_unique_ptr sge::renderer::vertex::create_buffer_from_view(
    sge::renderer::device::core_ref const _device,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::renderer::vf::dynamic::const_view const &_view,
    sge::renderer::resource_flags_field const &_resource_flags)
{
  sge::renderer::vertex::buffer_unique_ptr buffer(
      _device.get().create_vertex_buffer(sge::renderer::vertex::buffer_parameters(
          _vertex_declaration,
          _view.part_index(),
          sge::renderer::vertex::count(_view.size()),
          _resource_flags)));

  sge::renderer::vertex::scoped_lock const lock(
      fcppt::make_ref(*buffer), sge::renderer::lock_mode::writeonly);

  std::memcpy(lock.value().data(), _view.data(), _view.part().stride().get() * _view.size().get());

  return buffer;
}
