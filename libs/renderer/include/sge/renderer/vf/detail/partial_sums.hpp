//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_PARTIAL_SUMS_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_PARTIAL_SUMS_HPP_INCLUDED

#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/mpl/add.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/back.hpp>
#include <fcppt/mpl/list/fold.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/push_back.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf::detail
{

template<
	typename Sequence
>
using
partial_sums
=
fcppt::mpl::list::fold<
	Sequence,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			fcppt::mpl::list::push_back
		>,
		fcppt::mpl::arg<2>,
		fcppt::mpl::bind<
			fcppt::mpl::lambda<
				fcppt::mpl::add
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					fcppt::mpl::list::back
				>,
				fcppt::mpl::arg<2>
			>,
			fcppt::mpl::arg<1>
		>
	>,
    fcppt::mpl::list::object<
		std::integral_constant<
			sge::renderer::vf::vertex_size,
			0U
		>
	>
>;

}

#endif
