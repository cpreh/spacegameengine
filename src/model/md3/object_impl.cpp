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


#include <sge/log/global.hpp>
#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/optional_normal_sequence.hpp>
#include <sge/model/md3/optional_texcoord_sequence.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/src/model/md3/endian.hpp>
#include <sge/src/model/md3/frame.hpp>
#include <sge/src/model/md3/max_qpath.hpp>
#include <sge/src/model/md3/object_impl.hpp>
#include <sge/src/model/md3/read_and_check_id3p.hpp>
#include <sge/src/model/md3/read_s32.hpp>
#include <sge/src/model/md3/read_string.hpp>
#include <sge/src/model/md3/surface.hpp>
#include <sge/src/model/md3/surface_vector.hpp>
#include <sge/src/model/md3/tag.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::model::md3::object_impl::object_impl(
	std::istream &_stream,
	md3::load_flags::type const _flags
)
:
	vertices_(0),
	indices_(0)
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
			FCPPT_TEXT("Invalid md3 format!")
		);

	md3::s32 const version(
		md3::read_s32(
			_stream
		)
	);

	if(
		version != 15
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("md3 version is not 15 but continuing anyway.")
		);
	}

	name_ =
		md3::read_string<
			md3::max_qpath::value
		>(
			_stream
		);

	// flags
	md3::read_s32(
		_stream
	);

	md3::s32 const
		num_frames(
			md3::read_s32(
				_stream
			)
		),
		num_tags(
			md3::read_s32(
				_stream
			)
		),
		num_surfaces(
			md3::read_s32(
				_stream
			)
		);

	// num_skins
	fcppt::io::read<
		md3::s32
	>(
		_stream,
		md3::endian()
	);

	s32 const
		ofs_frames(
			md3::read_s32(
				_stream
			)
		),
		ofs_tags(
			md3::read_s32(
				_stream
			)
		),
		ofs_surfaces(
			md3::read_s32(
				_stream
			)
		),
		ofs_eof(
			md3::read_s32(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_frames
		,
		std::ios_base::beg
	);

	for(
		md3::s32 i = 0;
		i < num_frames;
		++i
	)
		frames_.push_back(
			md3::frame(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_tags
		,
		std::ios_base::beg
	);

	for(
		md3::s32 i = 0;
		i < num_tags;
		++i
	)
		tags_.push_back(
			md3::tag(
				_stream
			)
		);

	_stream.seekg(
		start
		+
		ofs_surfaces
		,
		std::ios_base::beg
	);

	for(
		md3::s32 i = 0;
		i < num_surfaces;
		++i
	)
	{
		surfaces_.push_back(
			md3::surface(
				_stream,
				_flags,
				num_frames
			)
		);

		md3::surface const &last_surface(
			surfaces_.back()
		);

		indices_ += last_surface.triangles().size();

		vertices_ += last_surface.transformed_vertices().size();
	}

	indices_ *= 3;

	_stream.seekg(
		start
		+
		ofs_eof
	);
}

sge::model::md3::object_impl::~object_impl()
{
}

sge::model::md3::index_sequence const
sge::model::md3::object_impl::indices(
	md3::string const &_name
) const
{
	md3::index_sequence result;

	md3::index ib_offset(0);

	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	sge::model::md3::triangle_vector const &triangles(
		surf.triangles()
	);

	for(
		sge::model::md3::triangle_vector::const_iterator triangle_it(
			triangles.begin()
		);
		triangle_it != triangles.end();
		++triangle_it
	)
		for(
			sge::model::md3::index_array::const_iterator index_it(
				triangle_it->indices().begin()
			);
			index_it != triangle_it->indices().end();
			++index_it
		)
			result.push_back(
				static_cast<
					md3::index
				>(
					*index_it
				)
				+ ib_offset
			);

	return result;
}

sge::model::md3::vertex_sequence const
sge::model::md3::object_impl::vertices(
	md3::string const &_name
) const
{
	md3::vertex_sequence result;

	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	for(
		md3::transformed_vertex_vector::const_iterator it(
			surf.transformed_vertices().begin()
		);
		it != surf.transformed_vertices().end();
		++it
	)
		result.push_back(
			fcppt::math::vector::structure_cast<
				md3::position
			>(
				it->pos()
			)
		);

	return result;
}

sge::model::md3::optional_texcoord_sequence const
sge::model::md3::object_impl::texcoords(
	md3::string const &_name
) const
{
	md3::texcoord_sequence result;

	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	for(
		md3::transformed_vertex_vector::size_type sz = 0;
		sz < surf.transformed_vertices().size();
		++sz
	)
		result.push_back(
			surf.texpos().at(
				sz
			).texcoord()
		);

	return
		sge::model::md3::optional_texcoord_sequence(
			result
		);
}

sge::model::md3::optional_normal_sequence const
sge::model::md3::object_impl::normals(
	md3::string const &_name
) const
{
	md3::normal_sequence result;

	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	for(
		md3::transformed_vertex_vector::const_iterator it(
			surf.transformed_vertices().begin()
		);
		it != surf.transformed_vertices().end();
		++it
	)
		result.push_back(
			it->normal()
		);

	return
		sge::model::md3::optional_normal_sequence(
			result
		);
}

sge::model::md3::part_name_sequence const
sge::model::md3::object_impl::part_names() const
{
	md3::part_name_sequence result;

	for(
		md3::surface_vector::const_iterator surface_it(
			surfaces_.begin()
		);
		surface_it != surfaces_.end();
		++surface_it
	)
		result.push_back(
			surface_it->name()
		);

	return result;
}


sge::model::md3::surface_vector::const_reference
sge::model::md3::object_impl::surface_by_name(
	md3::string const &_name
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
			surface_it->name() == _name
		)
			return *surface_it;

	throw sge::model::md3::exception(
		FCPPT_TEXT("Couldn't find md3 surface!")
	);
}
