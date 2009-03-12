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


#include "../object.hpp"
#include "../vertex_format.hpp"
#include <sge/math/pi.hpp>
#include <sge/log/headers.hpp>
#include <sge/renderer/vf/dynamic_view.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/view_size.hpp>
#include <sge/renderer/index/make_const_view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/istream_util.hpp>
#include <boost/tr1/array.hpp>
#include <boost/foreach.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <ios>
#include <algorithm>
#include <cmath>

namespace
{

unsigned const max_qpath = 64;

sge::md3::funit const
xyz_scale(
	static_cast<sge::md3::funit>(1)
	/ static_cast<sge::md3::funit>(64)
);

}

sge::md3::object::object(
	model::istream &is)
:
	vertices_(0),
	indices_(0)
{
	model::istream::off_type const start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(SGE_TEXT("Invalid md3 format!"));

	s32 const version = read<s32>(is);
	if(version != 15)
		SGE_LOG_WARNING(
			log::global(),
			log::_1 << SGE_TEXT("md3 version is not 15 but continuing anyway.")
		);

	name_ = read_string<max_qpath>(is);

	read<s32>(is); // flags

	s32 const
		num_frames = read<s32>(is),
		num_tags     = read<s32>(is),
		num_surfaces = read<s32>(is);
	
	read<s32>(is); // num_skins
	
	s32 const
		ofs_frames   = read<s32>(is),
		ofs_tags     = read<s32>(is),
		ofs_surfaces = read<s32>(is),
		ofs_eof      = read<s32>(is);

	is.seekg(start + ofs_frames, std::ios_base::beg);
	for(s32 i = 0; i < num_frames; ++i)
		frames.push_back(frame(is));

	is.seekg(start + ofs_tags, std::ios_base::beg);
	for(s32 i = 0; i < num_tags; ++i)
		tags.push_back(tag(is));

	is.seekg(start + ofs_surfaces, std::ios_base::beg);
	for(s32 i = 0; i < num_surfaces; ++i)
	{
		surfaces.push_back(surface(is, num_frames));
		surface const &s = surfaces.back();
		indices_ += s.triangles.size();
		vertices_ += s.transformed_vertices.size();
	}
	indices_ *= 3;

	is.seekg(start + ofs_eof);
}

sge::renderer::vf::dynamic_format const
sge::md3::object::format() const
{
	static renderer::vf::dynamic_format const fmt(
		renderer::vf::make_dynamic_format<
			vertex_format
		>()
	);

	return fmt;
}

sge::renderer::size_type
sge::md3::object::vertices() const
{
	return vertices_;
}

sge::renderer::size_type
sge::md3::object::indices() const
{
	return indices_;
}

void
sge::md3::object::copy_vertices(
	renderer::vf::dynamic_view const &view)
{
	if(vertices() > view.size())
		throw exception(
			SGE_TEXT("md3::object::copy_vertices(): view too small!")
		);

	typedef renderer::vf::view<
		vertex_format	
	> vertex_view;
		
	vertex_view const vertices(
		view	
	);

	vertex_view::iterator vbit = vertices.begin();

	BOOST_FOREACH(
		surface_vector::const_reference surf,
		surfaces
	)
		for(
			surface::transformed_vertex_vector::size_type sz = 0;
			sz < surf.transformed_vertices.size();
			++sz, ++vbit
		)
		{
			surface::transformed_vertex const &v(
				surf.transformed_vertices[
					sz
				]
			);

			(*vbit).set<vertex_pos>(v.pos);
			(*vbit).set<vertex_normal>(v.normal);
			(*vbit).set<vertex_texpos>(surf.st.at(sz).tex); // TODO: this may be wrong?
		}
}

// TODO: split this, too!
namespace
{

struct index_visitor : boost::static_visitor<> {
	explicit index_visitor(
		sge::md3::object::surface_vector const &surfaces_)
	:
		surfaces_(surfaces_)
	{}
	
	template<
		typename T
	>
	void operator()(
		T const &t) const
	{
	
		sge::renderer::size_type ib_offset(0);
		typedef typename T::value_type value_type;
		typename T::iterator it = t.begin();
		BOOST_FOREACH(
			sge::md3::object::surface_vector::const_reference surf,
			surfaces_
		)
		{
			BOOST_FOREACH(
				sge::md3::object::surface::triangle_vector::const_reference r,
				surf.triangles
			)
			{
				BOOST_FOREACH(
					sge::md3::object::surface::triangle::index_array::const_reference ind,
					r.indices
				)
					*it++ = static_cast<value_type>(ind + ib_offset);
			}
			ib_offset += static_cast<sge::renderer::size_type>(
				surf.transformed_vertices.size()
			);
		}
	}
private:
	sge::md3::object::surface_vector const &surfaces_;	
};

}

