//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/render/range_part_fwd.hpp> // IWYU pragma: keep
#include <sge/sprite/render/texture_ref_fwd.hpp>

namespace sge::sprite::render
{

template <typename Choices>
class range_part
{
public:
  using range_part_object = typename sge::sprite::detail::render::range_part_object<Choices>::type;

  explicit range_part(range_part_object);

  [[nodiscard]] sge::renderer::index::first first_index() const;

  [[nodiscard]] sge::renderer::vertex::first first_vertex() const;

  [[nodiscard]] sge::renderer::vertex::count vertex_count() const;

  [[nodiscard]] sge::renderer::index::count index_count() const;

  template <sge::sprite::texture_level Level>
  [[nodiscard]] sge::sprite::render::texture_ref texture_level() const;

private:
  range_part_object object_;
};

}

#endif
