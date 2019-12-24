//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_PART_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <sge/renderer/vf/to_label.hpp>
#include <sge/renderer/vf/to_packed_type.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <fcppt/metal/from_number_list.hpp>
#include <fcppt/metal/partial_sums.hpp>
#include <fcppt/metal/to_number_list.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename... Elements
>
struct part
{
	typedef
	metal::list<
		Elements...
	>
	elements;

	typedef
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
		elements
	>
	record_elements;

	typedef
	fcppt::metal::from_number_list<
		sge::renderer::vf::vertex_size,
		fcppt::metal::partial_sums<
			fcppt::metal::to_number_list<
				metal::transform<
					metal::lambda<
						sge::renderer::vf::detail::element_stride
					>,
					elements
				>
			>
		>
	>
	offsets;

	typedef
	metal::back<
		offsets
	>
	stride;
};

}
}
}

#endif
