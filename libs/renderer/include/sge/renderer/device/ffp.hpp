//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_DEVICE_FFP_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_FFP_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::device
{

/**
\brief Provides ffp functionality

In addition to the core device, ffp states such as fog, lighting and
alpha_testing are provided.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL ffp
:
	public sge::renderer::device::core
{
	FCPPT_NONMOVABLE(
		ffp
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	ffp();
public:
	[[nodiscard]]
	virtual
	sge::renderer::context::ffp_unique_ptr
	begin_rendering_ffp(
		sge::renderer::target::base_ref
	) = 0;

	virtual
	void
	end_rendering_ffp(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	) = 0; // NOLINT(google-runtime-references)

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::alpha_test::object_unique_ptr
	create_alpha_test_state(
		sge::renderer::state::ffp::alpha_test::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::clip_plane::object_unique_ptr
	create_clip_plane_state(
		sge::renderer::state::ffp::clip_plane::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::fog::object_unique_ptr
	create_fog_state(
		sge::renderer::state::ffp::fog::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::lighting::object_unique_ptr
	create_lighting_state(
		sge::renderer::state::ffp::lighting::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::lighting::light::object_unique_ptr
	create_light_state(
		sge::renderer::state::ffp::lighting::light::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::lighting::material::object_unique_ptr
	create_material_state(
		sge::renderer::state::ffp::lighting::material::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::misc::object_unique_ptr
	create_misc_state(
		sge::renderer::state::ffp::misc::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::sampler::object_unique_ptr
	create_ffp_sampler_state(
		sge::renderer::state::ffp::sampler::parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::state::ffp::transform::object_unique_ptr
	create_transform_state(
		sge::renderer::state::ffp::transform::parameters const &
	) = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	~ffp()
	override;
};

}

#endif
