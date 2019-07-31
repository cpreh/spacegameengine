//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
