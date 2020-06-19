//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_FACE_VERTEX_SEQUENCE_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_VERTEX_SEQUENCE_HPP_INCLUDED

#include <sge/model/obj/face_vertex.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{

using
face_vertex_sequence
=
std::vector<
	sge::model::obj::face_vertex
>;

}
}
}

#endif
