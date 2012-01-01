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


#include <sge/d3d9/texture/basic_impl.hpp>
#include <sge/d3d9/texture/cube.hpp>
#include <sge/d3d9/texture/cube_types.hpp>
#include <sge/d3d9/texture/lock_cube.hpp>
#include <sge/d3d9/texture/unlock_cube.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/tr1/functional.hpp>


sge::d3d9::texture::cube::cube(
	IDirect3DDevice9 *const _device,
	renderer::texture::cube_parameters const &_params
)
:
	texture::cube_basic(
		_device,
		_params
	),
	locked_side_()
{
}

sge::d3d9::texture::cube::~cube()
{
}

sge::image2d::view::object const
sge::d3d9::texture::cube::lock(
	renderer::texture::cube_side::type const _side,
	renderer::lock_rect const &_rect,
	renderer::lock_mode::type const _mode
)
{
	locked_side_ = _side;

	return
		this->lock_impl(
			this->lock_function(
				_side
			),
			_rect,
			_mode
		);
}

sge::image2d::view::const_object const
sge::d3d9::texture::cube::lock(
	renderer::texture::cube_side::type const _side,
	renderer::lock_rect const &_rect
) const
{
	locked_side_ = _side;

	return
		this->lock_impl(
			this->lock_function(
				_side
			),
			_rect
		);
}

void
sge::d3d9::texture::cube::unlock() const
{
	this->unlock_impl(
		std::tr1::bind(
			texture::unlock_cube,
			std::tr1::placeholders::_1,
			*locked_side_,
			std::tr1::placeholders::_2
		)
	);

	locked_side_.reset();
}

sge::d3d9::texture::cube::size_type
sge::d3d9::texture::cube::border_size() const
{
	return this->parameters().size();
}

sge::d3d9::texture::cube_basic::lock_function const
sge::d3d9::texture::cube::lock_function(
	renderer::texture::cube_side::type const _side
) const
{
	return
		std::tr1::bind(
			texture::lock_cube,
			std::tr1::placeholders::_1,
			_side,
			std::tr1::placeholders::_2,
			std::tr1::placeholders::_3,
			std::tr1::placeholders::_4
		);
}

template class
sge::d3d9::texture::basic<
	sge::d3d9::texture::cube_types
>;
