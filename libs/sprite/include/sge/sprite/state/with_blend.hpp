//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_WITH_BLEND_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_BLEND_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_blend_fwd.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/blend_write_mask.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

struct with_blend
{
	typedef sge::sprite::state::roles::blend role;

	typedef sge::sprite::state::roles::blend_write_mask parameter_role;

	typedef std::false_type needs_ffp;

	typedef std::true_type persistent;

	typedef std::true_type has_parameter;

	typedef sge::renderer::state::core::blend::object_unique_ptr state_type;

	typedef
	fcppt::optional::object<
		sge::renderer::state::core::blend::write_mask
	>
	optional_extra_parameters;

	SGE_SPRITE_DETAIL_SYMBOL
	static
	sge::renderer::state::core::blend::object_unique_ptr
	make(
		sge::renderer::device::core &,
		sge::sprite::state::with_blend::optional_extra_parameters const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	set(
		sge::renderer::context::core &,
		sge::renderer::state::core::blend::object const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	unset(
		sge::renderer::context::core &
	);
};

}
}
}

#endif
