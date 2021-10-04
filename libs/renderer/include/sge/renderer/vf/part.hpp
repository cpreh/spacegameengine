//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_PART_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <sge/renderer/vf/detail/partial_sums.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/back.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sge::renderer::vf
{

template<
	typename... Elements
>
struct part
{
	using
	elements
	=
	fcppt::mpl::list::object<
		Elements...
	>;

	using
	offsets
	=
	sge::renderer::vf::detail::partial_sums<
		fcppt::mpl::list::map<
			elements,
			fcppt::mpl::lambda<
				sge::renderer::vf::detail::element_stride
			>
		>
	>;

	using
	stride
	=
	fcppt::mpl::list::back<
		offsets
	>;
};

}

#endif
