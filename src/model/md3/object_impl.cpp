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


#include "object_impl.hpp"
#include <sge/log/global.hpp>
#include <sge/model/md3/exception.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <algorithm>
#include <ios>
#include <fstream>
#include <cmath>

namespace
{

unsigned const max_qpath = 64;

sge::model::md3::scalar const
xyz_scale(
	static_cast<sge::model::md3::scalar>(1)
	/ static_cast<sge::model::md3::scalar>(64)
);

fcppt::endianness::format::type const endian(
	fcppt::endianness::format::little
);

}

sge::model::md3::object_impl::object_impl(
	std::istream &is,
	md3::load_flags::type const lf
)
:
	vertices_(0),
	indices_(0)
{
	std::istream::off_type const start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(FCPPT_TEXT("Invalid md3 format!"));

	s32 const version = fcppt::io::read<s32>(is, endian);

	if(version != 15)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("md3 version is not 15 but continuing anyway.")
		);
	}

	name_ = read_string<max_qpath>(is);

	fcppt::io::read<s32>(is, endian); // flags

	s32 const
		num_frames = fcppt::io::read<s32>(is, endian),
		num_tags     = fcppt::io::read<s32>(is, endian),
		num_surfaces = fcppt::io::read<s32>(is, endian);

	fcppt::io::read<s32>(is, endian); // num_skins

	s32 const
		ofs_frames   = fcppt::io::read<s32>(is, endian),
		ofs_tags     = fcppt::io::read<s32>(is, endian),
		ofs_surfaces = fcppt::io::read<s32>(is, endian),
		ofs_eof      = fcppt::io::read<s32>(is, endian);

	is.seekg(start + ofs_frames, std::ios_base::beg);
	for(s32 i = 0; i < num_frames; ++i)
		frames_.push_back(frame(is));

	is.seekg(start + ofs_tags, std::ios_base::beg);
	for(s32 i = 0; i < num_tags; ++i)
		tags_.push_back(tag(is));

	is.seekg(start + ofs_surfaces, std::ios_base::beg);
	for(s32 i = 0; i < num_surfaces; ++i)
	{
		surfaces_.push_back(surface(is, lf, num_frames));
		surface const &s = surfaces_.back();
		indices_ += s.triangles.size();
		vertices_ += s.transformed_vertices.size();
	}
	indices_ *= 3;

	is.seekg(start + ofs_eof);
}

sge::model::md3::object_impl::~object_impl()
{
}

sge::model::md3::index_sequence const
sge::model::md3::object_impl::indices(
	fcppt::string const &_name
) const
{
	md3::index_sequence result;
	md3::index ib_offset(0);

	sge::model::md3::object_impl::surface_vector::const_reference surf(
		surface_by_name(
			_name
		)
	);

	for(
		sge::model::md3::object_impl::surface::triangle_vector::const_iterator triangle_it(
			surf.triangles.begin()
		);
		triangle_it != surf.triangles.end();
		++triangle_it
	)
	{
		for(
			sge::model::md3::object_impl::surface::triangle::index_array::const_iterator index_it(
				triangle_it->indices.begin()
			);
			index_it != triangle_it->indices.end();
			++index_it
		)
		{
			result.push_back(
				static_cast<
					md3::index
				>(
					*index_it
				)
				+ ib_offset
			);
		}
	}

	return result;
}

sge::model::md3::vertex_sequence const
sge::model::md3::object_impl::vertices(
	fcppt::string const &name) const
{
	md3::vertex_sequence result;

	sge::model::md3::object_impl::surface_vector::const_reference surf =
		surface_by_name(name);

	for(
		surface::transformed_vertex_vector::size_type sz = 0;
		sz < surf.transformed_vertices.size();
		++sz)
	{
		surface::transformed_vertex const &v(
			surf.transformed_vertices[sz]);

		result.push_back(
			fcppt::math::vector::structure_cast<md3::position>(
				v.pos));
	}

	return result;
}

fcppt::optional<sge::model::md3::texcoord_sequence> const
sge::model::md3::object_impl::texcoords(
	fcppt::string const &name) const
{
	md3::texcoord_sequence result;

	sge::model::md3::object_impl::surface_vector::const_reference surf =
		surface_by_name(name);

	for(
		surface::transformed_vertex_vector::size_type sz = 0;
		sz < surf.transformed_vertices.size();
		++sz)
	{
		result.push_back(
			static_cast<md3::texcoord>(
				surf.st.at(sz).tex));
	}

	return result;
}

