//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_OBJ_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::model::obj::material
{

using file_sequence = std::vector<std::filesystem::path>;

}

#endif
