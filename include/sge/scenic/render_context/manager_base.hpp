#ifndef SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CLASS_SYMBOL manager_base
{
FCPPT_NONCOPYABLE(
	manager_base);
public:
	virtual sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::object &) = 0;

	virtual
	~manager_base() = 0;
protected:
	manager_base();
};
}
}
}

#endif
