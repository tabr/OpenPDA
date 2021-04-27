//*****************************************************************************
//
// Author		: Trotzky Vasily
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
#ifndef TPINEXTENSIONAPI_HPP_
#define TPINEXTENSIONAPI_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

#include <stdint.h>
#include "boost_static_assert.h"

//We know on which MCU we are running, so use it for HW depandend ops(i.e. dirty hacks :)))
#ifdef NEIVERIO_STM8_PORT_

#endif
#ifdef NEIVERIO_STM32_PORT_

#endif
#ifdef NEIVERIO_AVR_PORT_

#endif
#ifdef NEIVERIO_XMEGA_PORT_

#endif

namespace IO
{
    namespace Private
    {          
        template<class TPIN>
        class TPinInterfaceExtension
        {                   
            typedef typename TPIN::IOInternals::Port PORT;
            typedef typename PORT::DataT PortDataT;
            typedef typename TPIN::IOInternals::ConfigPort CONFIG_PORT;
            static const bool Inverted = TPIN::IOInternals::Inverted;
            static const uint8_t PIN = TPIN::IOInternals::PortPinNumber;
            static const PortDataT MASK = (PortDataT)1U << PIN;
        public:
		static void SetOutHigh() 
                  {
                  TPIN::Set();
                  }
    		static void SetOutLow()
                  {
                  TPIN::Clear();
                  }
    		static void SetOutToggle()
                  {
                  TPIN::Toggle();
                  }
			static void SetPullUp()
                  {
                  SetDirInPullup();
                  }
			static bool IsPinLow()
                  {
                  return !(TPIN::IsSet());
                  }
			static bool IsPinHigh()
                  {
                  return TPIN::IsSet();
                  }
			static void SetDirIn()
                  {
                  SetDirInFloating();
                  }
			static void SetDirInFloating()
                  {
                  CONFIG_PORT::Configure::template InFloating<MASK>();
                  }
			static void SetDirInPullup()
                  {
                  CONFIG_PORT::Configure::template InPullUp<MASK>();
                  }
		static void SetDirOut()
                  {
                  CONFIG_PORT::Configure::template OutPushPull_Fast<MASK>();
                  }
            /*
            *~~Put your TPin public interface extensions here~~
            *  
            * Use TPIN to access already implemented TPin publics
            * PORT, PIN, CONFIG_PORT are = TPin template parameters
            * MASK is the same as MASK in TPin implementation             
            *  
            * I want you to feel comfortable, almost like you are inside TPin class :)
            */

            //Example of using already implemented TPin method
            static void ExtensionMethod1()
            {
                TPIN::Configure::OutPushPull_Fast();
            }

            //Example of accessing port associated with TPin
            static void ExtensionMethod2()
            {
                CONFIG_PORT::Configure::template OutPushPull_Slow<MASK>();
            }
            
            //Example of accessing port low level API
            //HIGHLY NOT RECOMENDED! 
            //Remember, you are extending TPin class interface
            //keep TPin as generic and portable as possible
            static void ExtensionMethod3()
            {
                PORT::template HWSpecificAPI<MASK>::GetGPIORegsReference().DDR |= MASK;
            }
        };//class TPinInterfaceExtension
    }//namespace Private
}//namespace IO
#endif

