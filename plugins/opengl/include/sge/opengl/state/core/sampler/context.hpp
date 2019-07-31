//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


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

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context

	);
public:
	typedef sge::opengl::context::object &parameter;

	explicit
	context(
		parameter
	);

	~context()
	override;

	void
	set(
		sge::renderer::state::core::sampler::const_optional_object_ref_map const &
	);

	sge::opengl::state::core::sampler::object const &
	get(
		sge::renderer::texture::stage
	) const;

	void
	reset();

	static
	sge::opengl::context::id const
	static_id;
private:
	typedef
	fcppt::unique_ptr<
		sge::opengl::state::core::sampler::object
	>
	object_unique_ptr;

	typedef
	fcppt::optional::reference<
		sge::opengl::state::core::sampler::object const
	>
	optional_object_ref;

	typedef
	std::map<
		sge::renderer::texture::stage,
		optional_object_ref
	>
	optional_object_ref_map;

	object_unique_ptr const defaults_;

	optional_object_ref_map objects_;
};

}
}
}
}
}

#endif
