#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_CONTEXT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_CONTEXT_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class context
:
	public sge::scenic::render_context::base
{
FCPPT_NONCOPYABLE(
	context);
public:
	SGE_SCENIC_SYMBOL
	explicit
	context(
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	sge::renderer::context::object &
	core_context();

	SGE_SCENIC_SYMBOL
	~context();
private:
	sge::renderer::context::object &core_context_;
};
}
}
}
}

#endif
