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


#ifndef SGE_RENDERER_LIGHT_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_LIGHT_OBJECT_HPP_INCLUDED

#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/light/variant.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace sge
{
namespace renderer
{
namespace light
{

class object
{
public:
	SGE_RENDERER_SYMBOL
	object(
		renderer::diffuse_color const &,
		renderer::specular_color const &,
		renderer::ambient_color const &,
		light::variant const &
	);

	SGE_RENDERER_SYMBOL
	renderer::diffuse_color const &
	diffuse() const;

	SGE_RENDERER_SYMBOL
	renderer::specular_color const &
	specular() const;

	SGE_RENDERER_SYMBOL
	renderer::ambient_color const &
	ambient() const;

	SGE_RENDERER_SYMBOL
	light::variant const &
	variant() const;
private:
	renderer::diffuse_color diffuse_;

	renderer::specular_color specular_;

	renderer::ambient_color ambient_;

	light::variant variant_;
};

}
}
}

#endif
