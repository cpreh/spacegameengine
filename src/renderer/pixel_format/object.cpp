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


#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>


sge::renderer::pixel_format::object::object(
	sge::renderer::pixel_format::color const _color,
	sge::renderer::pixel_format::depth_stencil const _depth_stencil,
	sge::renderer::pixel_format::optional_multi_samples const &_multi_samples,
	sge::renderer::pixel_format::srgb const _srgb
)
:
	color_(
		_color
	),
	depth_stencil_(
		_depth_stencil
	),
	multi_samples_(
		_multi_samples
	),
	srgb_(
		_srgb
	)
{
}

sge::renderer::pixel_format::color
sge::renderer::pixel_format::object::color() const
{
	return color_;
}

sge::renderer::pixel_format::depth_stencil
sge::renderer::pixel_format::object::depth_stencil() const
{
	return depth_stencil_;
}

sge::renderer::pixel_format::optional_multi_samples const
sge::renderer::pixel_format::object::multi_samples() const
{
	return multi_samples_;
}

sge::renderer::pixel_format::srgb
sge::renderer::pixel_format::object::srgb() const
{
	return srgb_;
}
