//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DEREF_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DEREF_TEXTURE_HPP_INCLUDED

#include <fcppt/reference_fwd.hpp>
#include <fcppt/shared_ptr_fwd.hpp>
#include <fcppt/unique_ptr_fwd.hpp>


namespace sge::sprite
{

template<
	typename Type
>
inline
Type const &
deref_texture(
	fcppt::shared_ptr<
		Type
	> const &_value
)
{
	return
		*_value;

}

template<
	typename Type
>
inline
Type const &
deref_texture(
	fcppt::unique_ptr<
		Type
	> const &_value
)
{
	return
		*_value;

}

template<
	typename Type
>
inline
Type const &
deref_texture(
	fcppt::reference<
		Type
	> const &_value
)
{
	return
		_value.get();
}

}

#endif
