#ifndef SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED
#define SGE_SHADER_SCOPED_PAIR_HPP_INCLUDED

#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/shader/pair_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace shader
{
class scoped_pair
{
	FCPPT_NONCOPYABLE(
		scoped_pair);
public:
	scoped_pair(
		sge::renderer::context::object &,
		sge::shader::pair &);

	~scoped_pair();
private:
	sge::shader::pair &parent_;
	sge::renderer::cg::scoped_program scoped_vertex_program_;
	sge::renderer::cg::scoped_program scoped_pixel_program_;
};
}
}

#endif
