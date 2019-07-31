//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_TRANSFORM_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_TRANSFORM_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object_fwd.hpp>
#include <sge/renderer/state/ffp/transform/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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

/**
\brief A scoped transform block

This class sets a new matrix for a given matrix mode in the constructor and
resets the matrix to the identity in the destructor.
*/
class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped(
		sge::renderer::context::ffp &context,
		sge::renderer::state::ffp::transform::mode,
		sge::renderer::state::ffp::transform::object const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();
private:
	sge::renderer::context::ffp &context_;

	sge::renderer::state::ffp::transform::mode const mode_;
};

}
}
}
}
}

#endif
