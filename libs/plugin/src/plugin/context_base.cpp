//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/cache.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <sge/plugin/impl/load_info.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/weak_ptr_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::plugin::context_base::context_base(
	sge::plugin::optional_cache_ref const &_cache,
	std::filesystem::path const &_path
)
:
	cache_(
		_cache
	),
	path_(
		_path
	),
	info_(
		sge::plugin::impl::load_info(
			_path
		)
	),
	library_ptr_()
{
}

sge::plugin::context_base::~context_base()
{
}

std::filesystem::path const &
sge::plugin::context_base::path() const
{
	return
		path_;
}

sge::plugin::info const &
sge::plugin::context_base::info() const
{
	return
		info_;
}

sge::plugin::library::object_shared_ptr
sge::plugin::context_base::load()
{
	return
		fcppt::optional::from(
			library_ptr_.lock(),
			[
				this
			]{
				sge::plugin::library::object_shared_ptr const ret(
					fcppt::make_shared_ptr<
						sge::plugin::library::object
					>(
						path_
					)
				);

				library_ptr_ =
					library_weak_ptr{
						ret
					};

				if(
					this->info().flags()
					&
					sge::plugin::flags::delayed_unload
				)
					fcppt::optional::maybe_void(
						cache_,
						[
							ret
						](
							fcppt::reference<
								sge::plugin::cache
							> const _cache
						)
						{
							_cache.get().add(
								ret
							);
						}
					);

				return
					ret;
			}
		);
}
