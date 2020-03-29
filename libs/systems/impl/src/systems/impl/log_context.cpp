//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/default_level.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/systems/optional_log_context_ref.hpp>
#include <sge/systems/impl/log_context.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/match.hpp>


sge::systems::impl::log_context::log_context(
	sge::systems::optional_log_context_ref const _log_context
)
:
	impl_{
		fcppt::optional::maybe(
			_log_context,
			[]{
				return
					variant{
						fcppt::make_unique_ptr<
							fcppt::log::context
						>(
							sge::log::default_level(),
							sge::log::default_level_streams()
						)
					};
			},
			[](
				fcppt::reference<
					fcppt::log::context
				> const _ref
			)
			{
				return
					variant{
						_ref
					};
			}
		)
	}
{
}

sge::systems::impl::log_context::~log_context()
{
}

fcppt::log::context_reference
sge::systems::impl::log_context::get() const
{
	return
		fcppt::variant::match(
			impl_,
			[](
				fcppt::unique_ptr<
					fcppt::log::context
				> const &_context
			)
			->
			fcppt::log::context_reference
			{
				return
					fcppt::make_ref(
						*_context
					);
			},
			[](
				fcppt::reference<
					fcppt::log::context
				> const &_context
			)
			->
			fcppt::log::context_reference
			{
				return
					_context;
			}
		);
}
