//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED

#include <sge/systems/detail/is_with_renderer.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/list/index_of_if.hpp>

namespace sge::systems::detail
{

template <typename Choices>
using renderer_caps = typename fcppt::mpl::list::at<
    Choices,
    fcppt::mpl::list::
        index_of_if<Choices, fcppt::mpl::lambda<sge::systems::detail::is_with_renderer>>>::caps;

}

#endif
