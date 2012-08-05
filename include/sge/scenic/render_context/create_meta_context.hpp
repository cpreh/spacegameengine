#ifndef SGE_SCENIC_RENDER_CONTEXT_CREATE_META_CONTEXT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CREATE_META_CONTEXT_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/meta_context_unique_ptr.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
SGE_SCENIC_SYMBOL
sge::scenic::render_context::meta_context_unique_ptr
create_meta_context(
	sge::renderer::device &);
}
}
}

#endif
