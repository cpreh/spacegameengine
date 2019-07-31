//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_ALPHA_TEST_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_ALPHA_TEST_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/variant.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace alpha_test
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	parameters(
		sge::renderer::state::ffp::alpha_test::variant const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::alpha_test::variant const &
	variant() const;
private:
	sge::renderer::state::ffp::alpha_test::variant variant_;
};

}
}
}
}
}

#endif
