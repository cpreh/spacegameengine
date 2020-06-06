//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/get_or_create_entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/make_if.hpp>


fcppt::reference<
	sge::parse::ini::entry
>
sge::parse::ini::get_or_create_entry(
	fcppt::reference<
		sge::parse::ini::section
	> const _section,
	sge::parse::ini::entry_name const &_entry_name,
	sge::parse::ini::value const &_value
)
{
	sge::parse::ini::entry_vector &entries(
		_section.get().entries
	);

	return
		fcppt::optional::from(
			fcppt::algorithm::find_by_opt(
				entries,
				[
					&_entry_name
				](
					sge::parse::ini::entry &_entry
				)
				{
					return
						fcppt::optional::make_if(
							sge::parse::ini::entry_name_equal{
								fcppt::make_cref(
									_entry_name
								)
							}(
								_entry
							),
							[
								&_entry
							]{
								return
									fcppt::make_ref(
										_entry
									);
							}
						);
				}
			),
			[
				&entries,
				&_entry_name,
				&_value
			]{
				entries.push_back(
					sge::parse::ini::entry(
						sge::parse::ini::entry_name{
							_entry_name
						},
						sge::parse::ini::value{
							_value
						}
					)
				);

				return
					fcppt::make_ref(
						entries.back()
					);
			}
		);
}
