#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED

#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/object_scoped_ptr.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/ffp/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace ffp
{
class manager
:
	public sge::scenic::render_context::manager_base
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::renderer::device::ffp &,
		sge::renderer::vertex_declaration &);

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::core &);

	SGE_SCENIC_SYMBOL
	~manager();
private:
	friend class sge::scenic::render_context::ffp::object;

	sge::renderer::device::ffp &renderer_;
	sge::renderer::vertex_declaration &vertex_declaration_;
};
}
}
}
}

#endif
