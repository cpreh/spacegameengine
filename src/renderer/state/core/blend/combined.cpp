/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/source.hpp>


sge::renderer::state::core::blend::combined::combined(
	sge::renderer::state::core::blend::source const _source,
	sge::renderer::state::core::blend::dest const _dest
)
:
	source_(
		_source
	),
	dest_(
		_dest
	)
{
}

sge::renderer::state::core::blend::source
sge::renderer::state::core::blend::combined::source() const
{
	return source_;
}

sge::renderer::state::core::blend::dest
sge::renderer::state::core::blend::combined::dest() const
{
	return dest_;
}
