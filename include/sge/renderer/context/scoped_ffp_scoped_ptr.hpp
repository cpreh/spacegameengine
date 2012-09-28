#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_SCOPED_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_SCOPED_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_ffp_fwd.hpp>
#include <fcppt/scoped_ptr_impl.hpp>

namespace sge
{
namespace renderer
{
namespace context
{
typedef
fcppt::scoped_ptr<
	sge::renderer::context::scoped_ffp
>
scoped_ffp_scoped_ptr;
}
}
}

#endif
