//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LIBRARY_IS_FUNCTION_PTR_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_IS_FUNCTION_PTR_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::plugin::impl::library
{

template<
	typename Function
>
using
is_function_ptr
=
std::is_function<
	typename
	std::remove_pointer<
		Function
	>::type
>;

}

#endif
