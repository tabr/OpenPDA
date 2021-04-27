//*****************************************************************************
//
// Author		: Trotzky Vasily
// Date			: Apr 05 2017
// All rights reserved.

// This is C++98 compatible binary literal implementation.
// Use as follows:
// static const uint8_t BinaryLiteralTest = BinaryLiteral8bit(10100101);
// You should enter exactly 8 digits. Only 1 and 0 are allowed;


// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.

// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or 
// other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************

#include <stdint.h>

#ifndef BINARYLITERAL_HPP_
#define BINARYLITERAL_HPP_

namespace BINARYLITERAL_HPP_private
{	
	//modified C++98 static assert implementation from Boost library
	#define BINARYLITERALCONCAT2(First, Second) (First ## Second)
	#define BINARYLITERALCONCAT(First, Second) BINARYLITERALCONCAT2(First, Second)	
	namespace boost
	{
		template <bool x> struct STATIC_ASSERTION_FAILURE;
		template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
		template<int x> struct static_assert_test{};
	}
	#define BINARYLITERAL_STATIC_ASSERT_BOOL_CAST(x) (bool)(x)
	#ifdef __GNUC__
	#define BINARYLITERAL_STATIC_ASSERT( B ) \
	   typedef boost::static_assert_test<\
		  sizeof(boost::STATIC_ASSERTION_FAILURE< BINARYLITERAL_STATIC_ASSERT_BOOL_CAST( B ) >)>\
			 (BINARYLITERALCONCAT(boost_static_assert_typedef_, __LINE__)) __attribute__((unused))
	#else
	#define BINARYLITERAL_STATIC_ASSERT( B ) \
	   typedef boost::static_assert_test<\
		  sizeof(boost::STATIC_ASSERTION_FAILURE< BINARYLITERAL_STATIC_ASSERT_BOOL_CAST( B ) >)>\
			 (BINARYLITERALCONCAT(boost_static_assert_typedef_, __LINE__))
	#endif
        //modified C++98 static assert implementation from Boost library END//

	template<uint8_t EXP> struct PowerOfTen { static const uint32_t value = 10 * PowerOfTen<EXP - 1>::value; };
	template<> struct PowerOfTen<0> { static const uint32_t value = 1; };
        
	template<bool ENABLED, uint32_t DIGIT> struct CheckDigit{}; 
	template<uint32_t DIGIT>
	struct CheckDigit<true, DIGIT>
	{	//If you get this assert:
		//You probably entered something else than 0 and 1 in your binary literal.
		//Only 1 and 0 are allowed. It should be like this: BinaryLiteral8bit(00000101);
		BINARYLITERAL_STATIC_ASSERT( ((DIGIT == 0) || (DIGIT == 1)) );
	};

	template<uint32_t NUMBER, unsigned N, bool CHECK_LITERAL_DIGITS=true>
	struct GetNDigit
	{
		static const uint32_t MOD = PowerOfTen<N+1>::value; static const uint32_t DIV = PowerOfTen<N>::value;
		enum { value = NUMBER % MOD / DIV };
		static const int JustToCheck = sizeof( CheckDigit<CHECK_LITERAL_DIGITS, value> );
	};
	template<uint32_t NUMBER, bool CHECK_DIGITS_ENABLED>
	struct GetNDigit<NUMBER, 0, CHECK_DIGITS_ENABLED>
	{
		enum { value = NUMBER % 10 };
		static const int JustToCheck = sizeof( CheckDigit<CHECK_DIGITS_ENABLED, value> );
	};

	template<uint32_t NUMBER, unsigned N>
	struct DigitsIterator
	{
		enum { value = (GetNDigit<NUMBER, N>::value << N) | DigitsIterator<NUMBER, N-1>::value };
	};
	template<uint32_t NUMBER>
	struct DigitsIterator<NUMBER, 0>
	{
		enum { value = GetNDigit<NUMBER, 0>::value };
	};

	template<uint32_t BINCONST>
	struct BinaryLiteral8bit
	{
		//If you get this assert:
		//You should enter exactly 8 digits. Only 1 and 0 are allowed! BinaryLiteral8bit(10100101);
		BINARYLITERAL_STATIC_ASSERT( (GetNDigit<BINCONST, 8, false>::value == 2) );
		enum{ value = DigitsIterator<BINCONST, 7>::value };
	};
}//namespace BL_private

// Use as follows:
// BinaryLiteral8bit(10100101);
// You should enter exactly 8 digits. Only 1 and 0 are allowed!
#define BinaryLiteral8bit( L ) BINARYLITERAL_HPP_private::BinaryLiteral8bit<2 ## L>::value;


#endif

