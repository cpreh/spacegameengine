//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/exception.hpp>
#include <sge/image2d/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::image2d::exception::exception(fcppt::string &&_what)
    : sge::image::exception(FCPPT_TEXT("2d: ") + std::move(_what))
{
}

sge::image2d::exception::exception(exception &&) noexcept = default;

sge::image2d::exception::exception(exception const &) = default;

sge::image2d::exception &sge::image2d::exception::operator=(exception &&) noexcept = default;

sge::image2d::exception &sge::image2d::exception::operator=(exception const &) = default;

sge::image2d::exception::~exception() noexcept = default;
