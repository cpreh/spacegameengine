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
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/at.hpp>


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
	using
	texture_levels
	=
	sge::sprite::detail::config::texture_levels<
		Choices
	>;

	using
	with_texture_point_size
	=
	sge::sprite::detail::config::find_with_texture_point_size<
		Choices
	>;

	using
	point_size
	=
	typename
	with_texture_point_size::point_size;

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
		fcppt::mpl::list::at<
			typename
			point_size::attribute_indices,
			Level
		>
	>;
public:
	using
	type
	=
	sge::sprite::detail::transform_texture_levels_static<
		fcppt::mpl::lambda<
			make_size
		>,
		texture_levels
	>;
};

}
}
}
}

#endif
