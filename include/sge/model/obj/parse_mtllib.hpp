#ifndef SGE_MODEL_OBJ_PARSE_MTLLIB_HPP_INCLUDED
#define SGE_MODEL_OBJ_PARSE_MTLLIB_HPP_INCLUDED

#include <sge/model/obj/material_map.hpp>
#include <sge/model/obj/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
SGE_MODEL_OBJ_SYMBOL
sge::model::obj::material_map const
parse_mtllib(
	boost::filesystem::path const &);
}
}
}

#endif
