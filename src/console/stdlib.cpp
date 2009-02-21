#include <sge/console/stdlib.hpp>
#include <sge/console/object.hpp>
#include <sge/console/exception.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

sge::console::stdlib::stdlib(
	object &_object,
	print_callback const &_print,
	error_callback const &_error)
	: object_(_object),
	  print_(_print),
	  error_(_error),
		get(
			object_.insert(
				SGE_TEXT("get"),
				boost::bind(&stdlib::fn_get,this,_1),
				SGE_TEXT("get <name> - display value of <name>"))),
		set(
			object_.insert(
				SGE_TEXT("set"),
				boost::bind(&stdlib::fn_set,this,_1),
				SGE_TEXT("set <name> <value> - set <name> to <value>"))),
		help(
			object_.insert(
				SGE_TEXT("help"),
				boost::bind(&stdlib::fn_help,this,_1),
				SGE_TEXT("list available functions"))),
		lsfuncs(
			object_.insert(
				SGE_TEXT("lsfuncs"),
				boost::bind(&stdlib::fn_help,this,_1),
				SGE_TEXT("list available functions"))),
		lsvars(
			object_.insert(
				SGE_TEXT("lsvars"),
				boost::bind(&stdlib::fn_lsvars,this,_1),
				SGE_TEXT("list available variables with values"))),
		man(
			object_.insert(
				SGE_TEXT("man"),
				boost::bind(&stdlib::fn_man,this,_1),
				SGE_TEXT("usage: man <function> - display help to <function>")))
{
}

void sge::console::stdlib::fn_get(arg_list const &v)
{
	if (v.size() == 1 || v[1].empty())
	{
		error_(SGE_TEXT("no variable given"));
		return;
	}
	string const arg = v[1];
	variable_map const &vars = object_.variables();
	variable_map::const_iterator i = vars.find(arg);
	if (i == vars.end())
	{
		error_(SGE_TEXT("variable ")+arg+SGE_TEXT(" not found"));
		return;
	}
	print_(arg+SGE_TEXT('=')+(i->second->string()));
}

void sge::console::stdlib::fn_set(arg_list const &v)
{
	if (v.size() < 3 || v[1].empty())
	{
		error_(SGE_TEXT("not enough arguments or empty variable name"));
		return;
	}
	string const arg = v[1];
	string const value = v[2];
	variable_map &vars = object_.variables();
	variable_map::iterator i = vars.find(arg);
	if (i == vars.end())
	{
		error_(SGE_TEXT("variable ")+arg+SGE_TEXT(" not found"));
		return;
	}
	try
	{
		i->second->string(value);
	}
	catch (exception const &e)
	{
		error_(SGE_TEXT("error: ")+e.what());
		return;
	}
	print_(arg+SGE_TEXT('=')+(i->second->string()));
}

void sge::console::stdlib::fn_help(arg_list const &)
{
	function_map const &fns = object_.functions();

	print_(boost::lexical_cast<string>(fns.size())+SGE_TEXT(" available functions:"));

	BOOST_FOREACH(function_map::const_reference p,fns)
		print_function(p);
}

void sge::console::stdlib::fn_lsvars(arg_list const &)
{
	variable_map const &vars = object_.variables();

	print_(boost::lexical_cast<string>(vars.size())+SGE_TEXT(" available variables:"));

	BOOST_FOREACH(variable_map::const_reference p,vars)
		print_(p.first+SGE_TEXT('=')+p.second->string());
}

void sge::console::stdlib::fn_man(arg_list const &v)
{
	if (v.size() < 2 || v[1].empty())
	{
		error_(SGE_TEXT("no function given"));
		return;
	}
	
	function_map const &fns = object_.functions();

	function_map::const_iterator i = fns.find(v[1]);

	if (i == fns.end())
	{
		error_(SGE_TEXT("function \"")+v[1]+SGE_TEXT("\" not found"));
		return;
	}

	print_function(*i);
}

void sge::console::stdlib::print_function(function_map::const_reference p)
{
	if (p.second->description().empty())
		print_(p.first);
	else
		print_(p.first+SGE_TEXT(": ")+p.second->description());
}
