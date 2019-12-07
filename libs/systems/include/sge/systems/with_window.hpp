//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WITH_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_WINDOW_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

struct with_window
{
	typedef
	std::true_type
	needs_init;

	typedef
	sge::systems::window
	parameter_type;

	typedef
	metal::list<>
	needs_before;
};

}
}

#endif
