//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DETAIL_ELEMENT_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_ELEMENT_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/to_label.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/index_of_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf::detail
{

template <typename Elements, typename Label>
using element_index = fcppt::mpl::list::index_of_if<
    Elements,
    fcppt::mpl::bind<
        fcppt::mpl::lambda<std::is_same>,
        fcppt::mpl::constant<Label>,
        fcppt::mpl::lambda<sge::renderer::vf::to_label>>>;

}

#endif
