////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the Diperan project.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file						Diperan/MyClass.hpp
///	@author						Sotiris Oikonomou <sotoik@gmail.com>
///	@date						15 May 2019

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Diperan_MyClass__
#define __Diperan_MyClass__

#include <ostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace diperan
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@brief						A MyClass class
///
///								This is a class.

class MyClass
{

	public:

		/// @brief				A MyEnum enum

		enum class MyEnum
		{

			First, ///< A first enum
			Second ///< A second enum
		
		} ;

		/// @brief				A MyType type

		typedef int MyType ;

		/// @brief				Default constructor

								MyClass										( ) ;

		/// @brief				A constructor
		///
		/// @param				[in] anEnum An enum
		/// @param				[in] anInteger An integer
		/// @param				[in] aString A string

								MyClass										(	const	MyClass::MyEnum&			anEnum,
																				const	int&						anInteger,
																				const	std::string&				aString								) ;

		/// @brief				Operators
		///
		/// @param				[in] aMyClass A MyClass instance
		/// @return				True if equal

		bool					operator ==									(	const	MyClass&					aMyClass							) const ;

		/// @brief				Stream operator
		///
		/// @param				[in] anOutputStream A stream
		/// @param				[in] aMyClass A MyClass instance
		/// @return				A stream reference

		friend std::ostream&	operator <<									(			std::ostream&				anOutputStream,
																				const	MyClass&					aMyClass							) ;

		/// @brief				Testers
		///
		/// @return				True if defined

		bool					isDefined									( ) const ;

		/// @brief				Getters
		///
		/// @return				Integer

		int						getInteger									( ) const ;

		/// @brief				Setters
		///
		/// @param				[in] anInteger An integer

		void					setInteger									(	const	int&						anInteger							) ;

		/// @brief				A public method

		void					doSomething									( ) ;

		/// @brief				Another public method

		void					printSomething								( ) ;

		/// @brief				A named constructor
		///
		/// @param				[in] anInteger An integer
		/// @return				A MyClass instance

		static MyClass			Integer										(	const	int&						anInteger							) ;

	private:

		MyClass::MyEnum			enum_ ; ///< An enum
		int						integer_ ; ///< An integer
		std::string				string_ ; ///< A string

		/// @brief				A private method

		void					doSomethingPrivate							( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////