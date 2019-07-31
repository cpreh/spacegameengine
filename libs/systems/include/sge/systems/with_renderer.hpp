//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WITH_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_RENDERER_HPP_INCLUDED

#include <sge/systems/renderer_caps_fwd.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/with_renderer_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	sge::systems::renderer_caps Caps
>
struct with_renderer
{
	typedef
	std::integral_constant<
		sge::systems::renderer_caps,
		Caps
	>
	caps;

	typedef
	std::true_type
	needs_init;

	typedef
	sge::systems::renderer
	parameter_type;

	typedef
	brigand::list<
		sge::systems::with_window
	>
	needs_before;
};

}
}

#endif
