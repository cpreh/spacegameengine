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


#include <sge/log/parameters.hpp>

sge::log::parameters::parameters()
:
	sink_(0),
	parent_(0),
	context_(0),
	prefix_(),
	enabled_(false),
	level_(
		level::warning
	),
	formatter_()
{}

sge::log::parameters 
sge::log::parameters::sink(
	ostream &nsink_
)
{
	sink_ = &nsink_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::parent(
	object const &nparent_
)
{
	parent_ = &nparent_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::context(
	log::context &ncontext_
)
{
	context_ = &ncontext_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::prefix(
	string const &nprefix_
)
{
	prefix_ = nprefix_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::enabled(
	bool nenabled_
)
{
	enabled_ = nenabled_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::level(
	log::level::type const nlevel_
)
{
	level_ = nlevel_;

	return *this;
}

sge::log::parameters 
sge::log::parameters::formatter(
	format::const_object_ptr const nformatter_
)
{
	formatter_ = nformatter_;

	return *this;
}

sge::ostream *
sge::log::parameters::sink() const
{
	return sink_;
}

sge::log::object const *
sge::log::parameters::parent() const
{
	return parent_;
}

sge::log::context *
sge::log::parameters::context() const
{
	return context_;
}

sge::string const
sge::log::parameters::prefix() const
{
	return prefix_;
}

bool
sge::log::parameters::enabled() const
{
	return enabled_;
}

sge::log::level::type
sge::log::parameters::level() const
{
	return level_;
}

sge::log::format::const_object_ptr const
sge::log::parameters::formatter() const
{
	return formatter_;
}
