//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_MATRIX_FROM_QUATERNION_HPP_INCLUDED
#define SGE_CEGUI_IMPL_MATRIX_FROM_QUATERNION_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>


namespace CEGUI
{
class Quaternion;
}

namespace sge::cegui::impl
{

sge::renderer::matrix4
matrix_from_quaternion(
	CEGUI::Quaternion const &
);

}

#endif
