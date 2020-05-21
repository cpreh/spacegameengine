//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CONTEXT_SCOPED_CORE_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_CORE_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/scoped_core_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class scoped_core
{
	FCPPT_NONMOVABLE(
		scoped_core
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_core(
		sge::renderer::device::core &,
		sge::renderer::target::base &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_core();

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::context::core &
	get() const;
private:
	sge::renderer::device::core &device_;

	sge::renderer::context::core_unique_ptr const context_;
};

}
}
}

#endif
