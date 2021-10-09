//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/cache.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>

sge::plugin::cache::cache() : plugins_() {}

sge::plugin::cache::~cache() = default;

void sge::plugin::cache::add(sge::plugin::library::object_shared_ptr const &_plugin)
{
  plugins_.push_back(_plugin);
}
