#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_META_CONTEXT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_META_CONTEXT_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/meta_context_base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class meta_context
:
	public sge::scenic::render_context::meta_context_base
{
FCPPT_NONCOPYABLE(
	meta_context);
public:
	SGE_SCENIC_SYMBOL
	meta_context();

	/* override(meta_context_base) */
	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::base_unique_ptr
	wrap_context(
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	~meta_context();
private:
};
}
}
}
}

#endif
