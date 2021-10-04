//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_OPTIONS_HPP_INCLUDED

#include <sge/sprite/process/geometry_options_fwd.hpp>
#include <sge/sprite/process/options_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::process
{

template<
	sge::sprite::process::geometry_options GeometryOptions
>
struct options
{
	using
	geometry_options
	=
	std::integral_constant<
		sge::sprite::process::geometry_options,
		GeometryOptions
	>;
};

}

#endif
