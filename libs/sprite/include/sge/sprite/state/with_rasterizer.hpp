//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_WITH_RASTERIZER_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_RASTERIZER_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_rasterizer_fwd.hpp>
#include <sge/sprite/state/roles/enable_scissor_test.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
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

struct with_rasterizer
{
	typedef sge::sprite::state::roles::rasterizer role;

	typedef sge::sprite::state::roles::enable_scissor_test parameter_role;

	typedef std::false_type needs_ffp;

	typedef std::true_type persistent;

	typedef std::true_type has_parameter;

	typedef sge::renderer::state::core::rasterizer::object_unique_ptr state_type;

	typedef
	fcppt::optional::object<
		sge::renderer::state::core::rasterizer::enable_scissor_test
	>
	optional_extra_parameters;

	SGE_SPRITE_DETAIL_SYMBOL
	static
	sge::renderer::state::core::rasterizer::object_unique_ptr
	make(
		sge::renderer::device::core &,
		sge::sprite::state::with_rasterizer::optional_extra_parameters const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	set(
		sge::renderer::context::core &,
		sge::renderer::state::core::rasterizer::object const &
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
