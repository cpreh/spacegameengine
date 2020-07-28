//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/config_fwd.hpp>
#include <sge/opengl/texture/const_binding_ref.hpp>
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
	using
	dim
	=
	sge::renderer::basic_dim<
		Dim
	>;

	using
	config_type
	=
	sge::opengl::texture::config<
		Dim
	>;

	using
	const_config_ref
	=
	fcppt::reference<
		config_type const
	>;

	using
	init_function_type
	=
	sge::opengl::texture::init_function<
		Dim
	>;

	parameters(
		sge::opengl::texture::const_binding_ref,
		sge::opengl::texture::buffer_type,
		const_config_ref,
		sge::opengl::color_order,
		sge::opengl::color_base_type,
		sge::opengl::internal_color_format,
		dim const &,
		init_function_type
	);

	[[nodiscard]]
	sge::opengl::texture::binding const &
	binding() const;

	[[nodiscard]]
	sge::opengl::texture::buffer_type
	buffer_type() const;

	[[nodiscard]]
	config_type const &
	config() const;

	[[nodiscard]]
	sge::opengl::color_order
	format_order() const;

	[[nodiscard]]
	sge::opengl::color_base_type
	format_base_type() const;

	[[nodiscard]]
	sge::opengl::internal_color_format
	internal_format() const;

	[[nodiscard]]
	dim const &
	size() const;

	[[nodiscard]]
	init_function_type
	init_function() const;
private:
	sge::opengl::texture::const_binding_ref binding_;

	sge::opengl::texture::buffer_type buffer_type_;

	const_config_ref config_;

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
