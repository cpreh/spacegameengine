//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BOX_HPP_INCLUDED

#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_box_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic_box
:
	public
		sge::opengl::texture::basic<
			Types
		>
{
	typedef
	sge::opengl::texture::basic<
		Types
	>
	base_type;

	FCPPT_NONCOPYABLE(
		basic_box
	);
public:
	typedef
	typename
	Types::parameters
	parameters_type;

	basic_box(
		sge::opengl::texture::basic_parameters const &,
		sge::opengl::texture::type,
		parameters_type const &,
		sge::opengl::texture::config<
			Types::buffer_types::dim_types::num_dims
		> const &
	);

	~basic_box()
	override;
private:
	typedef
	typename
	base_type::nonconst_buffer
	nonconst_buffer;

	typedef
	typename
	base_type::const_buffer
	const_buffer;

	typedef
	typename
	base_type::dim
	dim;

	nonconst_buffer &
	level(
		sge::renderer::texture::mipmap::level
	)
	override;

	const_buffer const &
	level(
		sge::renderer::texture::mipmap::level
	) const
	override;

	sge::renderer::texture::mipmap::level_count
	levels() const
	override;

	typedef
	fcppt::unique_ptr<
		nonconst_buffer
	>
	color_buffer_unique_ptr;

	typedef
	std::vector<
		color_buffer_unique_ptr
	>
	buffer_vector;

	buffer_vector const levels_;
};

}
}
}

#endif
