//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_PARSE_MTLLIB_HPP_INCLUDED
#define SGE_MODEL_OBJ_PARSE_MTLLIB_HPP_INCLUDED

#include <sge/model/obj/material_map.hpp>
#include <sge/model/obj/detail/symbol.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{

SGE_MODEL_OBJ_DETAIL_SYMBOL
sge::model::obj::material_map
parse_mtllib(
	fcppt::log::context &,
	boost::filesystem::path const &
);

}
}
}

#endif
