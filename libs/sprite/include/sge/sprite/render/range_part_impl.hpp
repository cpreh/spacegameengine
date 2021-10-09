//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_RENDER_RANGE_PART_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_IMPL_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <sge/sprite/render/range_part_decl.hpp>
#include <sge/sprite/render/texture_ref.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Choices>
sge::sprite::render::range_part<Choices>::range_part(range_part_object _object)
    : object_(std::move(_object))
{
}

template <typename Choices>
sge::renderer::index::first sge::sprite::render::range_part<Choices>::first_index() const
{
  return fcppt::record::get<sge::sprite::buffers::roles::first_index>(object_);
}

template <typename Choices>
sge::renderer::vertex::first sge::sprite::render::range_part<Choices>::first_vertex() const
{
  return fcppt::record::get<sge::sprite::buffers::roles::first_vertex>(object_);
}

template <typename Choices>
sge::renderer::vertex::count sge::sprite::render::range_part<Choices>::vertex_count() const
{
  return fcppt::record::get<sge::sprite::detail::roles::vertex_count>(object_);
}

template <typename Choices>
sge::renderer::index::count sge::sprite::render::range_part<Choices>::index_count() const
{
  return fcppt::record::get<sge::sprite::detail::roles::index_count>(object_);
}

template <typename Choices>
template <sge::sprite::texture_level Level>
sge::sprite::render::texture_ref sge::sprite::render::range_part<Choices>::texture_level() const
{
  return fcppt::record::get<sge::sprite::detail::roles::texture<Level>>(object_);
}

#endif
