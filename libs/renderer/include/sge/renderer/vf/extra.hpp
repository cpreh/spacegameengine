//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_EXTRA_HPP_INCLUDED
#define SGE_RENDERER_VF_EXTRA_HPP_INCLUDED

#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/extra_base.hpp>
#include <sge/renderer/vf/extra_fwd.hpp>
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/vector_fwd.hpp>
#include <mizuiro/color/format/homogenous_static_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vf
{

template<
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements,
	typename Index
>
struct extra<
	sge::renderer::vf::vector<
		Format,
		NumSubElements
	>,
	Index
>
:
sge::renderer::vf::extra_base<
	sge::renderer::vf::vector_base<
		Format,
		NumSubElements
	>,
	Index
>
{
	static_assert(
		std::is_fundamental<
			Format
		>::value,
		"Format must be fundamental"
	);

	static_assert(
		NumSubElements >= 1
		&& NumSubElements <= 4,
		"NumSubElements mut be between 1 and 4"
	);
};

template<
	typename ColorChannel,
	typename ColorLayout,
	typename Index
>
struct extra<
	mizuiro::color::format::homogenous_static<
		ColorChannel,
		ColorLayout
	>,
	Index
>
:
sge::renderer::vf::extra_base<
	sge::renderer::vf::color_base<
		mizuiro::color::format::homogenous_static<
			ColorChannel,
			ColorLayout
		>
	>,
	Index
>
{
};

}

#endif
