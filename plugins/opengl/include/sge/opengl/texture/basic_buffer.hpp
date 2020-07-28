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
#include <fcppt/nonmovable.hpp>
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
class basic_buffer // NOLINT(fuchsia-multiple-inheritance)
:
	public
		Types::base,
	public
		sge::opengl::texture::buffer_base
{
	FCPPT_NONMOVABLE(
		basic_buffer
	);
public:
	using
	base_type
	=
	typename
	Types::base;

	using
	image_tag
	=
	typename
	base_type::image_tag;

	using
	color_tag
	=
	sge::image::traits::image::color_tag<
		image_tag
	>;

	using
	format_type
	=
	sge::image::traits::pixel::format<
		color_tag
	>;

	using
	dim
	=
	typename
	base_type::dim;

	using
	config_type
	=
	sge::opengl::texture::config<
		dim::static_size::value
	>;

	basic_buffer(
		format_type,
		config_type const &,
		sge::opengl::texture::basic_buffer_parameters const &
	);

	~basic_buffer()
	override;

	[[nodiscard]]
	dim
	size() const
	override;

	[[nodiscard]]
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
