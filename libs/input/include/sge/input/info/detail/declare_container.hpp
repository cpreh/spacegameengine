//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_INFO_DETAIL_DECLARE_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_INFO_DETAIL_DECLARE_CONTAINER_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/input/info/container.hpp>


#define SGE_INPUT_INFO_DETAIL_DECLARE_CONTAINER(\
	id_param,\
	info_param\
)\
extern \
template \
class \
SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
sge::input::info::container<\
	id_param,\
	info_param\
>

#endif
