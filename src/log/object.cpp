/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/object.hpp>
#include <sge/log/parameters.hpp>
#include <sge/log/context.hpp>
#include <sge/log/level_stream.hpp>
#include <sge/log/format/default_level.hpp>
#include <sge/optional_impl.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/foreach_enumerator.hpp>
#include <sge/assert.hpp>
#include <tr1/functional>

sge::log::object::object(
	parameters const &param_
)
:
	parent_(
		param_.parent()
	),
	sink_(
		param_.sink()
		?
			param_.sink()
		:
			param_.parent()
			?
				param_.parent()->sink()
			:
				0
	),
	auto_context_(
		param_.context(),
		*this,
		param_.context()
		?
			param_.parent()
			&& param_.parent()->location()
			?
				*param_.parent()->location()
				+ param_.prefix()
			:
				log::location(
					param_.prefix()
				)
		:
			optional_location()	
	),
	formatter_(
		param_.formatter()
	),
	enabled_(
		param_.enabled()
	),
	level_streams_(),
	enabled_levels_()
{
	SGE_ASSERT(
		sink_
	);

	SGE_FOREACH_ENUMERATOR(
		i,
		level
	)
	{
		auto_ptr<
			level_stream
		> s(
			make_auto_ptr<
				level_stream
			>(
				std::tr1::ref(
					*sink()
				),
				format::default_level(
					i	
				)
			)
		);

		level_streams_.replace(
			i,
			s
		);

		enabled_levels_[
			i
		] = (param_.level() <= i);
	}
}

sge::log::object::~object()
{}

void
sge::log::object::log(
	level::type const level_,
	temporary_output const &helper
)
{
	if(
		!enabled()
		|| !activated(level_)
	)
		return;
	
	level_sink(level_).log(
		helper,
		formatter()
	);
}

sge::log::level_stream &
sge::log::object::level_sink(
	level::type const level_
)
{
	return level_streams_.at(
		level_
	);
}

sge::log::level_stream const &
sge::log::object::level_sink(
	level::type const level_
) const
{
	return level_streams_.at(
		level_
	);
}

void
sge::log::object::activate(
	level::type const level_
)
{
	enabled_levels_[
		level_
	] = true;
}

void
sge::log::object::deactivate(
	level::type const level_
)
{
	enabled_levels_[
		level_
	] = false;
}

bool
sge::log::object::activated(
	level::type const level_
) const
{
	return
		enabled_levels_[
			level_
		];
}

void
sge::log::object::enable(
	bool const b
)
{
	enabled_ = b;
}

bool
sge::log::object::enabled() const
{
	return enabled_;
}

sge::ostream *
sge::log::object::sink() const
{
	return sink_;
}

sge::log::format::const_object_ptr const
sge::log::object::formatter() const
{
	return formatter_;
}

sge::log::optional_location const
sge::log::object::location() const
{
	return auto_context_.location();
}
