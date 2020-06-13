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
#include <metal.hpp>
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
	using
	with_texture_list
	=
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_texture
	>;

	using
	with_texture_point_size_list
	=
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_texture_point_size
	>;
public:
	using
	type
	=
	std::conditional_t<
		std::is_same_v<
			with_texture_list,
			metal::list<>
		>,
		with_texture_point_size_list,
		with_texture_list
	>;
};

}
}
}
}

#endif