fcppt::optional<sge::model::md3::normal_sequence> const
sge::model::md3::object_impl::normals(
	fcppt::string const &name) const
{
	md3::normal_sequence result;

	sge::model::md3::object_impl::surface_vector::const_reference surf =
		surface_by_name(name);

	for(
		surface::transformed_vertex_vector::size_type sz = 0;
		sz < surf.transformed_vertices.size();
		++sz
	)
	{
		surface::transformed_vertex const &v(
			surf.transformed_vertices[sz]);

		result.push_back(
			v.normal);
	}

	return result;
}

sge::model::md3::part_name_sequence const
sge::model::md3::object_impl::part_names() const
{
	md3::part_name_sequence result;

	for(
		surface_vector::const_iterator surface_it(
			surfaces_.begin()
		);
		surface_it != surfaces_.end();
		++surface_it
	)
		result.push_back(
			surface_it->name);
	return result;
}


bool sge::model::md3::object_impl::read_and_check_id3p(std::istream& is)
{
	typedef fcppt::container::array<u8, 4> id3p_array;
	id3p_array id3p,
	           to_check = { { 0x49, 0x44, 0x50, 0x33 } };
	for(id3p_array::iterator i = id3p.begin(); i != id3p.end(); ++i)
		*i = fcppt::io::read<u8>(is, endian);
	return std::equal(id3p.begin(), id3p.end(), to_check.begin());
}

template<
	sge::model::md3::object_impl::string::size_type Max
>
inline sge::model::md3::object_impl::string const
sge::model::md3::object_impl::read_string(
	std::istream &_stream
)
{
	fcppt::container::array<
		string::value_type,
		Max
	> tmp_name;

	_stream.read(
		reinterpret_cast<
			char *
		>(
			tmp_name.data()
		),
		static_cast<
			std::streamsize
		>(
			tmp_name.size()
		)
	);

	if(
		!std::count(
			tmp_name.begin(),
			tmp_name.end(),
			0
		)
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("String in md3 file not ended with a 0!")
		);

	return tmp_name.data();
}

inline
sge::model::md3::object_impl::vec3 sge::model::md3::object_impl::convert_normal(
	s16 const _normal
)
{
	scalar const
		lat = static_cast<scalar>((_normal >> 8) & 255) * (fcppt::math::twopi<scalar>()) / 255,
		lng = static_cast<scalar>(_normal & 255) * (fcppt::math::twopi<scalar>()) / 255;

	return
		vec3(
			std::cos(lat) * std::sin(lng),
			std::sin(lat) * std::sin(lng),
			std::cos(lng)
		);
}

sge::model::md3::object_impl::surface_vector::const_reference
sge::model::md3::object_impl::surface_by_name(
	fcppt::string const &_name
) const
{
	for(
		surface_vector::const_iterator surface_it(
			surfaces_.begin()
		);
		surface_it != surfaces_.end();
		++surface_it
	)
		if(
			surface_it->name == _name
		)
			return *surface_it;

	throw sge::model::md3::exception(
		FCPPT_TEXT("Couldn't find surface called \"")
		+
		_name
		+
		FCPPT_TEXT('"')
	);
}


inline sge::model::md3::object_impl::vec3
sge::model::md3::object_impl::read_vec3(
	std::istream &is)
{
	return vec3(
		fcppt::io::read<scalar>(is, endian),
		fcppt::io::read<scalar>(is, endian),
		fcppt::io::read<scalar>(is, endian)
	);
}

inline sge::model::md3::object_impl::frame::frame(
	std::istream &is)
:
	min_bounds(read_vec3(is)),
	max_bounds(read_vec3(is)),
	local_origin(read_vec3(is)),
	radius(fcppt::io::read<scalar>(is, endian)),
	name(read_string<16>(is))
{}

inline sge::model::md3::object_impl::tag::tag(std::istream& is)
:
	name(read_string<max_qpath>(is)),
	origin(read_vec3(is))
{
	for(axis_array::iterator i = axis.begin(); i != axis.end(); ++i)
		*i = read_vec3(is);
}

