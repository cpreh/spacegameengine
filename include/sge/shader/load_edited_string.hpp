#ifndef SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED
#define SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED

#include <sge/cg/program/source.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/shader/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
SGE_SHADER_SYMBOL
sge::cg::program::source const
load_edited_string(
	sge::renderer::device &,
	sge::renderer::vertex_declaration const &,
	boost::filesystem::path const &);
}
}

#endif

