/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_RENDERER_STATE_EXTRACT_TRAMPOLINE_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_STATE_EXTRACT_TRAMPOLINE_IMPL_HPP_INCLUDED

#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/any_key.hpp>
#include <sge/renderer/state/extract_trampoline.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/map.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/src/renderer/state/make_state_key.hpp>
#include <fcppt/text.hpp>


template<
	typename T,
	typename States
>
T
sge::renderer::state::extract_trampoline(
	sge::renderer::state::list const &_list,
	state::trampoline<T, States> const &_trampoline
)
{
	state::map const &map(
		_list.values()
	);

	state::map::const_iterator const it(
		map.find(
			state::any_key(
				state::make_state_key(
					_trampoline.state()
				)
			)
		)
	);

	if(
		it == map.end()
	)
		throw renderer::exception(
			FCPPT_TEXT("renderer::list::get(): state not found!")
		);

	return
		it->second.get<
			typename renderer::state::trampoline<
				T,
				States
			>::var_type
		>().value();
}

#endif
