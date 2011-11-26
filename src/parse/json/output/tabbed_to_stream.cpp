/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/tabbed_to_stream.hpp>
#include <fcppt/format.hpp>
#include <fcppt/insert_to_string.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

struct output_visitor
{
	FCPPT_NONASSIGNABLE(
		output_visitor
	);
public:
	typedef
	void
	result_type;

	typedef
	fcppt::string::size_type
	tab_count;

	output_visitor(
		fcppt::io::ostream &_stream,
		tab_count const _tabs
	)
	:
		stream_(
			_stream
		),
		tabs_(
			_tabs
		)
	{
	}

	result_type
	operator()(
		sge::parse::json::object const &_object
	) const
	{
		stream_
			<<
			(
				fcppt::format(
					FCPPT_TEXT("%s{\n")
				)
				% this->make_tabs()
			).str();

		for(
			sge::parse::json::member_map::const_iterator it(
				_object.members.begin()
			);
			it != _object.members.end();
			++it
		)
		{
			stream_ <<
				(
					fcppt::format(
						FCPPT_TEXT("%s\"%s\" : \n")
					)
					% this->make_more_tabs()
					% it->first
				).str();

			fcppt::variant::apply_unary(
				output_visitor(
					stream_,
					tabs_+2
				),
				it->second
			);

			if(
				boost::next(it)
				!=
				_object.members.end()
			)
				stream_ << FCPPT_TEXT(',');

			stream_ << FCPPT_TEXT('\n');
		}

		stream_
			<< this->make_tabs()
			<< FCPPT_TEXT('}');
	}

	result_type
	operator()(
		sge::parse::json::array const &_array
	) const
	{
		stream_
			<<
			(
				fcppt::format(
					FCPPT_TEXT("%s[\n")
				)
				%
				this->make_tabs()
			).str();

		for(
			sge::parse::json::element_vector::const_iterator it(
				_array.elements.begin()
			);
			it != _array.elements.end();
			++it
		)
		{
			fcppt::variant::apply_unary(
				output_visitor(
					stream_,
					tabs_+1
				),
				*it
			);

			if(
				boost::next(it)
				!=
				_array.elements.end()
			)
				stream_ << FCPPT_TEXT(',');

			stream_ << FCPPT_TEXT('\n');
		}

		stream_
			<< this->make_tabs()
			<< FCPPT_TEXT(']');
	}

	result_type
	operator()(
		sge::parse::json::string const &_string
	) const
	{
		if(
			_string.find(
				FCPPT_TEXT('\"')
			)
			!= sge::parse::json::string::npos
		)
			throw sge::parse::json::exception(
				FCPPT_TEXT("quoted strings are unsupported")
			);

		stream_
			<< this->make_tabs()
			<< FCPPT_TEXT('"')
			<< _string
			<< FCPPT_TEXT('"');
	}

	result_type
	operator()(
		bool const _bool
	) const
	{
		stream_
			<< this->make_tabs()
			<<
			(
				_bool
				?
					fcppt::string(
						FCPPT_TEXT("true")
					)
				:
				fcppt::string(
					FCPPT_TEXT("false")
				)
			);
	}

	result_type
	operator()(
		sge::parse::json::null const &
	) const
	{
		stream_
			<< this->make_tabs()
			<< FCPPT_TEXT("null");
	}

	result_type
	operator()(
		sge::parse::json::int_type const _int
	) const
	{
		stream_
			<< this->make_tabs()
			<< fcppt::insert_to_string<
				fcppt::string
			>(
				_int
			);
	}

	result_type
	operator()(
		sge::parse::json::float_type const _float
	) const
	{
		stream_
			<< this->make_tabs()
			<<
			(
				fcppt::format(
					FCPPT_TEXT("%1$.2f")
				)
				%
				_float
			).str();
	}
private:
	fcppt::io::ostream &stream_;

	tab_count const tabs_;

	fcppt::string const
	make_tabs() const
	{
		return
			fcppt::string(
				tabs_,
				FCPPT_TEXT('\t')
			);
	}

	fcppt::string const
	make_more_tabs() const
	{
		return
			fcppt::string(
				tabs_ + 1u,
				FCPPT_TEXT('\t')
			);
	}

	fcppt::string
	make_even_more_tabs() const
	{
		return
			fcppt::string(
				tabs_ + 2u,
				FCPPT_TEXT('\t')
			);
	}
};

}

void
sge::parse::json::output::tabbed_to_stream(
	fcppt::io::ostream &_stream,
	sge::parse::json::object const &_object
)
{
	sge::parse::json::value value(
		_object
	);

	return
		fcppt::variant::apply_unary(
			output_visitor(
				_stream,
				0u
			),
			value
		);
}
