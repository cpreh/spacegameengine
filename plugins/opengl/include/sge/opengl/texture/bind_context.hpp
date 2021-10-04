//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge::opengl::texture
{

class bind_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		bind_context
	);
public:
	bind_context();

	~bind_context()
	override;

	[[nodiscard]]
	sge::opengl::texture::const_optional_base_ref
	stage(
		sge::renderer::texture::stage
	) const;

	void
	stage(
		sge::renderer::texture::stage,
		sge::opengl::texture::const_optional_base_ref const &
	);

	using
	parameter
	=
	void;

	static
	sge::opengl::context::id const
	static_id;
private:
	using
	texture_map
	=
	fcppt::container::index_map<
		sge::opengl::texture::const_optional_base_ref
	>;

	mutable texture_map map_;
};

}

#endif
