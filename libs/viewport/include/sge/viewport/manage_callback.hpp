//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_MANAGE_CALLBACK_HPP_INCLUDED
#define SGE_VIEWPORT_MANAGE_CALLBACK_HPP_INCLUDED

#include <sge/viewport/manage_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::viewport
{

using manage_callback = fcppt::function<sge::viewport::manage_function>;

}

#endif
