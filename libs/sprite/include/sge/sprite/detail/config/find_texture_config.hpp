//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_FIND_TEXTURE_CONFIG_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_FIND_TEXTURE_CONFIG_HPP_INCLUDED

#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/detail/config/find_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
struct find_texture_config
{
private:
	typedef
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_texture
	>
	with_texture_list;

	typedef
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_texture_point_size
	>
	with_texture_point_size_list;
public:
	typedef
	std::conditional_t<
		std::is_same<
			with_texture_list,
			brigand::list<>
		>::value,
		with_texture_point_size_list,
		with_texture_list
	>
	type;
};

}
}
}
}

#endif
