#ifndef SGE_SCENIC_CG_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_CG_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/cg_context/manager_fwd.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <sge/scenic/cg_context/optional_planar_texture.hpp>
#include <sge/shader/pair.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace scenic
{
namespace cg_context
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_SYMBOL
	object(
		sge::scenic::cg_context::manager &,
		sge::renderer::context::object &);

	SGE_SCENIC_SYMBOL
	void
	transform(
		sge::renderer::matrix_mode::type,
		sge::renderer::matrix4 const &);

	SGE_SCENIC_SYMBOL
	void
	diffuse_texture(
		sge::scenic::cg_context::optional_planar_texture const &);

	SGE_SCENIC_SYMBOL
	~object();
private:
	sge::scenic::cg_context::manager &manager_;
	sge::renderer::context::object &context_;
	sge::renderer::matrix4 current_world_;
	sge::renderer::matrix4 current_projection_;
};
}
}
}

#endif
