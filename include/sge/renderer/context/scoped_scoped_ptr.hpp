#ifndef SGE_RENDERER_CONTEXT_SCOPED_SCOPED_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_SCOPED_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace renderer
{
namespace context
{
typedef
fcppt::scoped_ptr<sge::renderer::context::scoped>
scoped_scoped_ptr;
}
}
}

#endif
