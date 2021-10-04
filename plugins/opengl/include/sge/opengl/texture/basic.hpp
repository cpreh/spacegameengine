//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge::opengl::texture
{

template<
	typename Types
>
class basic // NOLINT(fuchsia-multiple-inheritance)
:
	public
		Types::base,
	public
		sge::opengl::texture::base
{
	FCPPT_NONMOVABLE(
		basic
	);
protected:
	using
	parameters_type
	=
	typename
	Types::parameters;

	basic(
		sge::opengl::texture::basic_parameters const &,
		sge::opengl::texture::type,
		parameters_type const &
	);

	~basic()
	override;

	using
	base_type
	=
	typename
	Types::base;

	[[nodiscard]]
	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	[[nodiscard]]
	sge::renderer::texture::capabilities_field
	capabilities() const
	override;

	[[nodiscard]]
	sge::renderer::texture::mipmap::object
	mipmap() const
	override;

	[[nodiscard]]
	sge::opengl::context::object &
	context() const;
private:
	void
	generate_mipmaps()
	override;

	fcppt::log::object_reference const log_;

	sge::opengl::context::object_ref const context_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::renderer::texture::capabilities_field const capabilities_;

	sge::renderer::texture::mipmap::object const mipmap_;
};

}

#endif
