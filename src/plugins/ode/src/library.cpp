#include "../library.hpp"
#include <ode/ode.h>

sge::ode::library::library()
{
	dInitODE();
}

sge::ode::library::~library()
{
	dCloseODE();
}
