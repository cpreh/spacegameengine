#include <sge/config/media_path.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
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
	sge::model::obj::prototype const loaded_model(
		"/tmp/untitled.obj");
		//		sge::config::media_path() / FCPPT_TEXT("objs") / FCPPT_TEXT("dragon.obj"));

	std::cout << "Loaded successfully!\n";

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
				"/tmp/"/(*it));
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
