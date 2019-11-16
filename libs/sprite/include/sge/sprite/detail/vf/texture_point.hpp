//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED

#include <sge/sprite/detail/config/has_custom_texture_point_pos.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_size.hpp>
#include <sge/sprite/detail/vf/texture_point_pos.hpp>
#include <sge/sprite/detail/vf/texture_point_size.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/list/append.hpp>
#include <metal/list/list.hpp>
#include <metal/number/if.hpp>
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
struct texture_point
{
private:
	template<
		typename Type
	>
	using
	make_vector
	=
	metal::list<
		typename
		Type::type
	>;

	typedef
	metal::invoke<
		metal::if_<
			fcppt::metal::to_number<
				sge::sprite::detail::config::has_custom_texture_point_pos<
					Choices
				>
			>,
			metal::bind<
				metal::lambda<
					make_vector
				>,
				metal::always<
					sge::sprite::detail::vf::texture_point_pos<
						Choices
					>
				>
			>,
			metal::always<
				metal::list<>
			>
		>
	>
	vec1;

	template<
		typename Type
	>
	using
	append_size
	=
	metal::append<
		vec1,
		metal::list<
			typename
			Type::type
		>
	>;
public:
	typedef
	metal::invoke<
		metal::if_<
			fcppt::metal::to_number<
				sge::sprite::detail::config::has_custom_texture_point_size<
					Choices
				>
			>,
			metal::bind<
				metal::lambda<
					append_size
				>,
				metal::always<
					sge::sprite::detail::vf::texture_point_size<
						Choices
					>
				>
			>,
			metal::always<
				vec1
			>
		>
	>
	type;
};

}
}
}
}

#endif
