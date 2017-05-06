/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/media_path.hpp>
#include <sge/model/obj/material_to_face_sequence.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/prototype.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/default_level_streams.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdlib>
#include <iostream>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	fcppt::log::context log_context{
		fcppt::log::optional_level{
			fcppt::log::level::debug
		},
		fcppt::log::default_level_streams()
	};

	sge::model::obj::prototype const loaded_model{
		log_context,
		sge::config::media_path()
		/
		FCPPT_TEXT("objs")
		/
		FCPPT_TEXT("Monkey.obj")
	};

	fcppt::io::cout()
		<<
		FCPPT_TEXT("Loaded successfully!\n")
		<<
		FCPPT_TEXT("Would produce: ")
		<<
		(loaded_model.face_count() * 3u)
		<<
		FCPPT_TEXT(" indices\n")
		<<
		FCPPT_TEXT("Has: ")
		<<
		loaded_model.face_vertices().size()
		<<
		FCPPT_TEXT(" face vertices\n")
		<<
		FCPPT_TEXT("Bounding box: ")
		<<
		loaded_model.bounding_box()
		<<
		FCPPT_TEXT('\n');

	if(
		loaded_model.material_files().empty()
	)
	{
		fcppt::io::cout()
			<<
			FCPPT_TEXT("No material files\n");
	}
	else
	{
		fcppt::io::cout()
			<<
			FCPPT_TEXT("Material files:\n");

		for(
			boost::filesystem::path const &path
			:
			loaded_model.material_files()
		)
		{
			fcppt::io::cout()
				<<
				fcppt::filesystem::path_to_string(
					path
				)
				<<
				FCPPT_TEXT('\n')
				<<
				FCPPT_TEXT("Loading...\n");

			sge::model::obj::parse_mtllib(
				log_context,
				sge::config::media_path()
				/
				FCPPT_TEXT("mtls")
				/
				path
			);
		}
	}

	fcppt::io::cout()
		<<
		FCPPT_TEXT("Vertices/texcoords/normals: ")
		<<
		loaded_model.vertex_coordinates().size()
		<<
		FCPPT_TEXT('/')
		<<
		loaded_model.texture_coordinates().size()
		<<
		FCPPT_TEXT('/')
		<<
		loaded_model.normals().size()
		<<
		FCPPT_TEXT('\n');

	fcppt::io::cout()
		<<
		FCPPT_TEXT("First vertex/texcoord/normal: ")
		<<
		loaded_model.vertex_coordinates().front()
		<<
		FCPPT_TEXT('/')
		<<
		loaded_model.texture_coordinates().front()
		<<
		FCPPT_TEXT('/')
		<<
		loaded_model.normals().front()
		<<
		FCPPT_TEXT('\n');

	fcppt::io::cout()
		<<
		FCPPT_TEXT("Parts:\n");

	for(
		sge::model::obj::material_to_face_sequence::value_type const &pair
		:
		loaded_model.parts()
	)
	{
		if(
			pair.first.get().empty()
		)
			fcppt::io::cout()
				<<
				FCPPT_TEXT("\tDefault material\n");
		else
			fcppt::io::cout()
				<<
				FCPPT_TEXT("\tMaterial: ")
				<<
				pair.first
				<<
				FCPPT_TEXT('\n');

		fcppt::io::cout()
			<<
			FCPPT_TEXT("\tFaces: ")
			<<
			pair.second.size()
			<<
			FCPPT_TEXT('\n');
	}
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<<
		FCPPT_TEXT("Caught exception: ")
		<<
		_exception.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cout
		<<
		"Caught exception: "
		<<
		_exception.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
