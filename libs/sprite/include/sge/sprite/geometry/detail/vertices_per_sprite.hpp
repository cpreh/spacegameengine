//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_VERTICES_PER_SPRITE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_VERTICES_PER_SPRITE_HPP_INCLUDED

#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/geometry/detail/count_constant.hpp>
#include <fcppt/not.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Choices, typename Enable = void>
struct vertices_per_sprite;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Choices>
struct vertices_per_sprite<
    Choices,
    std::enable_if_t<sge::sprite::detail::config::needs_index_buffer<Choices>::value>>
    : sge::sprite::geometry::detail::count_constant<4U>
{
};

template <typename Choices>
struct vertices_per_sprite<
    Choices,
    std::enable_if_t<fcppt::not_(sge::sprite::detail::config::needs_index_buffer<Choices>::value)>>
    : sge::sprite::geometry::detail::count_constant<1U>
{
};

FCPPT_PP_POP_WARNING

}

#endif
