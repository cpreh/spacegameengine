//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_TO_PACKED_TYPE_HPP_INCLUDED
#define SGE_RENDERER_VF_TO_PACKED_TYPE_HPP_INCLUDED


namespace sge::renderer::vf
{

template<
	typename Type
>
using
to_packed_type
=
typename
Type::packed_type;

}

#endif
