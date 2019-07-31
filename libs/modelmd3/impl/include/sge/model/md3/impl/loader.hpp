//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_LOADER_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_LOADER_HPP_INCLUDED

#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/loader.hpp>
#include <sge/model/md3/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

class loader
:
	public sge::model::md3::loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
public:
	explicit
	loader(
		fcppt::log::context &
	);

	~loader()
	override;
private:
	sge::model::md3::object_unique_ptr
	load(
		boost::filesystem::path const &,
		sge::model::md3::load_flags_field
	)
	override;

	sge::model::md3::object_unique_ptr
	load_stream(
		std::istream &,
		sge::model::md3::load_flags_field
	)
	override;

	fcppt::log::object log_;
};

}
}
}
}

#endif
