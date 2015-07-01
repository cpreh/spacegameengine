#ifndef SGE_GUI_TEXT_CALLBACK_HPP_INCLUDED
#define SGE_GUI_TEXT_CALLBACK_HPP_INCLUDED

#include <sge/gui/text_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gui
{

typedef
std::function<
	sge::gui::text_function
>
text_callback;

}
}

#endif
