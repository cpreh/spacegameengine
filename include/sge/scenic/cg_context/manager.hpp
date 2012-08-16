#ifndef SGE_SCENIC_CG_CONTEXT_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_CG_CONTEXT_MANAGER_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/cg_context/object_fwd.hpp>
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
namespace cg_context
{
class manager
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_SYMBOL
	manager(
		sge::shader::context &,
		sge::renderer::vertex_declaration &);

	SGE_SCENIC_SYMBOL
	~manager();
private:
	friend class sge::scenic::cg_context::object;

	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_projection_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_inverse_transpose_matrix_;
	sge::shader::parameter::planar_texture diffuse_texture_;
};
}
}
}

#endif
