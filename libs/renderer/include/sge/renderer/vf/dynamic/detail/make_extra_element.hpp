//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_EXTRA_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_EXTRA_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/dynamic/detail/make_color.hpp>
#include <sge/renderer/vf/dynamic/detail/make_vector.hpp>
#include <mizuiro/color/format/homogenous_static_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements
>
inline
sge::renderer::vf::dynamic::vector
make_extra_element(
	sge::renderer::vf::vector<
		Format,
		NumSubElements
	> const &
)
{
	return
		sge::renderer::vf::dynamic::detail::make_vector<
			Format,
			NumSubElements
		>();
}

template<
	typename ColorChannel,
	typename ColorLayout
>
inline
sge::renderer::vf::dynamic::color
make_extra_element(
	mizuiro::color::format::homogenous_static<
		ColorChannel,
		ColorLayout
	> const  &
)
{
	return
		sge::renderer::vf::dynamic::detail::make_color<
			mizuiro::color::format::homogenous_static<
				ColorChannel,
				ColorLayout
			>
		>();
}

}
}
}
}
}

#endif
