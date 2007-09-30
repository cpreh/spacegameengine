/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <cstddef>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "../md3.hpp"
#include "../../math/constants.hpp"
#include "../../exception.hpp"
#include "../../istream.hpp"

const std::size_t max_qpath = 64;

const sge::space_unit MD3_XYZ_SCALE = 1.0/64;

sge::md3_model::md3_model(std::istream& is)
{
	const std::istream::off_type start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception("Invalid md3 format!");

	const s32 version = read<s32>(is);
	if(version != 15)
		std::cerr << "md3 version is not 15 but continuing anyway...\n";

	name_ = read_string<max_qpath>(is);

	read<s32>(is); // flags

	const s32 num_frames   = read<s32>(is);
	const s32 num_tags     = read<s32>(is);
	const s32 num_surfaces = read<s32>(is);
	                         read<s32>(is); // num_skins
	const s32 ofs_frames   = read<s32>(is);
	const s32 ofs_tags     = read<s32>(is);
	const s32 ofs_surfaces = read<s32>(is);
	const s32 ofs_eof      = read<s32>(is);

	is.seekg(start + ofs_frames, std::ios_base::beg);
	for(s32 i = 0; i < num_frames; ++i)
		frames.push_back(frame(is));

	is.seekg(start + ofs_tags, std::ios_base::beg);
	for(s32 i = 0; i < num_tags; ++i)
		tags.push_back(tag(is));

	is.seekg(start + ofs_surfaces, std::ios_base::beg);
	for(s32 i = 0; i < num_surfaces; ++i)
		surfaces.push_back(surface(is, num_frames));

	is.seekg(start + ofs_eof);
}

bool sge::md3_model::read_and_check_id3p(std::istream& is)
{
	boost::array<u8, 4> id3p;
	for(unsigned i = 0; i < id3p.size(); ++i)
		id3p[i] = read<u8>(is);
	return id3p[0] == 0x49 && id3p[1] == 0x44 && id3p[2] == 0x50 && id3p[3] == 0x33;
}

template<std::size_t Max>
inline sge::md3_model::string_type sge::md3_model::read_string(std::istream& is)
{
	boost::array<u8, Max> tmp_name;
	is.read(reinterpret_cast<char*>(tmp_name.c_array()), tmp_name.size());

	if(!std::count(tmp_name.begin(), tmp_name.end(), 0))
		throw exception("String in md3 file not ended with a 0!");

	return tmp_name.data();
}

inline sge::md3_model::vec3 sge::md3_model::convert_normal(const s16 normal)
{
	using std::sin;
	using std::cos;

	const space_unit lat = ((normal >> 8) & 255) * (2 * math::pi<space_unit>()) / 255,
	                 lng = (normal & 255) * (2 * math::pi<space_unit>()) / 255;

	return vec3(cos(lat) * sin(lng),
	            sin(lat) * sin(lng),
	            cos(lng));
}

inline sge::md3_model::vec3 sge::md3_model::read_vec3(std::istream& is)
{
	return vec3(read<f32>(is), read<f32>(is), read<f32>(is));
}

inline sge::md3_model::frame::frame(std::istream& is)
: min_bounds(read_vec3(is)),
  max_bounds(read_vec3(is)),
  local_origin(read_vec3(is)),
  radius(read<f32>(is)),
  name(read_string<16>(is))
{}

inline sge::md3_model::tag::tag(std::istream& is)
: name(read_string<max_qpath>(is)),
  origin(read_vec3(is))
{
	for(unsigned i = 0; i < axis.size(); ++i)
		axis[i] = read_vec3(is);
}

inline sge::md3_model::surface::surface(std::istream& is, const s32 num_frames_head)
{
	const std::istream::off_type start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception("Invalid md3 surface!");

	name = read_string<max_qpath>(is);
	read<s32>(is); // flags

	const s32 num_frames    = read<s32>(is);

	if(num_frames != num_frames_head)
		throw exception("num_frames mismatch in md3_model::surface!");

	const s32 num_shaders   = read<s32>(is);
	const s32 num_verts     = read<s32>(is);
	const s32 num_triangles = read<s32>(is);
	const s32 ofs_triangles = read<s32>(is);
	const s32 ofs_shaders   = read<s32>(is);
	const s32 ofs_st        = read<s32>(is);
	const s32 ofs_xyznormal = read<s32>(is);
	const s32 ofs_end       = read<s32>(is);

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
		transformed_vertices.push_back(vertex(is));

	is.seekg(start + ofs_end, std::ios_base::beg);
}

sge::md3_model::surface::shader::shader(std::istream& is)
: name(read_string<max_qpath>(is)),
  shader_index(read<s32>(is))
{}

sge::md3_model::surface::triangle::triangle(std::istream& is)
{
	for(unsigned i = 0; i < indices.size(); ++i)
		indices[i] = read<s32>(is);
}

sge::md3_model::surface::texcoord::texcoord(std::istream& is)
: tex(read<f32>(is), read<f32>(is))
{}

sge::md3_model::surface::vertex::vertex(std::istream& is)
: x(read<s16>(is)),
  y(read<s16>(is)),
  z(read<s16>(is)),
  normal(read<s16>(is))
{}

sge::md3_model::surface::transformed_vertex::transformed_vertex(const vertex& v)
: pos(v.x * MD3_XYZ_SCALE,
      v.y * MD3_XYZ_SCALE,
      v.z * MD3_XYZ_SCALE),
  normal(convert_normal(v.normal))
{}
