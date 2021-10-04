//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_OPTIONS_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OPTIONS_DECL_HPP_INCLUDED

#include <sge/sprite/projection_dim_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace sge::sprite::state
{

template<
	typename StateChoices
>
class options
{
	using
	elements_type
	=
	sge::sprite::state::detail::options_class<
		StateChoices
	>;
public:
	explicit
	options(
		sge::sprite::state::vertex_options
	);

	options &
	no_blend_state();

	options &
	no_rasterizer_state();

	options &
	no_transform_state();

	options &
	fixed_projection(
		sge::sprite::projection_dim const &
	);

	[[nodiscard]]
	sge::sprite::state::vertex_options
	vertex_options() const;

	template<
		typename Role
	>
	options &
	set(
		fcppt::record::label_value_type<
			elements_type,
			Role
		>
	);

	[[nodiscard]]
	elements_type const &
	elements() const;
private:
	sge::sprite::state::vertex_options vertex_options_;

	elements_type elements_;
};

}

#endif
