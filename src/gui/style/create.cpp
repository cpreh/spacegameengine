#include <sge/gui/impl/style/simple.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>
#include <sge/gui/style/create.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::gui::style::base_unique_ptr
sge::gui::style::create()
{
	return
		fcppt::unique_ptr_to_base<
			sge::gui::style::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sge::gui::impl::style::simple
			>()
		);
}
