//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_DETAIL_DECLARE_BASIC_PART_RAW_HPP_INCLUDED
#define SGE_TEXTURE_DETAIL_DECLARE_BASIC_PART_RAW_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/texture/basic_part_raw.hpp>


#define SGE_TEXTURE_DETAIL_DECLARE_BASIC_PART_RAW(\
	type\
)\
extern \
template \
class \
SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
sge::texture::basic_part_raw<\
	type\
>

#endif
