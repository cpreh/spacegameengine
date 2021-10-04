//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/variant.hpp>


namespace sge::renderer::state::ffp::lighting::light
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::ffp::lighting::diffuse_color,
		sge::renderer::state::ffp::lighting::specular_color,
		sge::renderer::state::ffp::lighting::ambient_color,
		sge::renderer::state::ffp::lighting::light::variant
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::diffuse_color const &
	diffuse() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::specular_color const &
	specular() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::ambient_color const &
	ambient() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::variant const &
	variant() const;
private:
	sge::renderer::state::ffp::lighting::diffuse_color diffuse_;

	sge::renderer::state::ffp::lighting::specular_color specular_;

	sge::renderer::state::ffp::lighting::ambient_color ambient_;

	sge::renderer::state::ffp::lighting::light::variant variant_;
};

}

#endif
