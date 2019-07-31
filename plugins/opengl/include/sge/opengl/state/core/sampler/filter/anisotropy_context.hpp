//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context_fwd.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace sampler
{
namespace filter
{

class anisotropy_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		anisotropy_context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	anisotropy_context(
		sge::opengl::info::context const &
	);

	~anisotropy_context()
	override;

	sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &
	config() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::opengl::state::core::sampler::filter::optional_anisotropy_config const config_;
};

}
}
}
}
}
}

#endif
