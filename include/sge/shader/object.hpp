/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_OBJECT_HPP_INCLUDED
#define SGE_SHADER_OBJECT_HPP_INCLUDED

#include <sge/shader/symbol.hpp>
#include <sge/shader/matrix_flags.hpp>
#include <sge/shader/activation_method_field.hpp>
#include <sge/shader/value_variant.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/object_parameters_fwd.hpp>
#include <sge/shader/texture_variant.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/glsl/scoped_attachment_fwd.hpp>
#include <fcppt/tr1/unordered_map.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace shader
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	// NOTE: Currently, we restrict ourselves to shaders from
	// files. There could be stream support, too. It's just laziness
	SGE_SHADER_SYMBOL explicit
	object(
		shader::object_parameters const &);

	SGE_SHADER_SYMBOL void
	update_uniform(
		renderer::glsl::string const &name,
		shader::value_variant const &);

	SGE_SHADER_SYMBOL void
	update_texture(
		renderer::glsl::string const &name,
		shader::texture_variant const &);

	// This is called by the scoped class, but you may call it manually, too
	SGE_SHADER_SYMBOL void
	activate(
		shader::activation_method_field const &);

	// This is called by the scoped class, but you may call it manually, too
	SGE_SHADER_SYMBOL void
	deactivate(
		shader::activation_method_field const &);

	// noncopyable classes are supposed to have a destructor
	SGE_SHADER_SYMBOL ~object();
private:
	// This is unordered because std::maps perform badly with strings
	typedef
	std::tr1::unordered_map
	<
		renderer::glsl::string,
		renderer::glsl::uniform::variable_ptr
	>
	uniform_map;

	typedef
	std::vector<renderer::glsl::pixel_shader_ptr>
	pixel_shader_sequence;

	typedef
	std::vector<renderer::glsl::vertex_shader_ptr>
	vertex_shader_sequence;

	typedef
	boost::ptr_vector<renderer::glsl::scoped_attachment>
	attachment_sequence;

	renderer::device &renderer_;
	renderer::vertex_declaration const &vertex_declaration_;
	renderer::glsl::program_ptr program_;
	uniform_map uniforms_,uniform_matrices_;
	shader::sampler_sequence samplers_;
	vertex_shader_sequence vertex_shaders_;
	pixel_shader_sequence pixel_shaders_;
	attachment_sequence attachments_;
};
}
}

#endif
