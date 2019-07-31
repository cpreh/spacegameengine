//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic
:
	public
		Types::base,
	public
		sge::opengl::texture::base
{
	FCPPT_NONCOPYABLE(
		basic
	);
protected:
	typedef
	typename
	Types::parameters
	parameters_type;

	basic(
		sge::opengl::texture::basic_parameters const &,
		sge::opengl::texture::type,
		parameters_type const &
	);

	~basic()
	override;

	typedef
	typename
	Types::base
	base_type;

	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	sge::renderer::texture::capabilities_field
	capabilities() const
	override;

	sge::renderer::texture::mipmap::object
	mipmap() const
	override;

	sge::opengl::context::object &
	context() const;
private:
	void
	generate_mipmaps()
	override;

	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::renderer::texture::capabilities_field const capabilities_;

	sge::renderer::texture::mipmap::object const mipmap_;
};

}
}
}

#endif
