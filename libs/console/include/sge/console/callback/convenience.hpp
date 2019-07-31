//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_CONVENIENCE_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_CONVENIENCE_HPP_INCLUDED

#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/callback/short_description.hpp>
#include <sge/console/callback/detail/convenience_wrapper.hpp>


namespace sge
{
namespace console
{
namespace callback
{

template<
	typename FunctionType,
	typename Function
>
inline
sge::console::callback::parameters
convenience(
	Function const &_function,
	sge::console::callback::name const &_name,
	sge::console::callback::short_description const &_short_description
)
{
	return
		sge::console::callback::parameters(
			sge::console::callback::function{
				sge::console::callback::detail::convenience_wrapper<
					FunctionType
				>{
					_function,
					_short_description.get()
				}
			},
			_name
		)
		.short_description(
			_short_description.get()
		);
}

}
}
}

#endif
