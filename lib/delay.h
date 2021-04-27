#ifndef DELAY_H_
#define DELAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_CPU
    #define F_CPU 16000000UL //16MHZ
    #warning "You should define F_CPU!!! Using 16MHz as default value."
#endif

#define DELAY_CYCLES  3
#define DELAY_CALLRET_OVERHEAD_COMP  2 //call/ret overhead compensation
//8 cycles calling/returning overhead and 3 cycles per 1 iteration
//no zero check! n==0 will give maximum delay(256 * 3 + 8=776cycles)
void delay_loop_impl(uint8_t n);

#define DELAY2_CALLRET_OVERHEAD  2
#define DELAY2_CYCLES  4
//9 cycles calling/returning overhead and 4 cycles per 1 iteration
//no zero check! n==0 will give maximum delay(65536 * 4 + 9=262153cycles)
void delay_loop2_impl(uint16_t n);

#define DELAYNEST_INNER_CYCLES  4
//innerLoop timings = 4*innerLoopN cycles. if innerLoopN==1 then 3 cycles;
//outerLoop timings = innerLoopCycles + 6(outer overhead) * outerLoopN
//call/ret overhead(once on calling) 11 cycles(depending on compiler's luck)
//no zero check! n==0 will give maximum delay(6536 iterations)
void delay_loop_nested_impl(uint16_t innerLoopN, uint16_t outerLoopN);


#pragma inline=forced
static inline void _delay_us(float usDelay);
#pragma inline=forced
static inline void _delay_ms(float msDelay);


void _delay_us(float usDelay)
{
    uint8_t __ticks;
	const float __tmp = ((F_CPU) / 3e6) * usDelay;
	const float __tmp2 = ((F_CPU) / 4e6) * usDelay;
	if (__tmp2 > 65535)
	{
        //iterations for 100us delay
        const uint16_t innerLoop100usIters = (uint16_t)((F_CPU) / 4e6) * 100.0f;
        //100.375 instead of 100 to compensate 6 cycles outer loop overhead
        const uint16_t outerLoopIters = (uint16_t)(usDelay / 100.375f); 
        delay_loop_nested_impl(innerLoop100usIters, outerLoopIters);
        return;
	}
	else if (__tmp > 255)
	{
		const uint16_t __ticks = (uint16_t)__tmp2;
		delay_loop2_impl( __ticks - DELAY2_CALLRET_OVERHEAD );
		return;
	}
	else
		__ticks = (uint8_t)__tmp;

    if( __ticks < DELAY_CALLRET_OVERHEAD_COMP )
      __ticks = 1;
    else
      __ticks = __ticks - DELAY_CALLRET_OVERHEAD_COMP;
	delay_loop_impl(__ticks);
}

void _delay_ms(float msDelay)
{
    _delay_us( msDelay * 1000 );
}

#ifdef __cplusplus
}
#endif

#endif

