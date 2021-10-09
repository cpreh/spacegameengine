//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/bad_sound_alloc.hpp>
#include <sge/audio/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::audio::bad_sound_alloc::bad_sound_alloc(fcppt::string &&_message)
    : sge::audio::exception(std::move(_message))
{
}

sge::audio::bad_sound_alloc::bad_sound_alloc(bad_sound_alloc &&) noexcept = default;

sge::audio::bad_sound_alloc::bad_sound_alloc(bad_sound_alloc const &) = default;

sge::audio::bad_sound_alloc &
sge::audio::bad_sound_alloc::operator=(bad_sound_alloc &&) noexcept = default;

sge::audio::bad_sound_alloc &
sge::audio::bad_sound_alloc::operator=(bad_sound_alloc const &) = default;

sge::audio::bad_sound_alloc::~bad_sound_alloc() noexcept = default;
