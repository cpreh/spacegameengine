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


#include <sge/console/arg_list.hpp>
#include <sge/console/error_callback.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/function.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/object.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/signal.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <sge/src/console/eval_grammar.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::object::object(
	sge::console::prefix const _prefix
)
:
	error_(),
	message_(),
	prefix_(
		_prefix.get()
	),
	funcs_(),
	fallback_(),
	help_connection_(
		this->insert(
			sge::console::callback::parameters(
				std::bind(
					&sge::console::object::help_callback,
					this,
					std::placeholders::_1
				),
				sge::console::callback::name(
					SGE_FONT_LIT("help")
				)
			)
			.short_description(
				SGE_FONT_LIT("Display help message")
			)
		)
	),
	man_connection_(
		this->insert(
			sge::console::callback::parameters(
				std::bind(
					&sge::console::object::man_callback,
					this,
					std::placeholders::_1
				),
				sge::console::callback::name(
					SGE_FONT_LIT("man")
				)
			)
			.short_description(
				SGE_FONT_LIT("Display information for a specific function")
			)
		)
	)
{
}
FCPPT_PP_POP_WARNING

sge::console::object::~object()
{
}

fcppt::signal::auto_connection
sge::console::object::insert(
	sge::console::callback::parameters const &_params
)
{
	sge::console::function_map::iterator it(
		funcs_.find(
			_params.name()
		)
	);

	if(
		it
		==
		funcs_.end()
	)
	{
		typedef std::pair<
			sge::console::function_map::iterator,
			bool
		> ret_type;

		ret_type const ret(
			funcs_.insert(
				std::make_pair(
					_params.name(),
					sge::console::function(
						_params.short_description(),
						_params.long_description()
					)
				)
			)
		);

		it = ret.first;

		FCPPT_ASSERT_ERROR(
			ret.second
		);
	}
	return
		it->second.signal().connect(
			_params.function(),
			std::bind(
				&sge::console::object::remove_function,
				this,
				_params.name()
			)
		);
}

fcppt::signal::auto_connection
sge::console::object::register_fallback(
	sge::console::fallback const &_callback
)
{
	return
		fallback_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::console::object::register_error_callback(
	sge::console::error_callback const &_callback
)
{
	return
		error_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::console::object::register_message_callback(
	sge::console::message_callback const &_callback
)
{
	return
		message_.connect(
			_callback
		);
}

void
sge::console::object::eval(
	sge::font::string const &sp
)
{
	if (sp.empty())
		return;

	if (sp[0] != prefix_)
	{
		fallback_(sp);
		return;
	}

	sge::font::string const s = sp.substr(1);

	sge::console::arg_list args;

	sge::console::eval_grammar<
		sge::font::string::const_iterator
	> grammar;

	sge::font::string::const_iterator beg = s.begin();

	boost::spirit::qi::parse(
		beg,
		s.end(),
		grammar,
		args
	);

	this->eval(
		args
	);
}

void
sge::console::object::eval(
	sge::console::arg_list const &args
)
{
	// just typing the prefix is not an error
	if(
		args.empty()
	)
		return;

	function_map::iterator const it(
		funcs_.find(
			args[0]
		)
	);

	if(
		it == funcs_.end()
	)
		throw sge::console::exception(
			SGE_FONT_LIT("couldn't find command \"")
			+
			args[0]
			+
			SGE_FONT_LIT('"')
		);

	it->second.signal()(
		args,
		*this
	);
}

sge::console::function_map const &
sge::console::object::functions() const
{
	return funcs_;
}

sge::font::char_type
sge::console::object::prefix() const
{
	return prefix_;
}

void
sge::console::object::emit_error(
	sge::font::string const &_string
)
{
	error_(
		_string
	);
}

void
sge::console::object::emit_message(
	sge::font::string const &_string
)
{
	message_(
		_string
	);
}

void
sge::console::object::help_callback(
	sge::console::arg_list const &
)
{
	this->emit_message(
		fcppt::insert_to_string<
			sge::font::string
		>(
			funcs_.size()
		)
		+
		SGE_FONT_LIT(" available functions:")
	);

	for(
		auto const &element
		:
		funcs_
	)
		this->emit_message(
			element.first
			+
			SGE_FONT_LIT(": ")
			+
			element.second.short_description().get()
		);
}

void
sge::console::object::man_callback(
	sge::console::arg_list const &v)
{
	if (v.size() < 2)
	{
		this->emit_error(
			SGE_FONT_LIT("no function given"));
		return;
	}

	function_map const &fns =
		funcs_;

	function_map::const_iterator i =
		funcs_.find(
			v[1]);

	if (i == fns.end())
	{
		this->emit_error(
			SGE_FONT_LIT("function \"")
			+ v[1]
			+ SGE_FONT_LIT("\" not found")
		);

		return;
	}

	if(
		i->second.long_description().get().empty()
	)
		this->emit_message(
			SGE_FONT_LIT("No manpage available")
		);
	else
		this->emit_message(
			i->second.long_description().get()
		);
}

void
sge::console::object::remove_function(
	sge::font::string const &_name
)
{
	function_map::iterator const it(
		funcs_.find(
			_name
		)
	);

	FCPPT_ASSERT_PRE(
		it != funcs_.end()
	);

	if(
		it->second.signal().empty()
	)
		funcs_.erase(
			it
		);
}
