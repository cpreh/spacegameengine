//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/context.hpp>
#include <sge/shader/context_ref.hpp>
#include <sge/shader/exception.hpp>
#include <sge/shader/load_edited_string.hpp>
#include <sge/shader/optional_cflags.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/pixel_program_stream.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/vertex_program_stream.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

using
istream_unique_ptr
=
fcppt::unique_ptr<
	std::istream
>;

istream_unique_ptr
open_istream_exn(
	std::filesystem::path const &_path
)
{
	using
	ifstream_unique_ptr
	=
	fcppt::unique_ptr<
		std::ifstream
	>;

	ifstream_unique_ptr result(
		fcppt::make_unique_ptr<
			std::ifstream
		>(
			_path
		)
	);

	if(
		!result->is_open()
	)
	{
		throw
			sge::shader::exception(
				FCPPT_TEXT("Couldn't open file \"")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
				+
				FCPPT_TEXT("\"")
			);
	}

	return
		fcppt::unique_ptr_to_base<
			std::istream
		>(
			std::move(
				result
			)
		);
}
}

sge::shader::pair::pair(
	sge::shader::context_ref const _context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::shader::vertex_program_path const &_vertex_program_path,
	sge::shader::pixel_program_path const &_pixel_program_path,
	sge::shader::optional_cflags const &_optional_cflags)
:
	pair{
		_context,
		_vertex_declaration,
		sge::shader::vertex_program_stream{
			fcppt::make_ref(
				*open_istream_exn(
					_vertex_program_path.get()
				)
			)
		},
		sge::shader::pixel_program_stream{
			fcppt::make_ref(
				*open_istream_exn(
					_pixel_program_path.get()
				)
			)
		},
		_optional_cflags
	}
{
}

sge::shader::pair::pair(
	sge::shader::context_ref const _context,
	sge::renderer::vertex::declaration const &_vertex_declaration,
	sge::shader::vertex_program_stream const &_vertex_program_stream,
	sge::shader::pixel_program_stream const &_pixel_program_stream,
	sge::shader::optional_cflags const &_optional_cflags
)
:
	context_(
		_context
	),
	vertex_program_(
		sge::cg::program::from_string_parameters(
			_context.get().cg_context(),
			sge::cg::program::source_type::text,
			_context.get().vertex_profile(),
			sge::shader::load_edited_string(
				_context.get().renderer(),
				_vertex_declaration,
				_vertex_program_stream.get().get()
			),
			sge::cg::program::main_function(
				"vertex_main"),
			sge::cg::program::compile_options(
				fcppt::container::join(
					_context.get().vertex_compile_options().value(),
					_optional_cflags.value()
				)
			)
		)
	),
	pixel_program_(
		sge::cg::program::from_string_parameters(
			_context.get().cg_context(),
			sge::cg::program::source_type::text,
			_context.get().pixel_profile(),
			sge::shader::load_edited_string(
				_context.get().renderer(),
				_vertex_declaration,
				_pixel_program_stream.get().get()
			),
			sge::cg::program::main_function(
				"pixel_main"
			),
			sge::cg::program::compile_options(
				fcppt::container::join(
					_context.get().pixel_compile_options().value(),
					_optional_cflags.value()
				)
			)
		)
	),
	loaded_vertex_program_(
		context_.get().renderer().load_cg_program(
			fcppt::make_ref(
				vertex_program_
			)
		)
	),
	loaded_pixel_program_(
		context_.get().renderer().load_cg_program(
			fcppt::make_ref(
				pixel_program_
			)
		)
	),
	planar_textures_()
{
}

sge::shader::context &
sge::shader::pair::context() const
{
	return
		context_.get();
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
= default;

void
sge::shader::pair::add_planar_texture(
	fcppt::reference<
		sge::shader::parameter::planar_texture
	> const _new_texture
)
{
	planar_textures_.insert(
		&_new_texture.get()
	);
}

void
sge::shader::pair::remove_planar_texture(
	sge::shader::parameter::planar_texture &_new_texture
)
{
	planar_textures_.erase(
		&_new_texture
	);
}
