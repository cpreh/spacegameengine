#include <sge/scenic/render_context/cg/context.hpp>

sge::scenic::render_context::cg::context::context(
	sge::renderer::context::object &_core_context)
:
	core_context_(
		_core_context)
{
}

sge::renderer::context::object &
sge::scenic::render_context::cg::context::core_context()
{
	return
		core_context_;
}

sge::scenic::render_context::cg::context::~context()
{
}
