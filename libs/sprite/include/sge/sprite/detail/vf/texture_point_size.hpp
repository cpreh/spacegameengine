//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/renderer/vf/extra.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/find_with_texture_point_size.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/at.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace vf
{

template<
	typename Choices
>
struct texture_point_size
{
private:
	typedef
	typename
	sge::sprite::detail::config::texture_levels<
		Choices
	>::type
	texture_levels;

	typedef
	typename
	sge::sprite::detail::config::find_with_texture_point_size<
		Choices
	>::type
	with_texture_point_size;

	typedef
	typename
	with_texture_point_size::point_size
	point_size;

	template<
		typename Level
	>
	using
	make_size
	=
	sge::renderer::vf::extra<
		sge::renderer::vf::vector<
			typename
			Choices::type_choices::float_type,
			1
		>,
		brigand::at<
			typename
			point_size::attribute_indices,
			Level
		>
	>;
public:
	typedef
	sge::sprite::detail::transform_texture_levels_static<
		brigand::bind<
			make_size,
			brigand::_1
		>,
		texture_levels
	>
	type;
};

}
}
}
}

#endif
