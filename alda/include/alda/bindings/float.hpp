/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef ALDA_BINDINGS_FLOAT_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_HPP_INCLUDED

#include <alda/symbol.hpp>
#include <alda/bindings/float_type.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

struct float_
:
majutsu::fundamental<
	alda::bindings::float_type
>
{
};

FCPPT_PP_POP_WARNING

ALDA_SYMBOL
majutsu::size_type
needed_size(
	majutsu::concepts::dynamic_memory::tag const *,
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &
);

ALDA_SYMBOL
void
place(
	majutsu::concepts::dynamic_memory::tag const *,
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &,
	majutsu::raw_pointer
);

ALDA_SYMBOL
alda::bindings::float_::type
make(
	majutsu::concepts::dynamic_memory::tag const *,
	alda::bindings::float_ const *,
	majutsu::const_raw_pointer
);

}
}

namespace majutsu
{
namespace concepts
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<>
struct static_size<
	alda::bindings::float_
>
:
majutsu::concepts::static_size<
	majutsu::fundamental<
		alda::bindings::float_type
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
