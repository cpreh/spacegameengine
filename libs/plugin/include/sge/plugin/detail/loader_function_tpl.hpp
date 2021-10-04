//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_DETAIL_LOADER_FUNCTION_TPL_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_LOADER_FUNCTION_TPL_HPP_INCLUDED

#include <fcppt/log/context_reference_fwd.hpp>


namespace sge::plugin::detail
{

template<
	typename Type
>
struct loader_function_tpl;

template<
	typename Result,
	typename... Args
>
struct loader_function_tpl<
	Result (
		Args...
	)
>
{
	using
	type
	=
	Result (
		fcppt::log::context_reference,
		Args...
	);
};

}

#endif
