//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_IS_NORMAL_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_NORMAL_SIZE_HPP_INCLUDED

#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/texture_size_option_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename T
>
struct is_normal_size
:
std::false_type
{
};

template<
	sge::sprite::config::texture_size_option Option
>
struct is_normal_size<
	sge::sprite::config::normal_size<
		Option
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
