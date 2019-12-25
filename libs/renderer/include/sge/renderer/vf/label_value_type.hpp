//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_LABEL_VALUE_TYPE_HPP_INCLUDED
#define SGE_RENDERER_VF_LABEL_VALUE_TYPE_HPP_INCLUDED

#include <sge/renderer/vf/detail/vertex.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Part,
	typename Label
>
using
label_value_type
=
fcppt::record::label_value_type<
	typename
	sge::renderer::vf::detail::vertex<
		Part
	>::type,
	Label
>;

}
}
}

#endif
