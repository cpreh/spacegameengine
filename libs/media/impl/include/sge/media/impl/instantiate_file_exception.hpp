//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_IMPL_INSTANTIATE_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_MEDIA_IMPL_INSTANTIATE_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/media/impl/file_exception_impl.hpp>

#define SGE_MEDIA_IMPL_INSTANTIATE_FILE_EXCEPTION(base) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION sge::media::file_exception<base>

#endif
