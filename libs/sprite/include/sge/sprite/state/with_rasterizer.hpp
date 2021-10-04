//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_WITH_RASTERIZER_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_RASTERIZER_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_rasterizer_fwd.hpp>
#include <sge/sprite/state/roles/enable_scissor_test.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::state
{

struct with_rasterizer
{
	using
	role
	=
	sge::sprite::state::roles::rasterizer;

	using
	parameter_role
	=
	sge::sprite::state::roles::enable_scissor_test;

	using
	needs_ffp
	=
	std::false_type;

	using
	persistent
	=
	std::true_type;

	using
	has_parameter
	=
	std::true_type;

	using
	state_type
	=
	sge::renderer::state::core::rasterizer::object_unique_ptr;

	using
	optional_extra_parameters
	=
	fcppt::optional::object<
		sge::renderer::state::core::rasterizer::enable_scissor_test
	>;

	SGE_SPRITE_DETAIL_SYMBOL
	static
	sge::renderer::state::core::rasterizer::object_unique_ptr
	make(
		sge::renderer::device::core_ref,
		sge::sprite::state::with_rasterizer::optional_extra_parameters const &
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	set(
		sge::renderer::context::core &, // NOLINT(google-runtime-references)
		fcppt::reference<
			sge::renderer::state::core::rasterizer::object const
		>
	);

	SGE_SPRITE_DETAIL_SYMBOL
	static
	void
	unset(
		sge::renderer::context::core & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
};

}

#endif
