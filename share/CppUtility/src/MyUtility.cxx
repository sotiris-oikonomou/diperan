////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the Diperan project.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file						Diperan/MyUtility.cxx
///	@author						Sotiris Oikonomou <sotoik@gmail.com>
///	@date						15 May 2019

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Diperan/MyClass.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int								main										(			int							argc,
																						char**						argv								)
{

	using diperan::MyClass ;

	(void) argc ;
	(void) argv ;

	MyClass myClass = MyClass::Integer(123) ;

	myClass.doSomething() ;
	myClass.printSomething() ;

	return 0 ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////