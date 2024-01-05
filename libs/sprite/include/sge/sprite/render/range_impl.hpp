//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/render/range_decl.hpp> // IWYU pragma: export
#include <sge/sprite/render/range_part_impl.hpp> // IWYU pragma: keep
#include <fcppt/make_cref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Choices>
sge::sprite::render::range<Choices>::range() : object_(), range_parts_()
{
}

template <typename Choices>
sge::sprite::render::range<Choices>::range(
    range_object const &_object, range_part_vector &&_range_parts)
    : object_(fcppt::make_cref(_object)), range_parts_(std::move(_range_parts))
{
}

template <typename Choices>
sge::sprite::render::range<Choices>::range(range &&) noexcept = default;

template <typename Choices>
sge::sprite::render::range<Choices> &
sge::sprite::render::range<Choices>::operator=(range &&) noexcept = default;

namespace sge::sprite::render
{
template <typename Choices>
range<Choices>::~range() = default;
}

template <typename Choices>
typename sge::sprite::render::range<Choices>::optional_object const &
sge::sprite::render::range<Choices>::object() const
{
  return object_;
}

template <typename Choices>
typename sge::sprite::render::range<Choices>::range_part_vector const &
sge::sprite::render::range<Choices>::parts() const
{
  return range_parts_;
}

#endif
