#include <sge/scenic/render_context/cg/context.hpp>
#include <sge/scenic/render_context/cg/meta_context.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::scenic::render_context::cg::meta_context::meta_context()
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::meta_context::wrap_context(
	sge::renderer::context::object &_core_context)
{
	return
		sge::scenic::render_context::base_unique_ptr(
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::context>(
				fcppt::ref(
					_core_context)));
}

sge::scenic::render_context::cg::meta_context::~meta_context()
{
}
