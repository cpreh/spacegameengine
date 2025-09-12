//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VERTICES_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VERTICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp> // IWYU pragma: keep
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer.hpp> // IWYU pragma: keep
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/is_vertex.hpp>
#include <sge/renderer/vf/iterator.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/proxy.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/algorithm/range_element_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ranges>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vertex
{

template <typename Format, typename Range>
sge::renderer::vertex::buffer_unique_ptr create_buffer_from_vertices(
    sge::renderer::device::core_ref const _device,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::renderer::resource_flags_field const &_resource_flags,
    Range const &_vertices)
{
  using vertex_type = std::remove_cvref_t<fcppt::algorithm::range_element_type<Range>>;

  static_assert(sge::renderer::vf::is_vertex<vertex_type>::value);

  using format_part = typename vertex_type::format_part;

  sge::renderer::vertex::buffer_unique_ptr buffer{
      _device.get().create_vertex_buffer(sge::renderer::vertex::buffer_parameters(
          _vertex_declaration,
          sge::renderer::vf::dynamic::make_part_index<Format, format_part>(),
          sge::renderer::vertex::count{std::ranges::size(_vertices)},
          _resource_flags))};

  sge::renderer::vertex::scoped_lock const lock{
      fcppt::make_ref(*buffer), sge::renderer::lock_mode::writeonly};

  using view = sge::renderer::vf::view<format_part>;

  view const dest{lock.value()};

  // TODO(philipp): Use ranges
  std::copy(std::ranges::begin(_vertices), std::ranges::end(_vertices), dest.begin());

  return buffer;
}

}

#endif
