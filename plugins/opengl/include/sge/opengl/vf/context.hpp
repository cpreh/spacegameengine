//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_VF_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/vf/client_state.hpp>
#include <sge/opengl/vf/context_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	using
	parameter
	=
	fcppt::log::object_reference;

	explicit
	context(
		parameter
	);

	~context()
	override;

	[[nodiscard]]
	sge::opengl::vf::client_state const &
	state() const;

	void
	state(
		sge::opengl::vf::client_state const &
	);

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::vf::client_state state_;
};

}
}
}

#endif
