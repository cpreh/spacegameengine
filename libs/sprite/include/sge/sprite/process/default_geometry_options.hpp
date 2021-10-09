//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_PROCESS_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/process/do_default_sort.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <fcppt/not.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::process
{

template <typename Choices, typename Compare, typename Enable = void>
struct default_geometry_options;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Choices, typename Compare>
struct default_geometry_options<
    Choices,
    Compare,
    std::enable_if_t<sge::sprite::detail::process::do_default_sort<Choices, Compare>::value>>
    : std::integral_constant<
          sge::sprite::process::geometry_options,
          sge::sprite::process::geometry_options::sort_and_update>
{
};

template <typename Choices, typename Compare>
struct default_geometry_options<
    Choices,
    Compare,
    std::enable_if_t<fcppt::not_(
        sge::sprite::detail::process::do_default_sort<Choices, Compare>::value)>>
    : std::integral_constant<
          sge::sprite::process::geometry_options,
          sge::sprite::process::geometry_options::update>
{
};

FCPPT_PP_POP_WARNING

}

#endif
