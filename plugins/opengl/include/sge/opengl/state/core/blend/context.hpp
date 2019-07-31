//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_BLEND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_BLEND_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/state/core/blend/context_fwd.hpp>
#include <sge/opengl/state/core/blend/optional_config.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace blend
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	context(
		sge::opengl::info::context const &
	);

	~context()
	override;

	sge::opengl::state::core::blend::optional_config const &
	config() const;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::state::core::blend::optional_config config_;
};

}
}
}
}
}

#endif
