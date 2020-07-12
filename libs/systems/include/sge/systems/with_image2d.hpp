//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_WITH_IMAGE2D_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_IMAGE2D_HPP_INCLUDED

#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/with_image2d_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

struct with_image2d
{
	using
	needs_init
	=
	std::true_type;

	using
	parameter_type
	=
	sge::systems::image2d;

	using
	needs_before
	=
	metal::list<>;
};

}
}

#endif
