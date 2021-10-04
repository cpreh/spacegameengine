//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_FLOAT_TYPE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_FLOAT_TYPE_HPP_INCLUDED

#include <sge/sprite/config/float_type_fwd.hpp>


namespace sge::sprite::config
{

template<
	typename Type
>
struct float_type
{
	using
	type
	=
	Type;
};

}

#endif
