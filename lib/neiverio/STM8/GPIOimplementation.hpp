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
#ifndef STM8_GPIOIMPLEMENTATION_HPP_
#define STM8_GPIOIMPLEMENTATION_HPP_

#ifndef NEIVERIO_HPP_
    #error "Do not include this file directly. Use #include\"neiverio.hpp\" instead!"
#endif

//define to know on what MCU we are running
#define NEIVERIO_STM8_PORT_
//#define NEIVERIO_STM32_PORT_
//#define NEIVERIO_AVR_PORT_
//#define NEIVERIO_XMEGA_PORT_

namespace IO
{
    namespace Private
    {
        struct NativePortBase: public GpioBase
        {	
            typedef uint8_t DataT;
            enum{ Width = sizeof(DataT) * 8 };
            
            struct IOInternals
            {                            
                typedef NativePortBase Base; //do we need this????
            };
        };//struct NativePortBase
    	
        template< class T >
    	class PortImplimentation: public NativePortBase
        {
            //Helper classes to acces GPIO registers nice and easy
            IO_REG_WRAPPER(T::GetPortStuct().ODR, ODR, uint8_t);
            IO_REG_WRAPPER(T::GetPortStuct().IDR, IDR, uint8_t);
            IO_REG_WRAPPER(T::GetPortStuct().DDR, DDR, uint8_t);
            IO_REG_WRAPPER(T::GetPortStuct().CR1, CR1, uint8_t);
            IO_REG_WRAPPER(T::GetPortStuct().CR2, CR2, uint8_t);
        public:           
            //=============Generic API. Everybody should implement and respect it==============
    		static void Write(DataT value){ ODR::Set(value); }
            static DataT Read(){ return ODR::Get(); }
            static DataT PinRead(){ return IDR::Get(); }
            static void Set(DataT value){ ODR::Or(value); }
    		static void Clear(DataT value){ ODR::And( (DataT)~value ); }
            static void ClearAndSet(DataT clearMask, DataT value){ ODR::AndOr((DataT)~clearMask, value); }
    		static void Toggle(DataT value){ ODR::Xor(value); }                        

            template<DataT value>
    		static void Set(){ ODR::Or(value); }
    		template<DataT value>
    		static void Clear(){ ODR::And((DataT)~value); }
            template<DataT clearMask, DataT value>
    		static void ClearAndSet(){ ODR::AndOr((DataT)~clearMask, value); }
            template<DataT value>
    		static void Toggle(){ ODR::Xor(value); }

            struct Configure
            {   
                template<DataT MASK>
                static void OutPushPull_Slow(){ DDR::Or(MASK); CR1::Or(MASK); CR2::And( (DataT)~MASK ); }
                template<DataT MASK>
                static void OutPushPull_Medium(){ OutPushPull_Fast<MASK>(); }
                template<DataT MASK>
                static void OutPushPull_Fast(){ DDR::Or(MASK); CR1::Or(MASK); CR2::Or(MASK); }
                template<DataT MASK>
                static void OutOpenDrain_Slow(){ DDR::Or(MASK); CR1::And( (DataT)~MASK ); CR2::And( (DataT)~MASK ); }
                template<DataT MASK>
                static void OutOpenDrain_Medium(){ OutOpenDrain_Fast<MASK>(); }
                template<DataT MASK>
                static void OutOpenDrain_Fast(){ DDR::Or(MASK); CR1::And( (DataT)~MASK ); CR2::Or(MASK); }
            
                template<DataT MASK>
                static void InFloating(){ DDR::And( (DataT)~MASK ); CR1::And( (DataT)~MASK ); CR2::And( (DataT)~MASK ); }
                template<DataT MASK>
                static void InPullUp(){ DDR::And( (DataT)~MASK ); CR1::Or(MASK); CR2::And( (DataT)~MASK ); }
                template<DataT MASK>
                static void InPullDown(){ InFloating<MASK>(); } //Pull down is not supported in STM8
                template<DataT MASK>
                static void InAnalog(){ InFloating<MASK>(); }

                template<DataT MASK>
                static void EnableAF(){ }   //there is no special bit for AF in STM8
                template<DataT MASK>
                static void DisableAF(){ }  //there is no special bit for AF in STM8
                template<DataT MASK>
                static void EnableInterrupt(){ CR2::Or(MASK); } //Please apply this to INPUT pins only!
                template<DataT MASK>
                static void DisableInterrupt(){ CR2::And( (DataT)~MASK ); } //Please apply this to INPUT pins only!
            };

            //=============Hardware specific API for maximum flexibility======================            
            //TPin will expose this API to users as Pxn::HWSpecificAPI::HWSpecific_method();
            //Some operations may need MASK to work, TPin will provide it.
            template< DataT MASK=0 >
            struct HWSpecificAPI
            {      
                static GPIO_TypeDef &GetGPIORegsReference(){ return T::GetPortStuct(); }
                static void HWSpecific1(){ }
                static void HWSpecific2(){ }
            };            
    	};//PortImplimentation
    }//namespace Private


#define MAKE_PORT(portName, className, ID) \
        class className :public Private::PortImplimentation<className>{\
            static GPIO_TypeDef &GetPortStuct(){ return *portName; }\
            friend class Private::PortImplimentation<className>;\
            public:\
            enum{Id = ID};\
        };

#ifdef GPIOA
	#define USE_PORTA
    MAKE_PORT(GPIOA, Porta, 'A')
#endif

#ifdef GPIOB
	#define USE_PORTB
    MAKE_PORT(GPIOB, Portb, 'B')
#endif

#ifdef GPIOC
	#define USE_PORTC
    MAKE_PORT(GPIOC, Portc, 'C')
#endif

#ifdef GPIOD
	#define USE_PORTD
    MAKE_PORT(GPIOD, Portd, 'D')
#endif

#ifdef GPIOE
	#define USE_PORTE
    MAKE_PORT(GPIOE, Porte, 'E')
#endif

#ifdef GPIOF
	#define USE_PORTF
    MAKE_PORT(GPIOF, Portf, 'F')
#endif

#ifdef GPIOG
	#define USE_PORTG
    MAKE_PORT(GPIOG, Portg, 'G')
#endif

#ifdef GPIOH
	#define USE_PORTH
    MAKE_PORT(GPIOH, Porth, 'H')
#endif

#ifdef GPIOI
	#define USE_PORTI
    MAKE_PORT(GPIOI, Porti, 'I')
#endif

}//namespace IO
#endif //STM8_PORTS_H_

