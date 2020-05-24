//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_FOG_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_FOG_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/fog/variant.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace fog
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	parameters(
		sge::renderer::state::ffp::fog::variant
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::variant const &
	variant() const;
private:
	sge::renderer::state::ffp::fog::variant variant_;
};

}
}
}
}
}

#endif
