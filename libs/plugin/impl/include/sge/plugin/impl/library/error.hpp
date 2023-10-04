//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_LIBRARY_ERROR_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_ERROR_HPP_INCLUDED

#include <fcppt/optional_string.hpp>

namespace sge::plugin::impl::library
{

[[nodiscard]] fcppt::optional_string error();

}

#endif
