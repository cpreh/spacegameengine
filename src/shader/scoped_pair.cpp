#include <sge/shader/context.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/scoped_pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>


sge::shader::scoped_pair::scoped_pair(
	sge::renderer::context::object &_render_context,
	sge::shader::pair &_parent)
:
	parent_(
		_parent),
	scoped_vertex_program_(
		_render_context,
		parent_.loaded_vertex_program()),
	scoped_pixel_program_(
		_render_context,
		parent_.loaded_pixel_program())
{
	for(
		sge::shader::pair::planar_texture_sequence::iterator it =
			parent_.planar_textures_.begin();
		it != parent_.planar_textures_.end();
		++it)
		it->activate(
			_render_context);
}

sge::shader::scoped_pair::~scoped_pair()
{
	for(
		sge::shader::pair::planar_texture_sequence::iterator it =
			parent_.planar_textures_.begin();
		it != parent_.planar_textures_.end();
		++it)
		it->deactivate();
}
