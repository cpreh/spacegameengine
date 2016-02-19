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

#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/format_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/object_decl.hpp>


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
	typename
	sge::image::traits::color_tag<
		image_tag
	>::type
	color_tag;

	typedef
	typename
	sge::image::traits::format<
		color_tag
	>::type
	format_type;

	basic_buffer(
		format_type,
		sge::opengl::texture::basic_buffer_parameters const &
	);

	~basic_buffer()
	override;

	typedef
	typename
	base_type::dim
	dim;

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