inline sge::model::md3::object_impl::surface::surface(std::istream& is, md3::load_flags::type const lf, const s32 num_frames_head)
{
	const std::istream::off_type start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(FCPPT_TEXT("Invalid md3 surface!"));

	name = read_string<max_qpath>(is);
	fcppt::io::read<s32>(is, endian); // flags

	const s32 num_frames    = fcppt::io::read<s32>(is, endian);

	if(num_frames != num_frames_head)
		throw exception(FCPPT_TEXT("num_frames mismatch in md3::object_impl::surface!"));

	s32 const
		num_shaders   = fcppt::io::read<s32>(is, endian),
		num_verts     = fcppt::io::read<s32>(is, endian),
		num_triangles = fcppt::io::read<s32>(is, endian),
		ofs_triangles = fcppt::io::read<s32>(is, endian),
		ofs_shaders   = fcppt::io::read<s32>(is, endian),
		ofs_st        = fcppt::io::read<s32>(is, endian),
		ofs_xyznormal = fcppt::io::read<s32>(is, endian),
		ofs_end       = fcppt::io::read<s32>(is, endian);

	is.seekg(start + ofs_triangles, std::ios_base::beg);
	for(s32 i = 0; i < num_triangles; ++i)
		triangles.push_back(triangle(is));

	is.seekg(start + ofs_shaders, std::ios_base::beg);
	for(s32 i = 0; i < num_shaders; ++i)
		shaders.push_back(shader(is));

	is.seekg(start + ofs_st, std::ios_base::beg);
	for(s32 i = 0; i < num_verts; ++i)
		st.push_back(texcoord(is));

	is.seekg(start + ofs_xyznormal, std::ios_base::beg);
	for(s32 i = 0; i < num_verts; ++i)
		transformed_vertices.push_back(
			transformed_vertex(
				vertex(is,lf)
			)
		);

	is.seekg(start + ofs_end, std::ios_base::beg);
}

sge::model::md3::object_impl::surface::shader::shader(
	std::istream &is)
:
	name(read_string<max_qpath>(is)),
	shader_index(fcppt::io::read<s32>(is, endian))
{}

sge::model::md3::object_impl::surface::triangle::triangle(
	std::istream& is)
{
	for(index_array::iterator i = indices.begin(); i != indices.end(); ++i)
		*i = fcppt::io::read<s32>(is, endian);
}

sge::model::md3::object_impl::surface::texcoord::texcoord(
	std::istream& is)
:
	tex(
		fcppt::io::read<scalar>(is, endian),
		fcppt::io::read<scalar>(is, endian)
	)
{
	std::swap(tex.x(),tex.y());
}

sge::model::md3::object_impl::surface::vertex::vertex(
	std::istream& is,
	md3::load_flags::type const lf)
:
	x(fcppt::io::read<s16>(is, endian)),
	y(fcppt::io::read<s16>(is, endian)),
	z(fcppt::io::read<s16>(is, endian)),
	normal(fcppt::io::read<s16>(is, endian))
{
	switch (lf)
	{
		case md3::load_flags::none:
			break;
		case md3::load_flags::switch_yz:
			// Motivation for this strange stuff:
			//
			// We assume our md3 is aligned with z as the "up" axis. To
			// realign it, we rotate by 90 degrees on the x axis. This
			// corresponds to a rotation matrix:
			//
			//  1  0  0
			//  0  0  1
			//  0 -1  0
			//
			// After that, however, the z axis points to the wrong
			// direction (found empirically). So we rotate by 180 degrees
			// around the y axis, which corresponds to a rotation matrix
			//
			//  -1 0  0
			//  0  1  0
			//  0  0 -1
			//
			// Multiplying those with an arbitrary vector (x,y,z) results in:
			//
			// (-x,z,y)
			x = static_cast<s16>(-x);
			std::swap(y,z);
			break;
	}
}

sge::model::md3::object_impl::surface::transformed_vertex::transformed_vertex(
	vertex const &v)
:
	pos(
		static_cast<scalar>(v.x) * xyz_scale,
		static_cast<scalar>(v.y) * xyz_scale,
		static_cast<scalar>(v.z) * xyz_scale
	),
	normal(
		convert_normal(
			v.normal
		)
	)
{}


