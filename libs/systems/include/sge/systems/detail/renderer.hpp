//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_RENDERER_HPP_INCLUDED

#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class renderer
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	renderer(
		sge::systems::renderer const &,
		sge::systems::renderer_caps
	);

	sge::systems::renderer const &
	parameters() const;

	sge::systems::renderer_caps
	caps() const;
private:
	sge::systems::renderer parameters_;

	sge::systems::renderer_caps caps_;
};

}
}
}

#endif
