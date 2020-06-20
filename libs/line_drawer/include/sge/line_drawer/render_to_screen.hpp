//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LINE_DRAWER_RENDER_TO_SCREEN_HPP_INCLUDED
#define SGE_LINE_DRAWER_RENDER_TO_SCREEN_HPP_INCLUDED

#include <sge/line_drawer/object_fwd.hpp>
#include <sge/line_drawer/detail/symbol.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>


namespace sge
{
namespace line_drawer
{

SGE_LINE_DRAWER_DETAIL_SYMBOL
void
render_to_screen(
	sge::renderer::device::ffp &, // NOLINT(google-runtime-references)
	sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
	sge::line_drawer::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}

#endif
