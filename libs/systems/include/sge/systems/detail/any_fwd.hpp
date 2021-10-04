//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ANY_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ANY_FWD_HPP_INCLUDED

#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge::systems::detail
{

using
any
=
fcppt::variant::object<
	sge::systems::config,
	sge::systems::window,
	sge::systems::detail::renderer,
	sge::systems::image2d,
	sge::systems::audio_loader,
	sge::systems::audio_player,
	sge::systems::input,
	sge::systems::font
>;

}

#endif
