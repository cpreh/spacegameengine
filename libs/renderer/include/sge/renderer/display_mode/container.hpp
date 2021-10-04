//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DISPLAY_MODE_CONTAINER_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_CONTAINER_HPP_INCLUDED

#include <sge/renderer/display_mode/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::display_mode
{

using
container
=
std::vector<
	sge::renderer::display_mode::object
>;

}

#endif
