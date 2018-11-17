/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/init_function.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/parameters_fwd.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


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
public:
	typedef
	sge::renderer::basic_dim<
		Dim
	>
	dim;

	typedef
	sge::opengl::texture::config<
		Dim
	>
	config_type;

	typedef
	sge::opengl::texture::init_function<
		Dim
	>
	init_function_type;

	parameters(
		sge::opengl::texture::binding const &,
		sge::opengl::texture::buffer_type,
		config_type const &,
		sge::opengl::color_order,
		sge::opengl::color_base_type,
		sge::opengl::internal_color_format,
		dim const &,
		init_function_type
	);

	sge::opengl::texture::binding const &
	binding() const;

	sge::opengl::texture::buffer_type
	buffer_type() const;

	config_type const &
	config() const;

	sge::opengl::color_order
	format_order() const;

	sge::opengl::color_base_type
	format_base_type() const;

	sge::opengl::internal_color_format
	internal_format() const;

	dim const &
	size() const;

	init_function_type
	init_function() const;
private:
	fcppt::reference<
		sge::opengl::texture::binding const
	> binding_;

	sge::opengl::texture::buffer_type buffer_type_;

	fcppt::reference<
		config_type const
	> config_;

	sge::opengl::color_order format_order_;

	sge::opengl::color_base_type format_base_type_;

	sge::opengl::internal_color_format internal_format_;

	dim size_;

	init_function_type init_function_;
};

}
}
}
}

#define SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_PARAMETERS(\
	seq,\
	_,\
	dimension\
)\
extern \
template \
class \
sge::opengl::texture::mipmap::parameters<\
	dimension\
>;

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_DECLARE_PARAMETERS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)

#endif
