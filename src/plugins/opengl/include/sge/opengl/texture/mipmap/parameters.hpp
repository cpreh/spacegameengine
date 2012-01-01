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


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/init_function.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/parameters_fwd.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace mipmap
{

template<
	fcppt::math::size_type Dim
>
class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	typedef typename renderer::basic_dim<
		Dim
	>::type dim;

	typedef typename texture::init_function<
		Dim
	>::type init_function_type;

	parameters(
		texture::binding const &,
		opengl::context::object &,
		texture::type,
		opengl::color_format,
		opengl::color_format_type,
		opengl::internal_color_format,
		dim const &,
		init_function_type const &
	);

	texture::binding const &
	binding() const;

	opengl::context::object &
	context() const;

	texture::type const
	type() const;

	opengl::color_format const
	format() const;

	opengl::color_format_type const
	format_type() const;

	opengl::internal_color_format const
	internal_format() const;

	dim const &
	size() const;

	init_function_type const &
	init_function() const;
private:
	texture::binding const &binding_;

	opengl::context::object &context_;

	texture::type const type_;

	opengl::color_format format_;

	opengl::color_format_type format_type_;

	opengl::internal_color_format internal_format_;

	dim const size_;

	init_function_type const init_function_;
};

}
}
}
}

#endif
