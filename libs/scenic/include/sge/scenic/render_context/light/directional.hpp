//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_DIRECTIONAL_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_DIRECTIONAL_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/light/direction.hpp>
#include <sge/scenic/render_context/light/directional_fwd.hpp>


namespace sge::scenic::render_context::light
{

class directional
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	explicit
	directional(
		sge::scenic::render_context::light::direction
	);

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::direction const &
	direction() const;
private:
	sge::scenic::render_context::light::direction direction_;
};

}

#endif
