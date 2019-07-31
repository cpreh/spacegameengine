//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_TRANSFORM_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_TRANSFORM_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace transform
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	parameters(
		sge::renderer::matrix4 const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::matrix4 const &
	matrix() const;
private:
	sge::renderer::matrix4 matrix_;
};

}
}
}
}
}

#endif
