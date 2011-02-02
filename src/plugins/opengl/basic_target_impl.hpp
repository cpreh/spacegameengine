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


#include "basic_target.hpp"
#include "viewport.hpp"
#include <fcppt/math/box/basic_impl.hpp>

template<
	typename Base
>
sge::opengl::basic_target<Base>::basic_target(
	renderer::viewport const &_viewport
)
:
	Base(),
	opengl::target_base(),
	viewport_(
		_viewport
	)
{
}

template<
	typename Base
>
sge::opengl::basic_target<Base>::~basic_target()
{
}


template<
	typename Base
>
void
sge::opengl::basic_target<Base>::activate_viewport()
{
	opengl::viewport(
		viewport_,
		this->height()
	);
}

template<
	typename Base
>
void
sge::opengl::basic_target<Base>::viewport(
	renderer::viewport const &_viewport
)
{
	viewport_ = _viewport;

	activate_viewport();
}

template<
	typename Base
>
sge::renderer::viewport const
sge::opengl::basic_target<Base>::viewport() const
{
	return viewport_;
}
