//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_ATTENUATION_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_ATTENUATION_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/light/attenuation_fwd.hpp>
#include <sge/scenic/render_context/light/constant_attenuation.hpp>
#include <sge/scenic/render_context/light/linear_attenuation.hpp>
#include <sge/scenic/render_context/light/quadratic_attenuation.hpp>


namespace sge::scenic::render_context::light
{
class attenuation
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	attenuation(
		sge::scenic::render_context::light::constant_attenuation const &,
		sge::scenic::render_context::light::linear_attenuation const &,
		sge::scenic::render_context::light::quadratic_attenuation const &
	);

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::constant_attenuation
	constant_attenuation() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::linear_attenuation
	linear_attenuation() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::quadratic_attenuation
	quadratic_attenuation() const;
private:
	sge::scenic::render_context::light::constant_attenuation constant_attenuation_;
	sge::scenic::render_context::light::linear_attenuation linear_attenuation_;
	sge::scenic::render_context::light::quadratic_attenuation quadratic_attenuation_;
};
}

#endif
