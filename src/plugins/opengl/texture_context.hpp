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


#ifndef SGE_OPENGL_TEXTURE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONTEXT_HPP_INCLUDED

#include "context/base.hpp"
#include "context/id.hpp"
#include "common.hpp"
#include <sge/renderer/stage_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace opengl
{

class texture_context
:
	public context::base
{
	FCPPT_NONCOPYABLE(
		texture_context
	);
public:
	texture_context();

	~texture_context();

	bool
	anisotropic_filter_supported() const;

	bool
	generate_mipmap_flag_supported() const;

	GLenum
	anisotropy_flag() const;

	GLenum
	max_anisotropy_flag() const;

	typedef std::vector<
		GLenum
	> texture_type_vector;

	void
	last_type(
		GLenum,
		sge::renderer::stage_type
	);

	GLenum
	last_type(
		sge::renderer::stage_type
	) const;

	static GLenum const invalid_type;

	typedef void needs_before;

	static context::id const static_id;
private:
	bool const
		anisotropic_filter_supported_,
		generate_mipmap_flag_supported_;
	
	GLenum const
		anisotropy_flag_,
		max_anisotropy_flag_;
	
	texture_type_vector last_types_;
};

}
}

#endif
