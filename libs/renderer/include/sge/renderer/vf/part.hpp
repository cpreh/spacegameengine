//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_PART_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/detail/element_stride.hpp>
#include <fcppt/brigand/partial_sums.hpp>
#include <fcppt/type_traits/is_brigand_sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename ElementList
>
struct part
{
	typedef
	ElementList
	elements;

	static_assert(
		fcppt::type_traits::is_brigand_sequence<
			ElementList
		>::value,
		"ElementList must be a brigand sequence"
	);

	typedef
	brigand::transform<
		elements,
		brigand::bind<
			sge::renderer::vf::detail::element_stride,
			brigand::_1
		>
	>
	strides;

	typedef
	fcppt::brigand::partial_sums<
		strides,
		sge::renderer::vf::vertex_size
	>
	offsets;

};

}
}
}

#endif
