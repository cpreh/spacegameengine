//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_MEDIA_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/file_exception_fwd.hpp> // IWYU pragma: keep
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/detail/instantiate/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge::media
{

template <typename Base>
class SGE_CORE_DETAIL_CLASS_SYMBOL file_exception : public Base
{
public:
  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  file_exception(sge::media::optional_name const &, fcppt::string const &);

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  file_exception(file_exception &&) noexcept;

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  file_exception(file_exception const &);

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  file_exception &operator=(file_exception &&) noexcept;

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  file_exception &operator=(file_exception const &);

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  ~file_exception() noexcept override;
};

}

#endif
