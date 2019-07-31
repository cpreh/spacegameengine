//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED

#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/size_choice.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/detail/primitives/normal_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	sge::sprite::config::texture_size_option TextureSize
>
struct normal_size final
:
	sge::sprite::config::size_choice
{
	typedef
	std::integral_constant<
		sge::sprite::config::texture_size_option,
		TextureSize
	>
	texture_option;

	template<
		typename Choices
	>
	struct apply
	:
	sge::sprite::detail::primitives::normal_size<
		Choices,
		TextureSize
	>
	{
	};
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
