//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_MAP_HPP_INCLUDED
#define SGE_WLINPUT_MAP_HPP_INCLUDED

#include <awl/backends/wayland/registry_id.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput
{

template <typename Object>
using map = std::unordered_map<awl::backends::wayland::registry_id, fcppt::shared_ptr<Object>>;

}

#endif
