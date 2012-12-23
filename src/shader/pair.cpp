/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/shader/context.hpp>
#include <sge/shader/exception.hpp>
#include <sge/shader/load_edited_string.hpp>
#include <sge/shader/pair.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <memory>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef
std::unique_ptr<std::istream>
istream_unique_ptr;

istream_unique_ptr
open_istream_exn(
	boost::filesystem::path const &_path)
{
	typedef
	std::unique_ptr<boost::filesystem::ifstream>
	boost_filesystem_ifstream_unique_ptr;

	boost_filesystem_ifstream_unique_ptr result(
		fcppt::make_unique_ptr<boost::filesystem::ifstream>(
			_path));

	if(!result->is_open())
		throw
			sge::shader::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					_path)+
				FCPPT_TEXT("\""));

	return
		istream_unique_ptr(
			std::move(
				result));
}
}

// TODO: Use a delegating constructor?
sge::shader::pair::pair(
	sge::shader::context &_context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::shader::vertex_program_path const &_vertex_program_path,
	sge::shader::pixel_program_path const &_pixel_program_path,
	sge::shader::optional_cflags const &_optional_cflags)
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
				*open_istream_exn(
				_vertex_program_path.get())),
			sge::cg::program::main_function(
				"vertex_main"),
			sge::cg::program::compile_options(
				_context.vertex_compile_options().value(),
				_optional_cflags.value()))),
	pixel_program_(
		sge::cg::program::from_string_parameters(
			_context.cg_context(),
			sge::cg::program::source_type::text,
			_context.pixel_profile(),
			sge::shader::load_edited_string(
				_context.renderer(),
				_vertex_declaration,
				*open_istream_exn(
					_pixel_program_path.get())),
			sge::cg::program::main_function(
				"pixel_main"),
			sge::cg::program::compile_options(
				_context.pixel_compile_options().value(),
				_optional_cflags.value()))),
	loaded_vertex_program_(
		context_.renderer().load_cg_program(
			vertex_program_)),
	loaded_pixel_program_(
		context_.renderer().load_cg_program(
			pixel_program_)),
	planar_textures_()
{
}

sge::shader::pair::pair(
	sge::shader::context &_context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::shader::vertex_program_stream const &_vertex_program_stream,
	sge::shader::pixel_program_stream const &_pixel_program_stream,
	sge::shader::optional_cflags const &_optional_cflags)
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
				_vertex_program_stream.get()),
			sge::cg::program::main_function(
				"vertex_main"),
			sge::cg::program::compile_options(
				_context.vertex_compile_options().value(),
				_optional_cflags.value()))),
	pixel_program_(
		sge::cg::program::from_string_parameters(
			_context.cg_context(),
			sge::cg::program::source_type::text,
			_context.pixel_profile(),
			sge::shader::load_edited_string(
				_context.renderer(),
				_vertex_declaration,
				_pixel_program_stream.get()),
			sge::cg::program::main_function(
				"pixel_main"),
			sge::cg::program::compile_options(
				_context.pixel_compile_options().value(),
				_optional_cflags.value()))),
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
