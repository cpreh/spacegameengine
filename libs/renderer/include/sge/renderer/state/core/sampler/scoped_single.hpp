//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_SCOPED_SINGLE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_SCOPED_SINGLE_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/scoped_single_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{

class scoped_single
{
	FCPPT_NONCOPYABLE(
		scoped_single
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_single(
		sge::renderer::context::core &,
		sge::renderer::texture::stage,
		sge::renderer::state::core::sampler::object const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_single();
private:
	sge::renderer::context::core &context_;

	sge::renderer::texture::stage const stage_;
};

}
}
}
}
}

#endif
