/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_PLUGIN_LOAD_WITH_LOG_OPTIONS_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_LOAD_WITH_LOG_OPTIONS_IMPL_HPP_INCLUDED

#include <sge/log/apply_options.hpp>
#include <sge/log/option_container.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/load_with_log_options.hpp>
#include <sge/plugin/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::object<
	Type
>
sge::plugin::load_with_log_options(
	sge::plugin::context<
		Type
	> const &_context,
	sge::log::option_container const &_options
)
{
	typedef
	sge::plugin::object<
		Type
	>
	result_type;

	result_type result(
		_context.load()
	);

	// TODO: This could be optimized by only applying the locations the
	// plugin has
	sge::log::apply_options(
		_options
	);

	return
		std::move(
			result
		);
}

#endif
