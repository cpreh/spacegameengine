//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_CLIP_PLANE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_CLIP_PLANE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef void parameter;

	context();

	~context()
	override;

	sge::renderer::state::index_count
	indices() const;

	void
	indices(
		sge::renderer::state::index_count
	);

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::renderer::state::index_count indices_;
};

}
}
}
}
}

#endif
