//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/context/scoped_ffp_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class scoped_ffp
{
	FCPPT_NONCOPYABLE(
		scoped_ffp
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_ffp(
		sge::renderer::device::ffp &,
		sge::renderer::target::base &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_ffp();

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::context::ffp &
	get() const;
private:
	sge::renderer::device::ffp &device_;

	sge::renderer::context::ffp_unique_ptr const context_;
};

}
}
}

#endif
