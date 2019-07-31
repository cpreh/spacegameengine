//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED

#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/bind.hpp>
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
struct texpos
{
private:
	template<
		typename Level
	>
	using
	make_pos
	=
	sge::renderer::vf::texpos<
		typename
		Choices::type_choices::float_type,
		2,
		sge::renderer::vf::index<
			Level::value
		>
	>;
public:
	typedef
	sge::sprite::detail::transform_texture_levels_static<
		brigand::bind<
			make_pos,
			brigand::_1
		>,
		typename
		sge::sprite::detail::config::texture_levels<
			Choices
		>::type
	>
	type;
};

}
}
}
}

#endif
