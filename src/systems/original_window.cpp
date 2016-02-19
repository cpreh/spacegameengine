/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/systems/original_window.hpp>
#include <sge/window/default_class_name.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/size_hints.hpp>
#include <sge/window/title.hpp>
#include <fcppt/string.hpp>


sge::systems::original_window::original_window(
	sge::window::title const &_title
)
:
	title_{
		_title
	},
	class_name_{
		sge::window::default_class_name()
	},
	dim_{},
	size_hints_{},
	hide_cursor_{
		false
	}
{
}

sge::systems::original_window &
sge::systems::original_window::dim(
	sge::window::dim const _dim
)
{
	dim_ =
		sge::window::optional_dim{
			_dim
		};

	return
		*this;
}

sge::systems::original_window &
sge::systems::original_window::class_name(
	fcppt::string const &_class_name
)
{
	class_name_ =
		_class_name;

	return
		*this;
}

sge::systems::original_window &
sge::systems::original_window::size_hints(
	sge::window::size_hints const &_size_hints
)
{
	size_hints_ =
		_size_hints;

	return
		*this;
}

sge::systems::original_window &
sge::systems::original_window::hide_cursor()
{
	hide_cursor_ =
		true;

	return
		*this;
}

sge::window::title const &
sge::systems::original_window::title() const
{
	return
		title_;
}

sge::window::optional_dim const &
sge::systems::original_window::dim() const
{
	return
		dim_;
}

fcppt::string const &
sge::systems::original_window::class_name() const
{
	return
		class_name_;
}

sge::window::size_hints const &
sge::systems::original_window::size_hints() const
{
	return
		size_hints_;
}

bool
sge::systems::original_window::hide_cursor() const
{
	return
		hide_cursor_;
}
