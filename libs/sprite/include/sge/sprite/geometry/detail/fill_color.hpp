//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_COLOR_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_COLOR_HPP_INCLUDED

#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/labels/color.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_color.hpp>
#include <sge/sprite/geometry/detail/count.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>
#include <fcppt/not.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Iterator, typename Choices>
inline std::enable_if_t<sge::sprite::detail::config::has_color<Choices>::value, void>
fill_color(Iterator _iterator, sge::sprite::object<Choices> const &_sprite)
{
  fcppt::algorithm::repeat(
      sge::sprite::geometry::detail::vertices_per_sprite<Choices>::value,
      [&_iterator, &_sprite]
      {
        sge::renderer::vf::set_proxy(
            *_iterator, sge::renderer::vf::labels::color{}, _sprite.color());

        ++_iterator;
      });
}

template <typename Iterator, typename Choices>
inline std::enable_if_t<fcppt::not_(sge::sprite::detail::config::has_color<Choices>::value), void>
fill_color(Iterator, sge::sprite::object<Choices> const &)
{
}

}

#endif
