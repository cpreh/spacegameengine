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


#ifndef SGE_PARSE_IMPL_PARSE_FILE_EXN_HPP_INCLUDED
#define SGE_PARSE_IMPL_PARSE_FILE_EXN_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/impl/file_error_string.hpp>
#include <sge/parse/impl/parse_file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/grammar_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace impl
{

template<
	typename Result,
	typename Ch,
	typename Skipper
>
Result
parse_file_exn(
	boost::filesystem::path const &_path,
	fcppt::parse::grammar<
		Result,
		Ch,
		Skipper
	> const &_grammar
)
{
	return
		fcppt::either::to_exception(
			sge::parse::impl::parse_file(
				_path,
				_grammar
			),
			[
				&_path
			](
				fcppt::optional::object<
					fcppt::parse::error<
						Ch
					>
				> &&_error
			)
			{
				return
					sge::parse::exception{
						fcppt::optional::maybe(
							std::move(
								_error
							),
							[
								&_path
							]{
								return
									FCPPT_TEXT("Failed to open ")
									+
									fcppt::filesystem::path_to_string(
										_path
									);
							},
							[
								&_path
							](
								fcppt::parse::error<
									Ch
								> &&_parse_error
							)
							{
								return
									sge::parse::impl::file_error_string(
										_path,
										std::move(
											_parse_error
										)
									);
							}
						)
					};
			}
		);
}

}
}
}

#endif
