//*****************************************************************************
// Author		: Konstantin Chizhov
// Date			: 2010
// All rights reserved.
//
// Massively patched by Trotskiy Vasily
// Date			: apr 2017
// All rights reserved.

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
#ifndef NEIVERIO_HPP_
#define NEIVERIO_HPP_

#include <stdint.h>
#include "gpiobase.hpp"
#include "ioregwrapper.hpp"

// Platform specific io ports implementation
// Add appropriate platform specific folder to your include paths
// This should declare ports like Porta, Portb, Portc ...etc
#include "GPIOimplementation.hpp"

//will declare port pins to have good names like Pa0, Pa2, Pa3 ...etc
#include "DeclarePortPins.hpp"

//NullPort and NullPin can be usefull as a dummy
namespace IO
{	
	struct NullPort: public Private::GpioBase
	{			
        typedef uint8_t DataT;
        enum{ Id = '-' };
		enum{ Width = sizeof(DataT) * 8 };
        
        struct IOInternals
        {
            typedef Private::GpioBase Base;
        };

		//Main runtime API======================
        static void Write(DataT value){ }
        static DataT Read(){ return 0; }
        static DataT PinRead(){ return 0; }
        static void Set(DataT value){ }
        static void Clear(DataT value){ }
        static void ClearAndSet(DataT clearMask, DataT value){ }
        static void Toggle(DataT value){ }            

        //Main compile time static API==================
        template<DataT value>
        static void Set(){ }
        template<DataT value>
        static void Clear(){ }
        template<DataT clearMask, DataT value>
        static void ClearAndSet(){ }
        template<DataT value>
        static void Toggle(){ }
        
        struct Configure
        {   
            template<DataT MASK>
            static void OutPushPull_Slow(){ }
            template<DataT MASK>
            static void OutPushPull_Medium(){ }
            template<DataT MASK>
            static void OutPushPull_Fast(){ }
            template<DataT MASK>
            static void OutOpenDrain_Slow(){ }
            template<DataT MASK>
            static void OutOpenDrain_Medium(){ }
            template<DataT MASK>
            static void OutOpenDrain_Fast(){ }
        
            template<DataT MASK>
            static void InFloating(){  }
            template<DataT MASK>
            static void InPullUp(){  }
            template<DataT MASK>
            static void InPullDown(){  } 
            template<DataT MASK>
            static void InAnalog(){  }

            template<DataT MASK>
            static void EnableAF(){ }   
            template<DataT MASK>
            static void DisableAF(){ } 
            template<DataT MASK>
            static void EnableInterrupt(){ }
            template<DataT MASK>
            static void DisableInterrupt(){ }                
        };
        //=============Hardware specific API for maximum flexibility======================            
        //TPin public interface will be extended by this hardware specific API
        //Some operations may need MASK to work, TPin will provide it for us
        template<DataT MASK=0>
        struct HWSpecificAPI{  };        
	};//struct NullPort

	typedef Private::TPin< NullPort, 0 > NullPin;
}

#endif//NEIVERIO_HPP_

