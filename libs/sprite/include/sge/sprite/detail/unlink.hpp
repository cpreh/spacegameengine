//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_UNLINK_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_UNLINK_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/destroy.hpp>
#include <sge/sprite/detail/config/is_intrusive.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
void
unlink(
	sge::sprite::object<
		Choices
	> &_this
)
{
	static_assert(
		sge::sprite::detail::config::is_intrusive<
			Choices
		>::value,
		"Sprite must be intrusive"
	);

	sge::sprite::detail::destroy(
		_this
	);

	_this.unlink();
}

}
}
}

#endif
