//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_DECLARE_MUXER_PARAMETERS_HPP_INCLUDED
#define SGE_MEDIA_DECLARE_MUXER_PARAMETERS_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/media/muxer_parameters.hpp>


#define SGE_MEDIA_DECLARE_MUXER_PARAMETERS(\
	system\
)\
extern \
template \
class \
SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
sge::media::muxer_parameters<\
	system\
>

#endif
