//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_WINDOW_DEMUXER_REF_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_WINDOW_DEMUXER_REF_HPP_INCLUDED

#include <sge/x11input/event/window_demuxer_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::x11input::event
{

using window_demuxer_ref = fcppt::reference<sge::x11input::event::window_demuxer>;

}

#endif