void
sge::md3::object::copy_indices(
	renderer::index::view const &view)
{
	if(
		indices() > renderer::index::view_size(
			renderer::index::make_const_view(
				view
			)
		)
	)
		throw exception(
			SGE_TEXT("md3::object::copy_indices(): view tool small!")
		);

	boost::apply_visitor(
		index_visitor(
			surfaces
		),
		view
	);
}


bool sge::md3::object::read_and_check_id3p(model::istream& is)
{
	typedef std::tr1::array<u8, 4> id3p_array;
	id3p_array id3p,
	           to_check = { { 0x49, 0x44, 0x50, 0x33 } };
	for(id3p_array::iterator i = id3p.begin(); i != id3p.end(); ++i)
		*i = read<u8>(is);
	return std::equal(id3p.begin(), id3p.end(), to_check.begin());
}

template<
	sge::md3::object::string::size_type Max
>
inline sge::md3::object::string const
sge::md3::object::read_string(model::istream& is)
{
	std::tr1::array<u8, Max> tmp_name;
	is.read(reinterpret_cast<char*>(tmp_name.c_array()), tmp_name.size());

	if(!std::count(tmp_name.begin(), tmp_name.end(), 0))
		throw exception(SGE_TEXT("String in md3 file not ended with a 0!"));

	return tmp_name.data();
}

inline sge::md3::object::vec3 sge::md3::object::convert_normal(const s16 normal)
{
	funit const
		lat = static_cast<funit>((normal >> 8) & 255) * (math::twopi<funit>()) / 255,
		lng = static_cast<funit>(normal & 255) * (math::twopi<funit>()) / 255;

	return vec3(
		std::cos(lat) * std::sin(lng),
		std::sin(lat) * std::sin(lng),
		std::cos(lng)
	);
}

inline sge::md3::object::vec3
sge::md3::object::read_vec3(
	model::istream &is)
{
	return vec3(
		read<funit>(is),
		read<funit>(is),
		read<funit>(is)
	);
}

inline sge::md3::object::frame::frame(
	model::istream &is)
:
	min_bounds(read_vec3(is)),
	max_bounds(read_vec3(is)),
	local_origin(read_vec3(is)),
	radius(read<funit>(is)),
	name(read_string<16>(is))
{}

inline sge::md3::object::tag::tag(model::istream& is)
:
	name(read_string<max_qpath>(is)),
	origin(read_vec3(is))
{
	for(axis_array::iterator i = axis.begin(); i != axis.end(); ++i)
		*i = read_vec3(is);
}

inline sge::md3::object::surface::surface(model::istream& is, const s32 num_frames_head)
{
	const model::istream::off_type start = is.tellg();

	if(!read_and_check_id3p(is))
		throw exception(SGE_TEXT("Invalid md3 surface!"));

	name = read_string<max_qpath>(is);
	read<s32>(is); // flags

	const s32 num_frames    = read<s32>(is);

	if(num_frames != num_frames_head)
		throw exception(SGE_TEXT("num_frames mismatch in md3::object::surface!"));

	s32 const
		num_shaders   = read<s32>(is),
		num_verts     = read<s32>(is),
		num_triangles = read<s32>(is),
		ofs_triangles = read<s32>(is),
		ofs_shaders   = read<s32>(is),
		ofs_st        = read<s32>(is),
		ofs_xyznormal = read<s32>(is),
		ofs_end       = read<s32>(is);

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
				vertex(is)
			)
		);

	is.seekg(start + ofs_end, std::ios_base::beg);
}

sge::md3::object::surface::shader::shader(
	model::istream &is)
:
	name(read_string<max_qpath>(is)),
	shader_index(read<s32>(is))
{}

sge::md3::object::surface::triangle::triangle(
	model::istream& is)
{
	for(index_array::iterator i = indices.begin(); i != indices.end(); ++i)
		*i = read<s32>(is);
}

sge::md3::object::surface::texcoord::texcoord(
	model::istream& is)
:
	tex(read<funit>(is), read<funit>(is))
{}

sge::md3::object::surface::vertex::vertex(
	model::istream& is)
:
	x(read<s16>(is)),
	y(read<s16>(is)),
	z(read<s16>(is)),
	normal(read<s16>(is))
{}

sge::md3::object::surface::transformed_vertex::transformed_vertex(
	vertex const &v)
:
	pos(
		static_cast<funit>(v.x) * xyz_scale,
		static_cast<funit>(v.y) * xyz_scale,
		static_cast<funit>(v.z) * xyz_scale
	),
	normal(
		convert_normal(
			v.normal
		)
	)
{}
