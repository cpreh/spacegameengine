//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_ERROR_CALLBACK_HPP_INCLUDED
#define SGE_CONSOLE_ERROR_CALLBACK_HPP_INCLUDED

#include <sge/console/error_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace console
{

using
error_callback
=
fcppt::function<
	sge::console::error_function
>;

}
}

#endif
