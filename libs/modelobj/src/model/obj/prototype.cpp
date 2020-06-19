//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/face_vertex.hpp>
#include <sge/model/obj/face_vertex_hash.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/model/obj/impl/log_name.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/box/extend_bounding_box.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace
{

using
line_count
=
std::uint64_t;

sge::model::obj::face_vertex
parse_face_vertex(
	line_count const _current_line,
	std::istream &_stream
)
{
	std::size_t vertex_coordinate_index; // NOLINT(cppcoreguidelines-init-variables)

	if(!(_stream >> vertex_coordinate_index))
	{
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::output_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face index"));
	}

	if(_stream.peek() != '/')
	{
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::output_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face delimiter (vertex)"));
	}

	_stream.ignore();

	std::size_t texture_coordinate_index; // NOLINT(cppcoreguidelines-init-variables)

	// No texture coordinate
	if(_stream.peek() == '/')
	{
		texture_coordinate_index =
			1U;
	}
	else
	{
		if(!(_stream >> texture_coordinate_index))
		{
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::output_to_fcppt_string(
						_current_line)+
					FCPPT_TEXT(": Invalid face index (texture coordinate)"));
		}
	}

	if(_stream.peek() != '/')
	{
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::output_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face delimiter (normal)"));
	}

	_stream.ignore();

	std::size_t normal_index; // NOLINT(cppcoreguidelines-init-variables)

	if(!(_stream >> normal_index))
	{
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::output_to_fcppt_string(
					_current_line)+
				FCPPT_TEXT(": Invalid face index"));
	}

	return
		sge::model::obj::face_vertex(
			sge::model::obj::vertex_coordinate_index(
				vertex_coordinate_index-1U),
			sge::model::obj::texture_coordinate_index(
				texture_coordinate_index-1U),
			sge::model::obj::normal_index(
				normal_index-1U));
}
}

sge::model::obj::prototype::prototype(
	fcppt::log::context_reference const _log_context,
	std::filesystem::path const &_filename
)
:
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			sge::model::obj::impl::log_name()
		)
	},
	vertex_coordinates_(),
	texture_coordinates_(),
	normals_(),
	face_vertices_(),
	parts_(),
	material_files_(),
	bounding_box_(
		fcppt::math::box::null<
			sge::model::obj::box
		>()
	)
{
	std::ifstream stream(
		_filename);

	if(!stream.is_open())
	{
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					_filename)+
				FCPPT_TEXT("\""));
	}

	using
	face_vertex_to_index_map
	=
	std::unordered_map<
		sge::model::obj::face_vertex,
		std::size_t
	>;

	std::filesystem::path const _obj_file_path(
		_filename.parent_path());

	face_vertex_to_index_map face_vertex_to_index;

	line_count line_counter = 0U;

	sge::model::obj::identifier current_material{
		sge::charconv::utf8_string{}
	};

	std::string line;
	while(
		std::getline(
			stream,
			line))
	{
		++line_counter;

		if(line.empty() || line[0] == '#')
		{
			continue;
		}

		std::string::size_type const first_space_position =
			line.find(' ');

		if(first_space_position == std::string::npos)
		{
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::output_to_fcppt_string(
						line_counter)+
					FCPPT_TEXT(": No prefix found."));
		}

		std::string const prefix =
			line.substr(
				0,
				first_space_position);

		if(prefix[0] == 'o' || prefix[0] == 's' || prefix[0] == 'g')
		{
			continue;
		}

		std::string const rest_of_line(
			line.substr(
				first_space_position+1U));

		if(prefix == "mtllib")
		{
			material_files_.push_back(
				_obj_file_path / rest_of_line);
		}
		else if(prefix == "usemtl")
		{
			current_material =
				sge::model::obj::identifier{
					sge::charconv::utf8_string{
						rest_of_line.begin(),
						rest_of_line.end()
					}
				};
		}
		else if(prefix == "v")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::vertex_coordinate coordinate{
				fcppt::no_init()};

			if(!(line_rest >> coordinate.x() >> coordinate.y() >> coordinate.z()))
			{
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::output_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid coordinate(s)"));
			}

			// Flip z
			coordinate.z() = -coordinate.z();

			if(vertex_coordinates_.empty())
			{
				bounding_box_ =
					sge::model::obj::box(
						coordinate,
						fcppt::math::dim::null<
							sge::model::obj::box::dim
						>()
					);
			}
			else
			{
				bounding_box_ =
					fcppt::math::box::extend_bounding_box(
						bounding_box_,
						coordinate);
			}

			vertex_coordinates_.push_back(
				coordinate);
		}
		else if(prefix == "vn")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::normal normal{
				fcppt::no_init()};

			if(!(line_rest >> normal.x() >> normal.y() >> normal.z()))
			{
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::output_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid normal(s)"));
			}

			// Flip z
			normal.z() = -normal.z();

			normals_.push_back(
				normal);
		}
		else if(prefix == "vt")
		{
			std::istringstream line_rest(
				rest_of_line);

			sge::model::obj::texture_coordinate tex_coord{
				fcppt::no_init()};

			if(!(line_rest >> tex_coord.x() >> tex_coord.y()))
			{
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::output_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid tex coord(s)"));
			}

			// Flip y
			texture_coordinates_.push_back(
				sge::renderer::vector2(
					tex_coord.x(),
					//1.0f - tex_coord.y()));
					1.0F - tex_coord.y()));
		}
		else if(prefix == "f")
		{
			std::istringstream line_rest(
				rest_of_line);

			using
			face_vertex_array
			=
			std::array<sge::model::obj::face_vertex,3>;

			face_vertex_array const temporary_face_vertices{{
				parse_face_vertex(
					line_counter,
					line_rest),
				parse_face_vertex(
					line_counter,
					line_rest),
				parse_face_vertex(
					line_counter,
					line_rest)
			}};

			sge::model::obj::face face;

			for(std::size_t i = 0; i < temporary_face_vertices.size(); ++i)
			{
				auto it =
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
									face_vertices_.size()-1U))).first;
				}

				// Flip triangle order
				face[2U - i] =
				//face[i] =
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
		}
		else
		{
			FCPPT_LOG_WARNING(
				log_,
				fcppt::log::out
					<<
					FCPPT_TEXT("Invalid obj prefix: ")
					<<
					fcppt::from_std_string(
						prefix
					)
			)
		}
	}

	if(texture_coordinates_.empty())
	{
		texture_coordinates_.push_back(
			fcppt::math::vector::null<
				sge::renderer::vector2
			>()
		);
	}
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
		0U;

	for(
		auto const &part : parts()
	)
	{
		result += part.second.size();
	}

	return
		result;
}

sge::model::obj::material::file_sequence const &
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
= default;
