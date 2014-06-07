/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_OPTIONS_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OPTIONS_DECL_HPP_INCLUDED

#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/detail/options_class.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename StateChoices
>
class options
{
	typedef typename sge::sprite::state::detail::options_class<
		StateChoices
	>::type elements_type;
public:
	typedef typename elements_type::memory_type::types flattened_types;

	explicit
	options(
		sge::sprite::state::vertex_options
	);

	options &
	no_blend_state();

	options &
	no_rasterizer_state();

	options &
	no_transform_state();

	sge::sprite::state::vertex_options
	vertex_options() const;

	template<
		typename Role
	>
	options &
	set(
		typename majutsu::role_return_type<
			flattened_types,
			Role
		>::type const &
	);

	elements_type const &
	elements() const;
private:
	sge::sprite::state::vertex_options vertex_options_;

	elements_type elements_;
};

}
}
}

#endif
