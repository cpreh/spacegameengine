//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_IS_WITH_TRANSFORM_HPP_INCLUDED
#define SGE_SPRITE_STATE_IS_WITH_TRANSFORM_HPP_INCLUDED

#include <sge/sprite/state/with_transform_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename Type
>
struct is_with_transform
:
std::false_type
{
};

template<>
struct is_with_transform<
	sge::sprite::state::with_transform
>
:
std::true_type
{
};

}
}
}

#endif
