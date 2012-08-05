#ifndef SGE_SCENIC_RENDER_CONTEXT_META_CONTEXT_BASE_SCOPED_PTR_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_META_CONTEXT_BASE_SCOPED_PTR_HPP_INCLUDED

#include <sge/scenic/render_context/meta_context_base_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
typedef
fcppt::scoped_ptr<sge::scenic::render_context::meta_context_base>
meta_context_base_scoped_ptr;
}
}
}

#endif
