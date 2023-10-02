//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/processor_ref.hpp>
#include <sge/input/cursor/relative_movement/object.hpp>
#include <sge/input/impl/cursor/relative_movement/detail/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp> // NOLINT(misc-include-cleaner)

sge::input::cursor::relative_movement::object::object(sge::input::processor_ref const _processor)
    : impl_{
          fcppt::make_unique_ptr<sge::input::cursor::relative_movement::detail::object>(_processor)}
{
}

sge::input::cursor::relative_movement::object::~object() = default;
