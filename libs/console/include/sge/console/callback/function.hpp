//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_FUNCTION_HPP_INCLUDED

#include <sge/console/callback/function_type.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace console
{
namespace callback
{

typedef
fcppt::function<
	sge::console::callback::function_type
>
function;

}
}
}

#endif
