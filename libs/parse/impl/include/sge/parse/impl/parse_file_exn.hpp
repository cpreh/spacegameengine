//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge::parse::impl
{

template<
	typename Result,
	typename Ch,
	typename Skipper
>
Result
parse_file_exn(
	std::filesystem::path const &_path,
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

#endif
