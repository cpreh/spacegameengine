//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_LOOP_HPP_INCLUDED
#define SGE_WINDOW_LOOP_HPP_INCLUDED

#include <sge/window/loop_function.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/window/detail/symbol.hpp>
#include <awl/main/exit_code.hpp>


namespace sge::window
{

SGE_WINDOW_DETAIL_SYMBOL
awl::main::exit_code
loop(
	sge::window::system &, // NOLINT(google-runtime-references)
	sge::window::loop_function const &
);

}

#endif
