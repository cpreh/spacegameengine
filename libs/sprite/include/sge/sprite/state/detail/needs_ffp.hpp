/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/any.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
struct needs_ffp
{
private:
	template<
		typename Type
	>
	using
	extract
	=
	typename Type::needs_ffp;
public:
	typedef
	brigand::any<
		typename
		StateChoices::optional_elements,
		brigand::bind<
			extract,
			brigand::_1
		>
	>
	type;
};

}
}
}
}

#endif
