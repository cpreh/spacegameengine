//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_IMPL_FILE_EXCEPTION_IMPL_HPP_INCLUDED
#define SGE_MEDIA_IMPL_FILE_EXCEPTION_IMPL_HPP_INCLUDED

#include <sge/media/error_string.hpp>
#include <sge/media/file_exception.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/string.hpp>

template <typename Base>
sge::media::file_exception<Base>::file_exception(
    sge::media::optional_name const &_name, fcppt::string const &_text)
    : Base(sge::media::error_string(_name, _text))
{
}

template <typename Base>
sge::media::file_exception<Base>::file_exception(file_exception &&) noexcept = default;

template <typename Base>
sge::media::file_exception<Base>::file_exception(file_exception const &) = default;

template <typename Base>
sge::media::file_exception<Base> &
sge::media::file_exception<Base>::operator=(file_exception &&) noexcept = default;

template <typename Base>
sge::media::file_exception<Base> &
sge::media::file_exception<Base>::operator=(file_exception const &) = default;

namespace sge::media
{
template <typename Base>
file_exception<Base>::~file_exception() noexcept = default;
}

#endif
