//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/tabbed_to_stream.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/format.hpp>
#include <iterator>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

// TODO(philipp): Simplify this
struct output_visitor
{
public:
	using
	tab_count
	=
	sge::charconv::utf8_string::size_type;

	output_visitor(
		std::ostream &_stream,
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

	void
	operator()(
		sge::parse::json::object const &_object
	) const
	{
		this->stream_.get()
			<<
			(
				boost::format(
					"%s{\n"
				)
				% this->make_tabs()
			).str();

		for(
			auto it(
				_object.members.begin()
			);
			it != _object.members.end();
			++it
		)
		{
			this->stream_.get()
				<<
				(
					boost::format(
						"%s\"%s\" :\n"
					)
					% this->make_more_tabs()
					% it->first
				).str();

			fcppt::variant::apply(
				output_visitor(
					this->stream_.get(),
					tabs_+2
				),
				it->second.get().get()
			);

			if(
				std::next(it)
				!=
				_object.members.end()
			)
			{
				this->stream_.get()
					<< ',';
			}

			this->stream_.get()
				<< '\n';
		}

		this->stream_.get()
			<< this->make_tabs()
			<< '}';
	}

	void
	operator()(
		sge::parse::json::array const &_array
	) const
	{
		this->stream_.get()
			<<
			(
				boost::format(
					"%s[\n"
				)
				%
				this->make_tabs()
			).str();

		for(
			auto it(
				_array.elements.begin()
			);
			it != _array.elements.end();
			++it
		)
		{
			fcppt::variant::apply(
				output_visitor(
					this->stream_.get(),
					tabs_+1
				),
				it->get().get()
			);

			if(
				std::next(it)
				!=
				_array.elements.end()
			)
			{
				this->stream_.get()
					<< ',';
			}

			this->stream_.get()
				<< '\n';
		}

		this->stream_.get()
			<< this->make_tabs()
			<< ']';
	}

	void
	operator()(
		std::string const &_string
	) const
	{
		if(
			fcppt::algorithm::contains(
				_string,
				'\"'
			)
		)
		{
			throw
				sge::parse::exception(
					FCPPT_TEXT("quoted strings are unsupported")
				);
		}

		this->stream_.get()
			<< this->make_tabs()
			<< '"'
			<< _string
			<< '"';
	}

	void
	operator()(
		bool const _bool
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			(
				_bool
				?
					sge::charconv::utf8_string{
						"true"
					}
				:
					sge::charconv::utf8_string{
						"false"
					}
			);
	}

	void
	operator()(
		sge::parse::json::null const &
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<< "null";
	}

	void
	operator()(
		sge::parse::json::int_type const _int
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			fcppt::output_to_std_string(
				_int
			);
	}

	void
	operator()(
		sge::parse::json::float_type const _float
	) const
	{
		this->stream_.get()
			<< this->make_tabs()
			<<
			(
				boost::format(
					"%1$.2f"
				)
				%
				_float
			).str();
	}
private:
	fcppt::reference<
		std::ostream
	> stream_;

	tab_count tabs_;

	[[nodiscard]]
	sge::charconv::utf8_string
	make_tabs() const
	{
		return
			sge::charconv::utf8_string(
				tabs_,
				'\t'
			);
	}

	[[nodiscard]]
	sge::charconv::utf8_string
	make_more_tabs() const
	{
		return
			sge::charconv::utf8_string(
				tabs_ + 1U,
				'\t'
			);
	}
};

}

void
sge::parse::json::output::tabbed_to_stream(
	std::ostream &_stream,
	sge::parse::json::start const &_start
)
{
	return
		fcppt::variant::apply(
			[
				&_stream
			](
				auto const &_value
			)
			{
				output_visitor{
					_stream,
					0U
				}(
					_value
				);
			},
			_start.variant
		);
}
