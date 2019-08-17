//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_MATERIAL_DIFFUSE_TEXTURE_PATH_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_DIFFUSE_TEXTURE_PATH_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
namespace material
{

FCPPT_MAKE_STRONG_TYPEDEF(
	std::filesystem::path,
	diffuse_texture_path
);

}
}
}
}

#endif
