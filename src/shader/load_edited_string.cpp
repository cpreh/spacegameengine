#include <sge/shader/load_edited_string.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <fcppt/config/external_end.hpp>


sge::cg::program::source const
sge::shader::load_edited_string(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	boost::filesystem::path const &_path)
{
	boost::filesystem::ifstream file(
		_path);

	return
		_renderer.transform_cg_vertex_program(
			_vd,
			sge::cg::program::source(
				fcppt::io::stream_to_string(
					file)));
}
