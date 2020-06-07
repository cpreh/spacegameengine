//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_VERTEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_VERTEX_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <sge/renderer/vf/to_label.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


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
		metal::transform<
			metal::bind<
				metal::lambda<
					fcppt::record::element
				>,
				metal::lambda<
					sge::renderer::vf::to_label
				>,
				metal::lambda<
					sge::renderer::vf::to_packed_type
				>
			>,
			metal::list<
				Elements...
			>
		>
	>;
};

}
}
}
}

#endif
