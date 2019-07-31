//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_MISC_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_MISC_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/misc/object_fwd.hpp>
#include <sge/renderer/state/ffp/misc/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace misc
{

class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped(
		sge::renderer::context::ffp &,
		sge::renderer::state::ffp::misc::object const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();
private:
	sge::renderer::context::ffp &context_;
};

}
}
}
}
}

#endif
