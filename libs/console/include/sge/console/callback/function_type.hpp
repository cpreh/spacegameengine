//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_FUNCTION_TYPE_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_FUNCTION_TYPE_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/object_ref.hpp>


namespace sge::console::callback
{

using
function_type
=
void(
	sge::console::arg_list const &,
	sge::console::object_ref
);

}

#endif
