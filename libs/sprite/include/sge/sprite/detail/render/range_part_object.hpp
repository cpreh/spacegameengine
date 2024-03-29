//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_RANGE_PART_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_RANGE_PART_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/detail/render/make_textures.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail::render
{

template <typename Choices>
struct range_part_object
{
private:
  using first_vertex_role = fcppt::record::
      element<sge::sprite::buffers::roles::first_vertex, sge::renderer::vertex::first>;

  using first_index_role =
      fcppt::record::element<sge::sprite::buffers::roles::first_index, sge::renderer::index::first>;

  using vertex_count_role = fcppt::record::
      element<sge::sprite::detail::roles::vertex_count, sge::renderer::vertex::count>;

  using index_count_role =
      fcppt::record::element<sge::sprite::detail::roles::index_count, sge::renderer::index::count>;

  using base_types = fcppt::mpl::list::object<first_vertex_role, vertex_count_role>;

  using indexed_types = fcppt::mpl::list::
      append<base_types, fcppt::mpl::list::object<first_index_role, index_count_role>>;

  using geometry_types = std::conditional_t<
      sge::sprite::detail::config::needs_index_buffer<Choices>::value,
      indexed_types,
      base_types>;

public:
  using type = fcppt::record::from_list<fcppt::mpl::list::append<
      geometry_types,
      typename sge::sprite::detail::render::make_textures<Choices>::type>>;
};

}

#endif
