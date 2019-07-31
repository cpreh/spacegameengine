//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_ACTOR_HPP_INCLUDED

#include <sge/opengl/vf/actor_fwd.hpp>
#include <sge/opengl/vf/client_state_combiner_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class actor
{
	FCPPT_NONCOPYABLE(
		actor
	);
protected:
	actor();
public:
	virtual
	void
	operator()(
		sge::opengl::vf::client_state_combiner &,
		sge::opengl::vf::pointer
	) const = 0;

	virtual
	sge::renderer::vf::dynamic::offset
	offset() const = 0;

	virtual
	void
	unuse(
		sge::opengl::vf::client_state_combiner &
	) const = 0;

	virtual
	~actor();
};

}
}
}

#endif
