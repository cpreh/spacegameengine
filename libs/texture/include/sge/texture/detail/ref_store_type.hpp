//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TEXTURE_DETAIL_REF_STORE_TYPE_HPP_INCLUDED
#define SGE_TEXTURE_DETAIL_REF_STORE_TYPE_HPP_INCLUDED

#include <fcppt/unique_ptr_impl.hpp>

namespace sge::texture::detail
{

template <typename T>
struct ref_store_type;

template <typename T>
struct ref_store_type<T &>
{
  using type = T &;
};

template <typename T>
struct ref_store_type<fcppt::unique_ptr<T> &&>
{
  using type = fcppt::unique_ptr<T> const;
};

}

#endif
