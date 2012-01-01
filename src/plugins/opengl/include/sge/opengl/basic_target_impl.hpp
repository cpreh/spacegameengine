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


#ifndef SGE_OPENGL_BASIC_TARGET_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TARGET_IMPL_HPP_INCLUDED

#include <sge/opengl/basic_target.hpp>
#include <sge/opengl/set_scissor_area.hpp>
#include <sge/opengl/viewport.hpp>
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
	active_(false),
	viewport_(
		_viewport
	),
	scissor_area_(
		renderer::scissor_area(
			_viewport.get()
		)
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
sge::opengl::basic_target<Base>::bind()
{
	active_ = true;

	this->on_bind();

	this->set_viewport();

	this->set_scissor_area();
}

template<
	typename Base
>
void
sge::opengl::basic_target<Base>::unbind()
{
	active_ = false;

	this->on_unbind();
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

	if(
		active_
	)
		this->set_viewport();
}

template<
	typename Base
>
sge::renderer::viewport const
sge::opengl::basic_target<Base>::viewport() const
{
	return viewport_;
}

template<
	typename Base
>
void
sge::opengl::basic_target<Base>::scissor_area(
	renderer::scissor_area const &_scissor_area
)
{
	scissor_area_ = _scissor_area;

	if(
		active_
	)
		this->set_scissor_area();
}

template<
	typename Base
>
sge::renderer::scissor_area const
sge::opengl::basic_target<Base>::scissor_area() const
{
	return scissor_area_;
}

template<
	typename Base
>
void
sge::opengl::basic_target<Base>::set_viewport()
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
sge::opengl::basic_target<Base>::set_scissor_area()
{
	opengl::set_scissor_area(
		scissor_area_,
		this->height()
	);
}

#endif
