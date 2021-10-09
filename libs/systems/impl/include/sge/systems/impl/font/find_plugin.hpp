//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_FONT_FIND_PLUGIN_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_FONT_FIND_PLUGIN_HPP_INCLUDED

#include <sge/font/plugin/collection_fwd.hpp>
#include <sge/font/plugin/object.hpp>
#include <sge/systems/font_fwd.hpp>

namespace sge::systems::impl::font
{

sge::font::plugin::object
find_plugin(sge::font::plugin::collection const &, sge::systems::font const &);

}

#endif
