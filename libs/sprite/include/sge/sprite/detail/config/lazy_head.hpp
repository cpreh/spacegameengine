//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_LAZY_HEAD_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_LAZY_HEAD_HPP_INCLUDED

#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/front.hpp>

namespace sge::sprite::detail::config
{

template <template <typename> class Function, typename List>
using lazy_head = fcppt::mpl::bind<
    fcppt::mpl::lambda<Function>,
    fcppt::mpl::bind<fcppt::mpl::lambda<fcppt::mpl::list::front>, fcppt::mpl::constant<List>>>;

}

#endif
