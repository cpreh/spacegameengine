//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_HAS_WITH_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_HAS_WITH_RENDERER_HPP_INCLUDED

#include <sge/systems/detail/is_with_renderer.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/any_of.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices
>
using
has_with_renderer
=
fcppt::mpl::list::any_of<
	Choices,
	fcppt::mpl::lambda<
		sge::systems::detail::is_with_renderer
	>
>;

}
}
}

#endif
