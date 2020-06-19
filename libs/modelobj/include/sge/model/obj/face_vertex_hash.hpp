//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_FACE_VERTEX_HASH_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_VERTEX_HASH_HPP_INCLUDED

#include <sge/model/obj/face_vertex_fwd.hpp>
#include <sge/model/obj/detail/symbol.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace std
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmismatched-tags)

template<>
struct hash<
	sge::model::obj::face_vertex
>
{
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	std::size_t
	operator()(
		sge::model::obj::face_vertex const &
	) const
	noexcept;
};

FCPPT_PP_POP_WARNING

}

#endif
