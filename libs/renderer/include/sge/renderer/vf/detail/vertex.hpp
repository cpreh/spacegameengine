//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_VERTEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_VERTEX_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <sge/renderer/vf/to_label.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

template<
	typename Type
>
struct vertex;

template<
	typename... Elements
>
struct vertex<
	sge::renderer::vf::part<
		Elements...
	>
>
{
	using
	type
	=
	fcppt::record::from_list<
		fcppt::mpl::list::map<
			fcppt::mpl::list::object<
				Elements...
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					fcppt::record::element
				>,
				fcppt::mpl::lambda<
					sge::renderer::vf::to_label
				>,
				fcppt::mpl::lambda<
					sge::renderer::vf::to_packed_type
				>
			>
		>
	>;
};

}
}
}
}

#endif
