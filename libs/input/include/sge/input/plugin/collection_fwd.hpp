//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_PLUGIN_COLLECTION_FWD_HPP_INCLUDED
#define SGE_INPUT_PLUGIN_COLLECTION_FWD_HPP_INCLUDED

#include <sge/input/system_fwd.hpp>
#include <sge/plugin/collection_fwd.hpp>


namespace sge
{
namespace input
{
namespace plugin
{

typedef
sge::plugin::collection<
	sge::input::system
>
collection;

}
}
}

#endif
