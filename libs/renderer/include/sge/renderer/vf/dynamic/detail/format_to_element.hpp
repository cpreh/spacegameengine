//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/detail/element_c.hpp>


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
	typename Type
>
struct format_to_element;

#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(\
	type_arg,\
	value_arg\
)\
template<>\
struct format_to_element<\
	type_arg\
>\
:\
sge::renderer::vf::dynamic::detail::element_c<\
	sge::renderer::vf::dynamic::element_type::value_arg\
>\
{\
}

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	float,
	float_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	double,
	double_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	char,
	byte
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned char,
	ubyte
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	short,
	short_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned short,
	ushort
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	int,
	int_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned,
	uint
);

#undef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT

}
}
}
}
}

#endif
