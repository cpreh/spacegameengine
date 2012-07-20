#ifndef SGE_SHADER_PAIR_HPP_INCLUDED
#define SGE_SHADER_PAIR_HPP_INCLUDED

#include <sge/cg/program/object.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/cg/loaded_program_scoped_ptr.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/scoped_pair_fwd.hpp>
#include <sge/shader/symbol.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
class pair
{
FCPPT_NONCOPYABLE(
	pair);
public:
	SGE_SHADER_SYMBOL
	pair(
		sge::shader::context &,
		sge::renderer::vertex_declaration &,
		sge::shader::vertex_program_path const &,
		sge::shader::pixel_program_path const &);

	SGE_SHADER_SYMBOL
	sge::shader::context &
	context() const;

	SGE_SHADER_SYMBOL
	sge::cg::program::object &
	vertex_program();

	SGE_SHADER_SYMBOL
	sge::cg::program::object &
	pixel_program();

	SGE_SHADER_SYMBOL
	sge::renderer::cg::loaded_program &
	loaded_vertex_program();

	SGE_SHADER_SYMBOL
	sge::renderer::cg::loaded_program &
	loaded_pixel_program();

	SGE_SHADER_SYMBOL
	~pair();
private:
	friend class sge::shader::parameter::planar_texture;
	friend class sge::shader::scoped_pair;

	typedef
	boost::ptr_vector
	<
		sge::shader::parameter::planar_texture,
		boost::view_clone_allocator
	>
	planar_texture_sequence;

	sge::shader::context &context_;
	sge::cg::program::object vertex_program_;
	sge::cg::program::object pixel_program_;
	sge::renderer::cg::loaded_program_scoped_ptr loaded_vertex_program_;
	sge::renderer::cg::loaded_program_scoped_ptr loaded_pixel_program_;
	planar_texture_sequence planar_textures_;

	void
	add_planar_texture(
		sge::shader::parameter::planar_texture &);

	void
	remove_planar_texture(
		sge::shader::parameter::planar_texture &);
};
}
}

#endif
