//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_SIZE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_SIZE_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/extra.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/find_with_texture_point_size.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
struct texture_point_size_impl
{
private:
	typedef
	sge::sprite::detail::config::texture_levels<
		Choices
	>
	texture_levels;

	typedef
	sge::sprite::detail::config::find_with_texture_point_size<
		Choices
	>
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
		metal::at<
			typename
			point_size::attribute_indices,
			fcppt::metal::to_number<
				Level
			>
		>
	>;
public:
	typedef
	sge::sprite::detail::transform_texture_levels_static<
		metal::lambda<
			make_size
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
