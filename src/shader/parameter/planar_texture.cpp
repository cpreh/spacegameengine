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


#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>


sge::shader::parameter::planar_texture::planar_texture(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	sge::shader::pair &_parent,
	sge::renderer::device::core &_renderer,
	optional_value const &_value)
:
	parent_(
		_parent),
	renderer_(
		_renderer),
	parameter_(
		_program.parameter(
			_name.get())),
	loaded_texture_(),
	scoped_texture_(),
	optional_render_context_(),
	value_(
		_value)
{
	parent_.add_planar_texture(
		*this);
}

void
sge::shader::parameter::planar_texture::set(
	optional_value const &_value)
{
	value_ =
		_value;

	if(optional_render_context_)
	{
		scoped_texture_.reset();

		loaded_texture_.reset();

		if(value_)
		{
			loaded_texture_.take(
				renderer_.load_cg_texture(
					parameter_.object(),
					*_value));

			scoped_texture_.take(
				fcppt::make_unique_ptr<sge::renderer::cg::scoped_texture>(
					*optional_render_context_,
					*loaded_texture_));
		}
	}
}

void
sge::shader::parameter::planar_texture::activate(
	sge::renderer::context::core &_render_context)
{
	FCPPT_ASSERT_PRE(
		!optional_render_context_);

	FCPPT_ASSERT_PRE(
		!scoped_texture_);

	optional_render_context_ =
		optional_render_context(
			_render_context);

	this->set(
		value_);
}

void
sge::shader::parameter::planar_texture::deactivate()
{
	FCPPT_ASSERT_PRE(
		optional_render_context_);

	scoped_texture_.reset();
	loaded_texture_.reset();
	optional_render_context_ =
		optional_render_context();
}

sge::shader::parameter::planar_texture::optional_loaded_texture
sge::shader::parameter::planar_texture::loaded_texture()
{
	return
		loaded_texture_
		?
			sge::shader::parameter::planar_texture::optional_loaded_texture(
				*loaded_texture_)
		:
			sge::shader::parameter::planar_texture::optional_loaded_texture();
}

sge::renderer::texture::stage const
sge::shader::parameter::planar_texture::stage() const
{
	FCPPT_ASSERT_PRE(
		scoped_texture_);
	return
		scoped_texture_->stage();
}

sge::shader::parameter::planar_texture::~planar_texture()
{
	parent_.remove_planar_texture(
		*this);
}
