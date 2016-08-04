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
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/prototype.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iostream>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	// TODO: This example is not compiled
	sge::model::obj::prototype const loaded_model(
		sge::config::media_path() / FCPPT_TEXT("objs") / FCPPT_TEXT("Monkey.obj"));

	std::cout << "Loaded successfully!\n";

	std::cout << "Would produce: " << (loaded_model.face_count() * 3u) << " indices\n";
	std::cout << "Has: " << (loaded_model.face_vertices().size()) << " face vertices\n";
	std::cout << "Bounding box: " << loaded_model.bounding_box() << "\n";
	if(loaded_model.material_files().empty())
	{
		std::cout << "No material files\n";
	}
	else
	{
		std::cout << "Material files:\n";
		for(
			sge::model::obj::material_file_sequence::const_iterator it =
				loaded_model.material_files().begin();
			it != loaded_model.material_files().end();
			++it)
		{
			std::cout << *it << "\n";
			std::cout << "Loading...\n";
			sge::model::obj::parse_mtllib(
				sge::config::media_path() / FCPPT_TEXT("mtls") / (*it));
		}
	}

	std::cout
		<< "Vertices/texcoords/normals: "
		<< loaded_model.vertex_coordinates().size()
		<< "/"
		<< loaded_model.texture_coordinates().size()
		<< "/"
		<< loaded_model.normals().size()
		<< "\n";

	std::cout
		<< "First vertex/texcoord/normal: "
		<< loaded_model.vertex_coordinates().front()
		<< "/"
		<< loaded_model.texture_coordinates().front()
		<< "/"
		<< loaded_model.normals().front()
		<< "\n";

	std::cout << "Parts:\n";
	for(
		sge::model::obj::material_to_face_sequence::const_iterator it =
			loaded_model.parts().begin();
		it != loaded_model.parts().end();
		++it)
	{
		if(it->first.get().empty())
			std::cout << "\tDefault material\n";
		else
			std::cout << "\tMaterial: " << it->first << "\n";
		std::cout << "\tFaces: " << it->second.size() << "\n";
	}
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< FCPPT_TEXT("caugth exception: ")
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cout
		<< "caught exception: "
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
