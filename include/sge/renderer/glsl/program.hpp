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


#ifndef SGE_RENDERER_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_RENDERER_GLSL_PROGRAM_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/shader_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{

/**
 * \brief A glsl program that combines shaders
 *
 * A glsl program controls which parts of the fixed function pipeline are
 * replaced by shaders. Initially, the program uses no shaders. It is possible
 * to use multiple shaders of the same kind in order to share code between
 * them. After all shaders of the program have been set, the program must be
 * linked. If no errors occur, then the program can be set for a
 * renderer::device. It is also possible to obtain uniform variables from an
 * already linked program.
 *
 * \see renderer::device::create_glsl_program
 * \see renderer::device::glsl_program
*/
class SGE_CLASS_SYMBOL program
{
	FCPPT_NONCOPYABLE(
		program
	);
protected:
	SGE_RENDERER_SYMBOL
	program();
public:
	/**
	 * \brief Returns a uniform variable
	 *
	 * Returns the uniform variable named \a name. A uniform variable can
	 * only be obtained if the program is already linked, and one of its
	 * shaders actually contains such a variable.
	 *
	 * \param name The name of the variable
	 *
	 * \return The uniform variable
	 *
	 * \throw sge::renderer::glsl::exception if anything goes wrong
	*/
	virtual glsl::uniform::variable_ptr const
	uniform(
		glsl::string const &name
	) = 0;

	/**
	 * \brief Sets the vertex declaration to use
	 *
	 * Sets the vertex declaration to use to \a vertex_declaration. This
	 * must be done if the program is going to use vertex shaders and
	 * before it will be used by renderer::device::glsl_program. Initially,
	 * no vertex declaration is set.
	 *
	 * \param vertex_declaration The vertex declaration to use
	*/
	virtual void
	vertex_declaration(
		renderer::vertex_declaration const &vertex_declaration
	) = 0;

	/**
	 * \brief Attaches a shader to the program
	 *
	 * Attaches \a shader to the program. The shader must have been compiled
	 * beforehand. This will only take effect when the program is linked.
	 *
	 * \see sge::renderer::glsl::scoped_attachment
	 *
	 * \warning The behaviour is undefined if a shader is attached multiple
	 * times without being detached first.
	*/
	virtual void
	attach_shader(
		glsl::shader const &shader
	) = 0;

	/**
	 * \brief Detaches a shader from the program
	 *
	 * Detached \a shader from the program. This will only take effect when
	 * the program is linked.
	 *
	 * \warning The behaviour is undefined if the shader is not attached.
	*/
	virtual void
	detach_shader(
		glsl::shader const &
	) = 0;

	/**
	 * \brief Sets a location for a color surface
	 *
	 * Sets the location for a color surface for \a stage to \a location.
	 * The location can then be used inside a program to render to the nth
	 * color surface. Initially, no locations are set.
	*/
	virtual void
	color_surface_location(
		renderer::texture::stage,
		glsl::string const &location
	) = 0;

	/**
	 * \brief Links the program
	 *
	 * Links all currently attached shaders of the program. This must be
	 * done before the program can be used by a renderer::device.
	 *
	 * \throw sge::renderer::glsl::exception if anything goes wrong
	*/
	virtual void
	link() = 0;

	/**
	 * \brief Returns the info log
	 *
	 * The info log contains information about errors that might have
	 * occured while construction the program, especially if a call to link
	 * failed.
	*/
	virtual fcppt::string const
	info_log() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~program() = 0;
};

}
}
}

#endif
