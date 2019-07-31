//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_IS_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_IS_OPTIONS_HPP_INCLUDED

#include <sge/sprite/process/geometry_options_fwd.hpp>
#include <sge/sprite/process/options_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename T
>
struct is_options
:
std::false_type
{
};

template<
	sge::sprite::process::geometry_options GeometryOptions
>
struct is_options<
	sge::sprite::process::options<
		GeometryOptions
	>
>
:
std::true_type
{
};

}
}
}

#endif
