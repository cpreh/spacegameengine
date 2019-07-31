//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/view/data_impl.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>


#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA_BASE(\
	tag,\
	view_type,\
	pointer\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
pointer \
sge::image::view::data<\
	tag\
>(\
	sge::image::view::view_type<\
		tag\
	> const &\
)

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA(\
	tag\
)\
SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA_BASE(\
	tag,\
	object,\
	sge::image::raw_pointer\
);\
SGE_IMAGE_IMPL_VIEW_INSTANTIATE_DATA_BASE(\
	tag,\
	const_object,\
	sge::image::const_raw_pointer\
)

#endif
