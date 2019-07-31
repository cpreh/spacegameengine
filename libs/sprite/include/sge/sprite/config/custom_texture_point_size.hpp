//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_CUSTOM_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_CUSTOM_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/custom_texture_point_size_fwd.hpp>
#include <fcppt/type_traits/is_brigand_sequence.hpp>
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
	typename AttributeNames
>
struct custom_texture_point_size
{
	typedef
	std::true_type
	is_texture_point_size;

	static_assert(
		fcppt::type_traits::is_brigand_sequence<
			AttributeNames
		>::value,
		"AttributeNames must be an mpl sequence"
	);

	typedef
	AttributeNames
	attribute_indices;
};

}
}
}

#endif
