#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/scenic/render_context/optional_planar_texture.hpp>
#include <sge/scenic/light_sequence.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual void
	transform(
		sge::renderer::matrix_mode::type,
		sge::renderer::matrix4 const &) = 0;

	virtual void
	diffuse_texture(
		sge::scenic::render_context::optional_planar_texture const &) = 0;

	virtual void
	lights(
		sge::scenic::light_sequence const &) = 0;

	virtual
	~base() = 0;
protected:
	base();
};
}
}
}

#endif
