//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_NORMAL_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_NORMAL_SIZE_HPP_INCLUDED

#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/types/dim_fwd.hpp>
#include <sge/sprite/types/size_or_texture_size_fwd.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	sge::sprite::config::texture_size_option
>
struct normal_size;

template<
	typename Choices
>
struct normal_size<
	Choices,
	sge::sprite::config::texture_size_option::never
>
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::size,
			sge::sprite::types::dim<
				typename
				Choices::type_choices
			>
		>
	>
	type;
};

template<
	typename Choices
>
struct normal_size<
	Choices,
	sge::sprite::config::texture_size_option::always
>
{
	typedef
	metal::list<>
	type;
};

template<
	typename Choices
>
struct normal_size<
	Choices,
	sge::sprite::config::texture_size_option::maybe
>
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::size_or_texture_size,
			sge::sprite::types::size_or_texture_size<
				typename
				Choices::type_choices
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
