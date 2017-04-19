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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_HPP_INCLUDED

#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/static_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic_buffer
:
	public
		Types::base,
	public
		sge::opengl::texture::buffer_base
{
	FCPPT_NONCOPYABLE(
		basic_buffer
	);
public:
	typedef
	typename
	Types::base
	base_type;

	typedef
	typename
	base_type::image_tag
	image_tag;

	typedef
	sge::image::traits::image::color_tag<
		image_tag
	>
	color_tag;

	typedef
	sge::image::traits::pixel::format<
		color_tag
	>
	format_type;

	typedef
	typename
	base_type::dim
	dim;

	typedef
	sge::opengl::texture::config<
		dim::static_size::value
	>
	config_type;

	basic_buffer(
		format_type,
		config_type const &,
		sge::opengl::texture::basic_buffer_parameters const &
	);

	~basic_buffer()
	override;

	dim
	size() const
	override;

	format_type
	format() const
	override;
private:
	dim const size_;

	format_type const format_;
};

}
}
}

#endif
