//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_LOOP_FUNCTION_HPP_INCLUDED
#define SGE_WINDOW_LOOP_FUNCTION_HPP_INCLUDED

#include <awl/event/base_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace window
{

typedef
fcppt::function<
	void (
		awl::event::base const &
	)
>
loop_function;

}
}

#endif
