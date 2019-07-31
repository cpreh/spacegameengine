//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_OBJECT_BASE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_OBJECT_BASE_HPP_INCLUDED

#include <sge/sprite/detail/config/is_intrusive.hpp>
#include <sge/sprite/intrusive/detail/object_base_hook.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/types/empty_base.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
using object_base
=
std::conditional_t<
	sge::sprite::detail::config::is_intrusive<
		Choices
	>::value,
	sge::sprite::intrusive::detail::object_base_hook,
	brigand::empty_base
>;

}
}
}

#endif
