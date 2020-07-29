//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_SCOPED_WORK_BINDING_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SCOPED_WORK_BINDING_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/scoped_work_binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class scoped_work_binding
:
	public sge::opengl::texture::binding
{
	FCPPT_NONMOVABLE(
		scoped_work_binding
	);
public:
	scoped_work_binding(
		fcppt::log::object &, // NOLINT(google-runtime-references)
		sge::opengl::context::object &, // NOLINT(google-runtime-references)
		sge::opengl::texture::type,
		sge::opengl::texture::id
	);

	~scoped_work_binding()
	override;
private:
	[[nodiscard]]
	sge::renderer::texture::stage
	stage() const
	override;

	static
	sge::renderer::texture::stage
	get_stage();

	[[nodiscard]]
	sge::opengl::texture::type
	type() const
	override;

	void
	bind(
		sge::opengl::texture::optional_id,
		sge::opengl::texture::type
	);

	sge::opengl::texture::active_level const active_level_;

	sge::opengl::texture::optional_id const previous_id_;

	sge::opengl::texture::type const type_;

	sge::opengl::texture::optional_type const previous_type_;
};

}
}
}

#endif
