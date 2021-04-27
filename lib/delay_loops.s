#include <vregs.inc>
//void delay_loop_impl(uint8_t n);
        PUBLIC delay_loop_impl
        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
delay_loop_impl:
??delay_loop_impl_1:
        DEC       A
        JRNE      L:??delay_loop_impl_1
        RET

//void delay_loop2_impl(uint16_t n);
        PUBLIC delay_loop2_impl
        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
delay_loop2_impl:
??delay_loop_impl2_1:
        DECW      X        
        JRNE      L:??delay_loop_impl2_1	
        RET

//void delay_loop_nested_impl(uint16_t innerLoopN, uint16_t outerLoopN);
		PUBLIC delay_loop_nested_impl
        SECTION `.near_func.text`:CODE:REORDER:NOROOT(0)
        CODE
delay_loop_nested_impl:
		LDW       s:?w0, X
??delay_loop_nested_impl_outer:        
        LDW       X, s:?w0
??delay_loop_nested_impl_inner:        
        DECW      X        
        JRNE      L:??delay_loop_nested_impl_inner
        DECW      Y
        JRNE      L:??delay_loop_nested_impl_outer
		RET

        SECTION VREGS:DATA:REORDER:NOROOT(0)

        END

