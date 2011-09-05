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


#include "surface.hpp"
#include "endian.hpp"
#include "max_qpath.hpp"
#include "read_and_check_id3p.hpp"
#include "read_string.hpp"
#include "s32.hpp"
#include "shader.hpp"
#include "texpos.hpp"
#include "transformed_vertex.hpp"
#include "triangle.hpp"
#include "vertex.hpp"
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/exception.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>

sge::model::md3::surface::surface(
	std::istream &_stream,
	md3::load_flags::type const _flags,
	md3::s32 const _num_frames_head
)
{
	std::istream::off_type const start(
		_stream.tellg()
	);

	if(
		!md3::read_and_check_id3p(
			_stream
		)
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("Invalid md3 surface!")
		);

	name_ =
		md3::read_string<
			md3::max_qpath::value
		>(
			_stream
		);

	// flags
	fcppt::io::read<
		md3::s32
	>(
		_stream,
		md3::endian()
	);

	md3::s32 const num_frames(
		fcppt::io::read<
			md3::s32
		>(
			_stream,
			md3::endian()
		)
	);

	if(
		num_frames != _num_frames_head
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("num_frames mismatch in md3::surface!")
		);

	md3::s32 const
		num_shaders(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		num_verts(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		num_triangles(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		ofs_triangles(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		ofs_shaders(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				endian()
			)
		),
		ofs_st(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		ofs_xyznormal(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		),
		ofs_end(
			fcppt::io::read<
				md3::s32
			>(
				_stream,
				md3::endian()
			)
		);

	_stream.seekg(
		start
		+
		ofs_triangles
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_triangles;
		++i
	)
		triangles_.push_back(
			md3::triangle(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_shaders
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_shaders;
		++i
	)
		shaders_.push_back(
			md3::shader(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_st
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		texpos_.push_back(
			md3::texpos(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_xyznormal
		,
		std::ios_base::beg
	);

	for(
		s32 i = 0;
		i < num_verts;
		++i
	)
		transformed_vertices_.push_back(
			md3::transformed_vertex(
				md3::vertex(
					_stream,
					_flags
				)
			)
		);

	_stream.seekg(
		start
		+
		ofs_end
		,
		std::ios_base::beg
	);
}

sge::model::md3::string const &
sge::model::md3::surface::name() const
{
	return name_;
}

sge::model::md3::shader_vector const &
sge::model::md3::surface::shaders() const
{
	return shaders_;
}

sge::model::md3::triangle_vector const &
sge::model::md3::surface::triangles() const
{
	return triangles_;
}

sge::model::md3::texpos_vector const &
sge::model::md3::surface::texpos() const
{
	return texpos_;
}

sge::model::md3::transformed_vertex_vector const &
sge::model::md3::surface::transformed_vertices() const
{
	return transformed_vertices_;
}
