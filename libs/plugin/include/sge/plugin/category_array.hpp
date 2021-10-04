//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CATEGORY_ARRAY_HPP_INCLUDED
#define SGE_PLUGIN_CATEGORY_ARRAY_HPP_INCLUDED

#include <sge/plugin/context_base_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::plugin
{

using
category_array
=
std::vector<
	sge::plugin::context_base_ref
>;

}

#endif
