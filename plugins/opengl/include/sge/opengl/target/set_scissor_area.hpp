//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_SET_SCISSOR_AREA_HPP_INCLUDED
#define SGE_OPENGL_TARGET_SET_SCISSOR_AREA_HPP_INCLUDED

#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/target/scissor_area_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

void
set_scissor_area(
	sge::renderer::target::scissor_area const &,
	sge::renderer::screen_unit
);

}
}
}

#endif
