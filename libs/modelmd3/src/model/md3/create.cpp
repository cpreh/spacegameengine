//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/md3/create.hpp>
#include <sge/model/md3/loader.hpp>
#include <sge/model/md3/loader_unique_ptr.hpp>
#include <sge/model/md3/impl/loader.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>


sge::model::md3::loader_unique_ptr
sge::model::md3::create(
	fcppt::log::context_reference const _log_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::model::md3::loader
		>(
			fcppt::make_unique_ptr<
				sge::model::md3::impl::loader
			>(
				_log_context
			)
		);
}
