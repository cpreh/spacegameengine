//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_EXTRACT_PARAMETER_TYPE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_EXTRACT_PARAMETER_TYPE_HPP_INCLUDED


namespace sge::systems::detail
{

template<
	typename Type
>
using
extract_parameter_type
=
typename
Type::parameter_type;

}

#endif
