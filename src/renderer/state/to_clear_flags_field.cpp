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


#include <sge/renderer/state/to_clear_flags_field.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <utility>

namespace
{

typedef std::pair<
	sge::renderer::clear_flags::type,
	sge::renderer::state::bool_::trampoline_type const *
> translation_pair;

typedef fcppt::container::array<
	translation_pair,
	sge::renderer::clear_flags::size
> translation_array;

translation_array const translation =
{{
	std::make_pair(
		sge::renderer::clear_flags::back,
		&sge::renderer::state::bool_::clear_backbuffer
	),
	std::make_pair(
		sge::renderer::clear_flags::depth,
		&sge::renderer::state::bool_::clear_zbuffer
	),
	std::make_pair(
		sge::renderer::clear_flags::stencil,
		&sge::renderer::state::bool_::clear_stencil
	)
}};

}

sge::renderer::clear_flags_field const
sge::renderer::state::to_clear_flags_field(
	state::list const &_list
)
{
	renderer::clear_flags_field ret(
		renderer::clear_flags_field::null()
	);

	for(
		translation_array::const_iterator it(
			translation.begin()
		);
		it != translation.end();
		++it
	)
		ret[
			it->first
		] =
			_list.get(
				*it->second
			);

	return ret;
}
