//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class SGE_CORE_DETAIL_CLASS_SYMBOL ffp
:
	public sge::renderer::context::core
{
	FCPPT_NONMOVABLE(
		ffp
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	ffp();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~ffp()
	override;

	virtual
	void
	alpha_test_state(
		sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &
	) = 0;

	virtual
	void
	clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
	) = 0;

	virtual
	void
	fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref const &
	) = 0;

	virtual
	void
	lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref const &
	) = 0;

	virtual
	void
	lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &
	) = 0;

	virtual
	void
	material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &
	) = 0;

	virtual
	void
	misc_state(
		sge::renderer::state::ffp::misc::const_optional_object_ref const &
	) = 0;

	virtual
	void
	sampler_ffp_state(
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	) = 0;

	virtual
	void
	transform(
		sge::renderer::state::ffp::transform::mode,
		sge::renderer::state::ffp::transform::const_optional_object_ref const &
	) = 0;
};

}
}
}

#endif
