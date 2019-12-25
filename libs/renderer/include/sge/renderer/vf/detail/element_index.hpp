//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_ELEMENT_INDEX_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_ELEMENT_INDEX_HPP_INCLUDED

#include <sge/renderer/vf/to_label.hpp>
#include <fcppt/metal/index_of_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
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
	typename Elements,
	typename Label
>
using
element_index
=
fcppt::metal::index_of_if<
	Elements,
	metal::bind<
		metal::trait<
			std::is_same
		>,
		metal::always<
			Label
		>,
		metal::lambda<
			sge::renderer::vf::to_label
		>
	>
>;

}
}
}
}

#endif
