//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/source.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/from.hpp>


sge::renderer::state::core::blend::object_unique_ptr
sge::sprite::state::with_blend::make(
	sge::renderer::device::core_ref const _device,
	sge::sprite::state::with_blend::optional_extra_parameters const &_write_mask
)
{
	return
		_device.get().create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_variant{
					sge::renderer::state::core::blend::alpha_enabled{
						sge::renderer::state::core::blend::combined(
							sge::renderer::state::core::blend::source::src_alpha,
							sge::renderer::state::core::blend::dest::inv_src_alpha
						)
					}
				},
				fcppt::optional::from(
					_write_mask,
					[]{
						return
							sge::renderer::state::core::blend::write_mask_all();
					}
				)
			)
		);
}

void
sge::sprite::state::with_blend::set(
	sge::renderer::context::core &_context,
	fcppt::reference<
		sge::renderer::state::core::blend::object const
	> const _state
)
{
	_context.blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref(
			_state
		)
	);
}

void
sge::sprite::state::with_blend::unset(
	sge::renderer::context::core &_context
)
{
	_context.blend_state(
		sge::renderer::state::core::blend::const_optional_object_ref()
	);
}
