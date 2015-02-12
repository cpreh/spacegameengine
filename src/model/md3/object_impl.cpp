/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/optional_normal_sequence.hpp>
#include <sge/model/md3/optional_texcoord_sequence.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/src/model/md3/endian.hpp>
#include <sge/src/model/md3/frame.hpp>
#include <sge/src/model/md3/logger.hpp>
#include <sge/src/model/md3/max_qpath.hpp>
#include <sge/src/model/md3/object_impl.hpp>
#include <sge/src/model/md3/read_and_check_id3p.hpp>
#include <sge/src/model/md3/read_s32.hpp>
#include <sge/src/model/md3/read_string.hpp>
#include <sge/src/model/md3/surface.hpp>
#include <sge/src/model/md3/surface_vector.hpp>
#include <sge/src/model/md3/tag.hpp>
#include <sge/src/model/md3/transformed_vertex.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_exn.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::model::md3::object_impl::object_impl(
	std::istream &_stream,
	sge::model::md3::load_flags const _flags
)
:
	vertices_{
		0
	},
	indices_{
		0
	},
	name_(),
	frames_(),
	tags_(),
	surfaces_()
{
	std::istream::off_type const start(
		_stream.tellg()
	);

	if(
		!sge::model::md3::read_and_check_id3p(
			_stream
		)
	)
		throw sge::model::md3::exception(
			FCPPT_TEXT("Invalid md3 format!")
		);

	sge::model::md3::s32 const version(
		md3::read_s32(
			_stream
		)
	);

	if(
		version != 15
	)
	{
		FCPPT_LOG_WARNING(
			sge::model::md3::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("md3 version is not 15 but continuing anyway.")
		);
	}

	name_ =
		sge::model::md3::read_string<
			sge::model::md3::max_qpath::value
		>(
			_stream
		);

	// flags
	sge::model::md3::read_s32(
		_stream
	);

	sge::model::md3::s32 const
		num_frames(
			sge::model::md3::read_s32(
				_stream
			)
		),
		num_tags(
			sge::model::md3::read_s32(
				_stream
			)
		),
		num_surfaces(
			sge::model::md3::read_s32(
				_stream
			)
		);

	// num_skins
	fcppt::io::read<
		sge::model::md3::s32
	>(
		_stream,
		sge::model::md3::endian()
	);

	s32 const
		ofs_frames(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_tags(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_surfaces(
			sge::model::md3::read_s32(
				_stream
			)
		),
		ofs_eof(
			sge::model::md3::read_s32(
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

	fcppt::algorithm::repeat(
		num_frames,
		[
			&_stream,
			this
		]
		{
			frames_.push_back(
				sge::model::md3::frame(
					_stream
				)
			);
		}
	);

	_stream.seekg(
		start
		+
		ofs_tags
		,
		std::ios_base::beg
	);

	fcppt::algorithm::repeat(
		num_tags,
		[
			&_stream,
			this
		]
		{
			tags_.push_back(
				sge::model::md3::tag(
					_stream
				)
			);
		}
	);

	_stream.seekg(
		start
		+
		ofs_surfaces
		,
		std::ios_base::beg
	);

	fcppt::algorithm::repeat(
		num_surfaces,
		[
			&_stream,
			_flags,
			num_frames,
			this
		]
		{
			surfaces_.push_back(
				sge::model::md3::surface(
					_stream,
					_flags,
					num_frames
				)
			);

			sge::model::md3::surface const &last_surface(
				surfaces_.back()
			);

			indices_ +=
				last_surface.triangles().size();

			vertices_ +=
				last_surface.transformed_vertices().size();
		}
	);

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

sge::model::md3::index_sequence
sge::model::md3::object_impl::indices(
	sge::model::md3::string const &_name
) const
{
	sge::model::md3::index_sequence result;

	sge::model::md3::index ib_offset(0);

	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	sge::model::md3::triangle_vector const &triangles(
		surf.triangles()
	);

	for(
		auto const &triangle
		:
		triangles
	)
		for(
			auto const &index
			:
			triangle.indices()
		)
			result.push_back(
				static_cast<
					sge::model::md3::index
				>(
					index
				)
				+ ib_offset
			);

	return result;
}

sge::model::md3::vertex_sequence
sge::model::md3::object_impl::vertices(
	sge::model::md3::string const &_name
) const
{
	return
		fcppt::algorithm::map<
			sge::model::md3::vertex_sequence
		>(
			this->surface_by_name(
				_name
			).transformed_vertices(),
			[](
				sge::model::md3::transformed_vertex const &_vertex
			)
			{
				return
					_vertex.pos();
			}
		);
}

sge::model::md3::optional_texcoord_sequence
sge::model::md3::object_impl::texcoords(
	sge::model::md3::string const &_name
) const
{
	sge::model::md3::surface_vector::const_reference surf(
		this->surface_by_name(
			_name
		)
	);

	return
		sge::model::md3::optional_texcoord_sequence(
			fcppt::algorithm::map<
				sge::model::md3::texcoord_sequence
			>(
				fcppt::make_int_range_count(
					surf.transformed_vertices().size()
				),
				[
					&surf
				](
					sge::model::md3::transformed_vertex_vector::size_type const _index
				)
				{

					return
						surf.texpos().at(
							_index
						).texcoord();
				}
			)
		);
}

sge::model::md3::optional_normal_sequence
sge::model::md3::object_impl::normals(
	sge::model::md3::string const &_name
) const
{
	return
		sge::model::md3::optional_normal_sequence(
			fcppt::algorithm::map<
				sge::model::md3::normal_sequence
			>(
				this->surface_by_name(
					_name
				).transformed_vertices(),
				[](
					sge::model::md3::transformed_vertex const &_vertex
				)
				{
					return
						_vertex.normal();
				}
			)
		);
}

sge::model::md3::part_name_sequence
sge::model::md3::object_impl::part_names() const
{
	return
		fcppt::algorithm::map<
			sge::model::md3::part_name_sequence
		>(
			surfaces_,
			[](
				sge::model::md3::surface const &_surface
			)
			{
				return
					_surface.name();
			}
		);
}


sge::model::md3::surface_vector::const_reference
sge::model::md3::object_impl::surface_by_name(
	sge::model::md3::string const &_name
) const
{
	return
		*fcppt::algorithm::find_if_exn(
			surfaces_,
			[
				&_name
			](
				sge::model::md3::surface const &_surface
			)
			{
				return
					_surface.name()
					==
					_name;
			},
			[]{
				return
					sge::model::md3::exception{
						FCPPT_TEXT("Couldn't find md3 surface!")
					};
			}
		);
}
