//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_EVENT_COMBINER_HPP_INCLUDED
#define SGE_WINDOW_EVENT_COMBINER_HPP_INCLUDED

#include <sge/window/detail/symbol.hpp>
#include <awl/event/container.hpp>


namespace sge
{
namespace window
{

SGE_WINDOW_DETAIL_SYMBOL
awl::event::container
event_combiner(
	awl::event::container &&,
	awl::event::container &&
);

}
}

#endif
