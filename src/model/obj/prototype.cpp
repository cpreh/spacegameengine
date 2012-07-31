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


#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/prototype.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/box/extend_bounding_box.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/filesystem/fstream.hpp>
#include <algorithm>
#include <string>
#include <fcppt/config/external_end.hpp>

#include <fcppt/config/external_begin.hpp>
#include <iostream>
#include <map>
#include <boost/unordered_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{
typedef
unsigned long
line_count;

sge::model::obj::face_vertex const
parse_face_vertex(
	line_count const _current_line,
	std::istream &_stream)
{
	std::size_t vertex_coordinate_index,texture_coordinate_index,normal_index;

	if(!(_stream >> vertex_coordinate_index))
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face index"));

	if(_stream.peek() != '/')
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face delimiter"));

	_stream.ignore();

	if(!(_stream >> texture_coordinate_index))
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face index"));

	if(_stream.peek() != '/')
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face delimiter"));

	_stream.ignore();

	if(!(_stream >> normal_index))
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face index"));

	return
		sge::model::obj::face_vertex(
			sge::model::obj::vertex_coordinate_index(
				vertex_coordinate_index),
			sge::model::obj::texture_coordinate_index(
				texture_coordinate_index),
			sge::model::obj::normal_index(
				normal_index));
}
}

sge::model::obj::prototype::prototype(
	boost::filesystem::path const &_filename)
:
	vertex_coordinates_(),
	texture_coordinates_(),
	normals_(),
	face_vertices_(),
	parts_(),
	material_files_(),
	bounding_box_(
		sge::model::obj::box::null())
{
	boost::filesystem::ifstream stream(
		_filename);

	if(!stream.is_open())
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					_filename)+
				FCPPT_TEXT("\""));

	typedef
		std::map<sge::model::obj::face_vertex,std::size_t>
		//boost::unordered_map<sge::model::obj::face_vertex,std::size_t>
	face_vertex_to_index_map;

	face_vertex_to_index_map face_vertex_to_index;

	line_count line_counter = 0;
	std::string current_material = "";
	std::string line;
	while(
		std::getline(
			stream,
			line))
	{
		if(line_counter % 100u == 0)
			std::cout << "\r" << line_counter;
		++line_counter;

		if(line.empty() || line[0] == '#')
			continue;

		std::string::size_type const first_space_position =
			line.find(' ');

		if(first_space_position == std::string::npos)
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::insert_to_fcppt_string(
						line_counter)+
					FCPPT_TEXT(": No prefix found."));

		std::string const prefix =
			line.substr(
				0,
				first_space_position);

		if(prefix[0] == 'o' || prefix[0] == 's' || prefix[0] == 'g')
			continue;

		std::string const rest_of_line(
			line.substr(
				first_space_position+1u));

		if(prefix == "mtllib")
		{
			material_files_.push_back(
				rest_of_line);
			continue;
		}

		if(prefix == "usemtl")
		{
			current_material =
				rest_of_line;
		}

		if(prefix == "v")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::vertex_coordinate coordinate;
			if(!(line_rest >> coordinate[0] >> coordinate[1] >> coordinate[2]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid coordinate(s)"));

			if(vertex_coordinates_.empty())
				bounding_box_.pos(
					coordinate);
			else
				bounding_box_ =
					fcppt::math::box::extend_bounding_box(
						bounding_box_,
						coordinate);

			vertex_coordinates_.push_back(
				coordinate);

			continue;
		}

		if(prefix == "vn")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::normal normal;
			if(!(line_rest >> normal[0] >> normal[1] >> normal[2]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid normal(s)"));

			normals_.push_back(
				normal);

			continue;
		}

		if(prefix == "vt")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::texture_coordinate tex_coord;
			if(!(line_rest >> tex_coord[0] >> tex_coord[1]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid tex coord(s)"));

			texture_coordinates_.push_back(
				tex_coord);

			continue;
		}

		if(prefix == "f")
		{
			std::istringstream line_rest(
				rest_of_line);

			typedef
			fcppt::container::array<sge::model::obj::face_vertex,3>
			face_vertex_array;

			face_vertex_array const temporary_face_vertices =
			{
				{
					parse_face_vertex(
						line_counter,
						line_rest),
					parse_face_vertex(
						line_counter,
						line_rest),
					parse_face_vertex(
						line_counter,
						line_rest)
				}
			};

			sge::model::obj::face face;

			for(std::size_t i = 0; i < temporary_face_vertices.size(); ++i)
			{
				face_vertex_to_index_map::iterator it =
					face_vertex_to_index.find(
						temporary_face_vertices[i]);

				/*
				sge::model::obj::face_vertex_sequence::iterator it =
					std::find(
						face_vertices_.begin(),
						face_vertices_.end(),
						temporary_face_vertices[i]);
						*/

				if(it == face_vertex_to_index.end())
				{
					face_vertices_.push_back(
						temporary_face_vertices[i]);

					it =
						face_vertex_to_index.insert(
							std::make_pair(
								temporary_face_vertices[i],
								static_cast<std::size_t>(
									face_vertices_.size()-1u))).first;
				}

				face[i] =
					it->second;
				/*
					static_cast<std::size_t>(
						std::distance(
							face_vertices_.begin(),
							it));
							*/
			}

			parts_[current_material].push_back(
				face);

			continue;
		}
	}

	std::cout << "\n";
}

sge::model::obj::vertex_coordinate_sequence const &
sge::model::obj::prototype::vertex_coordinates() const
{
	return
		vertex_coordinates_;
}

sge::model::obj::texture_coordinate_sequence const &
sge::model::obj::prototype::texture_coordinates() const
{
	return
		texture_coordinates_;
}

sge::model::obj::normal_sequence const &
sge::model::obj::prototype::normals() const
{
	return
		normals_;
}

sge::model::obj::face_vertex_sequence const &
sge::model::obj::prototype::face_vertices() const
{
	return face_vertices_;
}

sge::model::obj::material_to_face_sequence const &
sge::model::obj::prototype::parts() const
{
	return
		parts_;
}

std::size_t
sge::model::obj::prototype::face_count() const
{
	std::size_t result =
		0u;

	for(
		sge::model::obj::material_to_face_sequence::const_iterator it =
			this->parts().begin();
		it != this->parts().end();
		++it)
		result += it->second.size();

	return
		result;
}

sge::model::obj::material_file_sequence const &
sge::model::obj::prototype::material_files() const
{
	return
		material_files_;
}

sge::model::obj::box const &
sge::model::obj::prototype::bounding_box() const
{
	return
		bounding_box_;
}

sge::model::obj::prototype::~prototype()
{
}
