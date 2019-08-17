//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/model/md3/load_flags_field.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/object_unique_ptr.hpp>
#include <sge/model/md3/impl/loader.hpp>
#include <sge/model/md3/impl/log_name.hpp>
#include <sge/model/md3/impl/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::loader::loader(
	fcppt::log::context &_log_context
)
:
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			sge::model::md3::impl::log_name()
		)
	}
{
}

sge::model::md3::impl::loader::~loader()
{
}

sge::model::md3::object_unique_ptr
sge::model::md3::impl::loader::load(
	std::filesystem::path const &_path,
	sge::model::md3::load_flags_field const _flags
)
{
	std::ifstream file(
		_path,
		std::ios_base::binary
	);

	file.exceptions(
		std::ios_base::failbit
		| std::ios_base::badbit
	);

	return
		fcppt::unique_ptr_to_base<
			sge::model::md3::object
		>(
			fcppt::make_unique_ptr<
				sge::model::md3::impl::object
			>(
				log_,
				file,
				_flags
			)
		);
}

sge::model::md3::object_unique_ptr
sge::model::md3::impl::loader::load_stream(
	std::istream &_stream,
	sge::model::md3::load_flags_field const _flags
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::model::md3::object
		>(
			fcppt::make_unique_ptr<
				sge::model::md3::impl::object
			>(
				log_,
				_stream,
				_flags
			)
		);
}
