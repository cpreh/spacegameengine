//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TARGET_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/target/context_fwd.hpp>
#include <sge/opengl/target/optional_base_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	context();

	~context()
	override;

	[[nodiscard]]
	sge::opengl::target::optional_base_ref const &
	last_target();

	void
	last_target(
		sge::opengl::target::optional_base_ref const &
	);

	using
	parameter
	=
	void;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::target::optional_base_ref last_target_;
};

}
}
}

#endif
