#include <sge/shader/context.hpp>
#include <sge/shader/load_edited_string.hpp>
#include <sge/shader/pair.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>


sge::shader::pair::pair(
	sge::shader::context &_context,
	sge::renderer::vertex_declaration &_vertex_declaration,
	sge::shader::vertex_program_path const &_vertex_program_path,
	sge::shader::pixel_program_path const &_pixel_program_path)
:
	context_(
		_context),
	vertex_program_(
		sge::cg::program::from_string_parameters(
			_context.cg_context(),
			sge::cg::program::source_type::text,
			_context.vertex_profile(),
			sge::shader::load_edited_string(
				_context.renderer(),
				_vertex_declaration,
				_vertex_program_path.get()),
			sge::cg::program::main_function(
				"vertex_main"),
			_context.vertex_compile_options())),
	pixel_program_(
		sge::cg::program::from_string_parameters(
			_context.cg_context(),
			sge::cg::program::source_type::text,
			_context.pixel_profile(),
			sge::shader::load_edited_string(
				_context.renderer(),
				_vertex_declaration,
				_pixel_program_path.get()),
			sge::cg::program::main_function(
				"pixel_main"),
			_context.pixel_compile_options())),
	loaded_vertex_program_(
		context_.renderer().load_cg_program(
			vertex_program_)),
	loaded_pixel_program_(
		context_.renderer().load_cg_program(
			pixel_program_)),
	planar_textures_()
{
}

sge::shader::context &
sge::shader::pair::context() const
{
	return
		context_;
}

sge::cg::program::object &
sge::shader::pair::vertex_program()
{
	return
		vertex_program_;
}

sge::cg::program::object &
sge::shader::pair::pixel_program()
{
	return
		pixel_program_;
}

sge::renderer::cg::loaded_program &
sge::shader::pair::loaded_vertex_program()
{
	return
		*loaded_vertex_program_;
}

sge::renderer::cg::loaded_program &
sge::shader::pair::loaded_pixel_program()
{
	return
		*loaded_pixel_program_;
}

sge::shader::pair::~pair()
{
}

void
sge::shader::pair::add_planar_texture(
	sge::shader::parameter::planar_texture &_new_texture)
{
	sge::shader::parameter::planar_texture * const _new_texture_ptr =
		&_new_texture;

	planar_textures_.push_back(
		_new_texture_ptr);
}

void
sge::shader::pair::remove_planar_texture(
	sge::shader::parameter::planar_texture &_new_texture)
{
	sge::shader::parameter::planar_texture * const _new_texture_ptr =
		&_new_texture;

	fcppt::algorithm::ptr_container_erase(
		planar_textures_,
		_new_texture_ptr);
}
