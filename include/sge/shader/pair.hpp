/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_PAIR_HPP_INCLUDED
#define SGE_SHADER_PAIR_HPP_INCLUDED

#include <sge/cg/program/object.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/optional_cflags.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/pixel_program_stream.hpp>
#include <sge/shader/scoped_pair_fwd.hpp>
#include <sge/shader/symbol.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/vertex_program_stream.hpp>
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
		sge::renderer::vertex::declaration const &,
		sge::shader::vertex_program_path const &,
		sge::shader::pixel_program_path const &,
		sge::shader::optional_cflags const &);

	SGE_SHADER_SYMBOL
	pair(
		sge::shader::context &,
		sge::renderer::vertex::declaration const &,
		sge::shader::vertex_program_stream const &,
		sge::shader::pixel_program_stream const &,
		sge::shader::optional_cflags const &);

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
	sge::renderer::cg::loaded_program_unique_ptr const loaded_vertex_program_;
	sge::renderer::cg::loaded_program_unique_ptr const loaded_pixel_program_;
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
