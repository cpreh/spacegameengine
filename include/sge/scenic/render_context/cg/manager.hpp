#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/cg/object_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/matrix4.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class manager
:
	public sge::scenic::render_context::manager_base
{
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::shader::context &,
		sge::renderer::vertex_declaration &);

	/* override */
	sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::object &);

	~manager();
private:
	friend class sge::scenic::render_context::cg::object;

	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_projection_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_inverse_transpose_matrix_;
	sge::shader::parameter::planar_texture diffuse_texture_;
};
}
}
}
}

#endif
