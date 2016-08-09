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
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
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
	boost::filesystem::path const &_path,
	sge::model::md3::load_flags_field const _flags
)
{
	boost::filesystem::ifstream file(
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
