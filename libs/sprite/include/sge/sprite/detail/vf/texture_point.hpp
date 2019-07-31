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
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/back.hpp>
#include <brigand/sequences/list.hpp>
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
	struct make_vector
	{
		typedef
		brigand::list<
			typename
			Type::type
		>
		type;
	};

	typedef
	typename
	brigand::eval_if<
		sge::sprite::detail::config::has_custom_texture_point_pos<
			Choices
		>,
		brigand::apply<
			brigand::bind<
				make_vector,
				brigand::pin<
					sge::sprite::detail::vf::texture_point_pos<
						Choices
					>
				>
			>
		>,
		brigand::identity<
			brigand::list<>
		>
	>::type
	vec1;

	template<
		typename Type
	>
	using
	append_size
	=
	brigand::push_back<
		vec1,
		brigand::list<
			typename
			Type::type
		>
	>;
public:
	typedef
	typename
	brigand::eval_if<
		sge::sprite::detail::config::has_custom_texture_point_size<
			Choices
		>,
		brigand::apply<
			brigand::bind<
				append_size,
				brigand::pin<
					sge::sprite::detail::vf::texture_point_size<
						Choices
					>
				>
			>
		>,
		brigand::identity<
			vec1
		>
	>::type
	type;
};

}
}
}
}

#endif
