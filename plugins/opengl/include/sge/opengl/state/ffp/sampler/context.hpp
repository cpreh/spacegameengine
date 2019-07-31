//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace sampler
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

	sge::renderer::texture::stage
	stages() const;

	void
	stages(
		sge::renderer::texture::stage
	);

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::renderer::texture::stage stages_;
};

}
}
}
}
}

#endif
