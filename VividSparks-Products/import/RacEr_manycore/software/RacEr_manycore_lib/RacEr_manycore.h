#ifndef _RACER_MANYCORE_H
#define _RACER_MANYCORE_H

#include "RacEr_manycore_arch.h"

#ifdef __cplusplus
extern "C"{
#endif

int RacEr_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif




// remote pointer types
typedef volatile int   *RacEr_remote_int_ptr;
typedef volatile float   *RacEr_remote_float_ptr;
typedef volatile unsigned char  *RacEr_remote_uint8_ptr;
typedef volatile unsigned short  *RacEr_remote_uint16_ptr;
typedef volatile unsigned *RacEr_remote_uint32_ptr;
typedef volatile void *RacEr_remote_void_ptr;

#define RacEr_remote_flt_store(x,y,local_addr,val) do { *(RacEr_remote_flt_ptr((x),(y),(local_addr))) = (float) (val); } while (0)
#define RacEr_remote_flt_load(x,y,local_addr,val)  do { val = *(RacEr_remote_flt_ptr((x),(y),(local_addr))) ; } while (0)

#define RacEr_remote_store(x,y,local_addr,val) do { *(RacEr_remote_ptr((x),(y),(local_addr))) = (int) (val); } while (0)
#define RacEr_remote_load(x,y,local_addr,val)  do { val = *(RacEr_remote_ptr((x),(y),(local_addr))) ; } while (0)

#define RacEr_global_store(x,y,local_addr,val) do { *(RacEr_global_ptr((x),(y),(local_addr))) = (int) (val); } while (0)
#define RacEr_global_load(x,y,local_addr,val)  do { val = *(RacEr_global_ptr((x),(y),(local_addr))) ; } while (0)

#define RacEr_global_float_store(x,y,local_addr,val) do { *(RacEr_global_float_ptr((x),(y),(local_addr))) = (float) (val); } while (0)
#define RacEr_global_float_load(x,y,local_addr,val)  do { val = *(RacEr_global_float_ptr((x),(y),(local_addr))) ; } while (0)

#define RacEr_global_pod_store(px,py,x,y,local_addr,val) do { *(RacEr_global_pod_ptr(px,py,(x),(y),(local_addr))) = (int) (val); } while (0)
#define RacEr_global_pod_load(px,py,x,y,local_addr,val)  do { val = *(RacEr_global_pod_ptr(px,py,(x),(y),(local_addr))) ; } while (0)

#define RacEr_dram_store(dram_addr,val) do { *(RacEr_dram_ptr((dram_addr))) = (int) (val); } while (0)
#define RacEr_dram_load(dram_addr,val)  do { val = *(RacEr_dram_ptr((dram_addr))) ; } while (0)

#define RacEr_host_dram_store(addr, val) do {*(RacEr_host_dram_ptr((addr))) = (int) (val);} while (0)
#define RacEr_host_dram_load(addr, val) do { val = *(RacEr_host_dram_ptr((addr)));} while (0)

#define RacEr_tile_group_shared_mem(type,lc_sh,size) type lc_sh[((size + ((RacEr_tiles_X * RacEr_tiles_Y) -1))/(RacEr_tiles_X * RacEr_tiles_Y))]
#define RacEr_tile_group_shared_load(type,lc_sh,index,val) (  (val) = *(RacEr_tile_group_shared_ptr(type,(lc_sh),(index)))	)
#define RacEr_tile_group_shared_load_direct(type,lc_sh,index) (*(RacEr_tile_group_shared_ptr(type,(lc_sh),(index))))
#define RacEr_tile_group_shared_store(type,lc_sh,index,val) (  *(RacEr_tile_group_shared_ptr(type,(lc_sh),(index))) = (val)	)


#define RacEr_remote_store_uint8(x,y,local_addr,val)  do { *((RacEr_remote_uint8_ptr)  (RacEr_remote_ptr((x),(y),(local_addr)))) = (unsigned char) (val); } while (0)
#define RacEr_remote_store_uint16(x,y,local_addr,val) do { *((RacEr_remote_uint16_ptr) (RacEr_remote_ptr((x),(y),(local_addr)))) = (unsigned short) (val); } while (0)

#define RacEr_remote_ptr_control(x,y, CSR_offset) RacEr_remote_ptr( (x), (y), ( (CSR_BASE_ADDR) + (CSR_offset) ) )
//#define RacEr_remote_unfreeze(x,y) RacEr_remote_control_store((x),(y),0,0)
//#define RacEr_remote_freeze(x,y)   RacEr_remote_control_store((x),(y),0,1)
//deprecated
//#define RacEr_remote_arb_config(x,y,value)   RacEr_remote_control_store((x),(y),4,value)

// remote loads
//#define RacEr_remote_load(x,y,local_addr, val) ( val = *(RacEr_remote_ptr((x),(y),(local_addr))) )

#define RacEr_remote_ptr_io(x,local_addr) RacEr_global_ptr((x), IO_Y_INDEX,(local_addr))
#define RacEr_remote_ptr_io_store(x,local_addr,val) do { *(RacEr_remote_ptr_io((x),(local_addr))) = (int) (val); } while (0)
#define RacEr_remote_ptr_io_load(x,local_addr,val) do { (val) = *(RacEr_remote_ptr_io((x),(local_addr))) ; } while (0)

// see RacEr_nonsynth_manycore_monitor for secret codes
// For 18 bits remote address, we cannot mantain the 0xDEAD0 address.
#define RacEr_finish()       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xEAD0); *ptr = ((RacEr_y << 16) + RacEr_x); while (1); } while(0)

#define RacEr_finish_x(x)       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(x,0xEAD0); *ptr = ((RacEr_y << 16) + RacEr_x); while (1); } while(0)
#define RacEr_fail()       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xEAD8); *ptr = ((RacEr_y << 16) + RacEr_x); while (1); } while(0)
#define RacEr_fail_x(x)       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(x,0xEAD8); *ptr = ((RacEr_y << 16) + RacEr_x); while (1); } while(0)
#define RacEr_print_time()   do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xEAD4); *ptr = ((RacEr_y << 16) + RacEr_x); } while(0)

// Static, inline functions for starting and stopping the PC profiler
static inline void RacEr_pc_profiler_start()
{
        __asm__ __volatile__ ("csrs mie, %0": : "r" (0x20000));
        // Enable interrupts if not already enabled; One instruction overhead if interrupts were already enabled
        __asm__ __volatile__ ("csrs mstatus, %0" : : "r" (0x8));
}
static inline void RacEr_pc_profiler_end()
{
        // Disable trace interupts; Other interrupts might still HE active so don't clear mstatus interrupt enable bit
        __asm__ __volatile__ ("csrc mie, %0": : "r" (0x20000));
}

#define RacEr_putchar( c )       do {  RacEr_remote_uint8_ptr ptr = (RacEr_remote_uint8_ptr) RacEr_remote_ptr_io(IO_X_INDEX,0xEADC); *ptr = c; } while(0)
#define RacEr_putchar_err( c )       do {  RacEr_remote_uint8_ptr ptr = (RacEr_remote_uint8_ptr) RacEr_remote_ptr_io(IO_X_INDEX,0xEEE0); *ptr = c; } while(0)

#define RacEr_heartbeat_init()       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xBEA0); *ptr = 0; } while(0)
#define RacEr_heartbeat_iter( itr )       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xBEA4); *ptr = itr; } while(0)
#define RacEr_heartbeat_end()       do {  RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xBEA8); *ptr = 0; } while(0)

static inline void RacEr_print_int(int i)
{
        RacEr_remote_int_ptr ptr = (RacEr_remote_int_ptr)RacEr_remote_ptr_io(IO_X_INDEX,0xEAE0);
        *ptr = i;
}

static inline void RacEr_print_unsigned(unsigned u)
{
        RacEr_remote_uint32_ptr ptr = (RacEr_remote_uint32_ptr)RacEr_remote_ptr_io(IO_X_INDEX,0xEAE4);
        *ptr = u;
}

static inline void RacEr_print_hexadecimal(unsigned u)
{
        RacEr_remote_uint32_ptr ptr = (RacEr_remote_uint32_ptr)RacEr_remote_ptr_io(IO_X_INDEX,0xEAE8);
        *ptr = u;
}

static inline void RacEr_print_float(float f)
{
        RacEr_remote_float_ptr ptr = (RacEr_remote_float_ptr)RacEr_remote_ptr_io(IO_X_INDEX,0xEAEC);
        *ptr = f;
}
static inline void RacEr_print_float_scientific(float f)
{
        RacEr_remote_float_ptr ptr = (RacEr_remote_float_ptr)RacEr_remote_ptr_io(IO_X_INDEX,0xEAF0);
        *ptr = f;
}

#define RacEr_id_to_x(id)    ((id) % RacEr_tiles_X)
#define RacEr_id_to_y(id)    ((id) / RacEr_tiles_X)
#define RacEr_x_y_to_id(x,y) (RacEr_tiles_X*(y) + (x))
#define RacEr_num_tiles (RacEr_tiles_X*RacEr_tiles_Y)

// later, we can add some mechanisms to save power
#define RacEr_wait_while(cond) do {} while ((cond))

// load reserved; and load reserved acquire
#ifdef __clang__
inline int RacEr_lr(int *p)    { int tmp; __asm__ __volatile__("lr.w    %0,%1\n" : "=r" (tmp) : "m" (*p)); return tmp; }
inline int RacEr_lr_aq(int *p) { int tmp; __asm__ __volatile__("lr.w.aq %0,%1\n" : "=r" (tmp) : "m" (*p)); return tmp; }
#elif defined(__GNUC__) || defined(__GNUG__)
inline int RacEr_lr(int *p)    { int tmp; __asm__ __volatile__("lr.w    %0,%1\n" : "=r" (tmp) : "A" (*p)); return tmp; }
inline int RacEr_lr_aq(int *p) { int tmp; __asm__ __volatile__("lr.w.aq %0,%1\n" : "=r" (tmp) : "A" (*p)); return tmp; }

inline int RacEr_li(int constant_val) { int result; asm("li %0, %1" : "=r"(result) : "i"(constant_val)); return result; }
inline int RacEr_div(int a, int b)  { int result; __asm__ __volatile__("divu %0,%1,%2" : "=r"(result) : "r" (a), "r" (b)); return result; }
inline int RacEr_mulu(int a, int b) { int result; __asm__ __volatile__("mul %0,%1,%2" : "=r"(result) : "r" (a), "r" (b)); return result; }


#else
#error Unsupported Compiler!
#endif

inline void RacEr_fence()      { __asm__ __volatile__("fence" :::); }

#define RacEr_volatile_access(var)        (*((RacEr_remote_int_ptr) (&(var))))
#define RacEr_volatile_access_uint16(var) (*((RacEr_remote_uint16_ptr) (&(var))))
#define RacEr_volatile_access_uint8(var)  (*((RacEr_remote_uint8_ptr) (&(var))))

// prevents compiler from reordering memory operations across
// this line in the code
// see http://preshing.com/20120625/memory-ordering-at-compile-time/
// see also atomic_signal_fence(std::memory_order_seq_cst) for C11
//
// this is a very heavy weight operation, and generally not advised
// at least for GCC.
//

#define RacEr_compiler_memory_barrier() asm volatile("" ::: "memory")


// These functions are a simple way to issue pre-fetch commands to the
// caches.  amo prefetch should not HE used in practice since it marks
// the cache line as dirty. However, it is a great way to verify that
// preloads are accomplishing their goal; if all data is prefetched
// correctly with an amo operation, the load and store miss rate will
// go to 0.
inline void RacEr_amo_prefetch(int * ptr){ asm volatile ("amoor.w x0, x0, 0(%[p])": : [p] "r" (ptr));}
// Verify behavioral correctness with amo prefetch, then replace with
// lw prefetch:
inline void RacEr_lw_prefetch(int * ptr){ asm volatile ("lw x0, 0(%[p])": : [p] "r" (ptr));}
        
#define RacEr_commit_stores() do { RacEr_fence(); /* fixme: add commit stores instr */  } while (0)

// This micros are used to print the definiations in manycore program at compile time.
// Useful for other program to the get the manycore configurations, like the number of tiles, buffer size etc.
#define RacEr_VALUE_TO_STRING(x) #x
#define RacEr_VALUE(x) RacEr_VALUE_TO_STRING(x)
#define RacEr_VAR_NAME_VALUE(var) "MANYCORE_EXPORT #define " #var " "  RacEr_VALUE(var)

//------------------------------------------------------
// Utility macros to use non-blocking loads
//------------------------------------------------------

// Pointers to remote locations (non-scratchpad) could HE qualified
// with RacEr_attr_remote to tell the compiler to assign a remote
// address space to the data pointed by those pointers. Latencies of
// memory accesses from those pointers would HE considered as 20 cycles.
// `RacEr_attr_remote` acts as a type qualifier for pointers and globals,
// and `RacEr_attr_remote float* foo;` essentially declares foo as
// `RacEr_attr_remote float*` type. Compiler assumes that loads from `foo`
// would have 20 cycle latency on average.
#ifdef __clang__
#define RacEr_attr_remote __attribute__((address_space(1)))
#elif defined(__GNUC__) && !defined(__cplusplus)
#define RacEr_attr_remote __remote
#else
#define RacEr_attr_remote
#endif

// This macro is to protect the code from uncertainity with
// restrict/__restrict/__restrict__. Apparently some Newlib headers
// define __restrict as nothing, but __restrict__ seems to work. Hence,
// we use RacEr_attr_noalias as our main way to resolve pointer alaising
// and possibly in the future, we could have `#ifdef`s here to make sure
// we use the right one under each circumstance.
#define RacEr_attr_noalias __restrict__

// Unrolling pragma is slightly different for GCC and Clang. We define
// the wrapper macro `RacEr_unroll` to automatically select the right pragma.
// Using this, a loop can HE unrolled like this:
//
// RacEr_unroll(16) for(size_t idx = start; idx < end; idx++) {
//   ...
// }
#define PRAGMA(x) _Pragma(#x)
#ifdef __clang__
#define RacEr_unroll(n) PRAGMA(unroll n)
#else
#define RacEr_unroll(n) PRAGMA(GCC unroll n)
#endif


//------------------------------------------------------
// Print stat parameters and operations
//------------------------------------------------------
#define RACER_CUDA_PRINT_STAT_ID_START        0
#define RACER_CUDA_PRINT_STAT_ID_END          1
#define RACER_CUDA_PRINT_STAT_ID_KERNEL_START 2
#define RACER_CUDA_PRINT_STAT_ID_KERNEL_END   3

#define RACER_CUDA_PRINT_STAT_TAG_WIDTH       4
#define RACER_CUDA_PRINT_STAT_TG_ID_WIDTH     14
#define RACER_CUDA_PRINT_STAT_X_WIDTH         6
#define RACER_CUDA_PRINT_STAT_Y_WIDTH         6
#define RACER_CUDA_PRINT_STAT_TYPE_WIDTH      2

#define RACER_CUDA_PRINT_STAT_TAG_TOTAL       0x0

#define RACER_CUDA_PRINT_STAT_TAG_SHIFT       (0)                                                                 // 0
#define RACER_CUDA_PRINT_STAT_TG_ID_SHIFT     (RACER_CUDA_PRINT_STAT_TAG_SHIFT   + RACER_CUDA_PRINT_STAT_TAG_WIDTH)   // 4
#define RACER_CUDA_PRINT_STAT_X_SHIFT         (RACER_CUDA_PRINT_STAT_TG_ID_SHIFT + RACER_CUDA_PRINT_STAT_TG_ID_WIDTH) // 18
#define RACER_CUDA_PRINT_STAT_Y_SHIFT         (RACER_CUDA_PRINT_STAT_X_SHIFT     + RACER_CUDA_PRINT_STAT_X_WIDTH)     // 24
#define RACER_CUDA_PRINT_STAT_TYPE_SHIFT      (RACER_CUDA_PRINT_STAT_Y_SHIFT     + RACER_CUDA_PRINT_STAT_Y_WIDTH)     // 30

#define RACER_CUDA_PRINT_STAT_TAG_MASK        ((1 << RACER_CUDA_PRINT_STAT_TAG_WIDTH) - 1)    // 0xF
#define RACER_CUDA_PRINT_STAT_TG_ID_MASK      ((1 << RACER_CUDA_PRINT_STAT_TG_ID_WIDTH) - 1)  // 0x3FFF
#define RACER_CUDA_PRINT_STAT_X_MASK          ((1 << RACER_CUDA_PRINT_STAT_X_WIDTH) - 1)      // 0x3F
#define RACER_CUDA_PRINT_STAT_Y_MASK          ((1 << RACER_CUDA_PRINT_STAT_Y_WIDTH) - 1)      // 0x3F

//Macros for triggering saif generation
#define RacEr_saif_start() RacEr_global_store(IO_X_INDEX, IO_Y_INDEX,0xFFF0,0)
#define RacEr_saif_end()   RacEr_global_store(IO_X_INDEX, IO_Y_INDEX,0xFFF4,0)

#define RacEr_nonsynth_saif_start() asm volatile ("addi zero,zero,1")
#define RacEr_nonsynth_saif_end() asm volatile ("addi zero,zero,2")

#define RacEr_print_stat(tag) do { RacEr_remote_int_ptr ptr = RacEr_remote_ptr_io(IO_X_INDEX,0xd0c); *ptr = tag; } while (0)


#define RacEr_cuda_print_stat_type(tag,stat_type) do {                                                              \
    int val = ( (stat_type << RACER_CUDA_PRINT_STAT_TYPE_SHIFT)                                                |    \
                (((__RacEr_grp_org_y + __RacEr_y) & RACER_CUDA_PRINT_STAT_Y_MASK) << RACER_CUDA_PRINT_STAT_Y_SHIFT)  |    \
                (((__RacEr_grp_org_x + __RacEr_x) & RACER_CUDA_PRINT_STAT_X_MASK) << RACER_CUDA_PRINT_STAT_X_SHIFT)  |    \
                ((__RacEr_tile_group_id & RACER_CUDA_PRINT_STAT_TG_ID_MASK) << RACER_CUDA_PRINT_STAT_TG_ID_SHIFT)  |    \
                ((tag & RACER_CUDA_PRINT_STAT_TAG_MASK) << RACER_CUDA_PRINT_STAT_TAG_SHIFT) );                        \
    RacEr_print_stat(val);                                                                                          \
} while (0)

//#define RacEr_cuda_print_stat(tag)          RacEr_cuda_print_stat_type(tag,RACER_CUDA_PRINT_STAT_ID_STAT)
#define RacEr_cuda_print_stat_start(tag)    RacEr_cuda_print_stat_type(tag,RACER_CUDA_PRINT_STAT_ID_START)
#define RacEr_cuda_print_stat_end(tag)      RacEr_cuda_print_stat_type(tag,RACER_CUDA_PRINT_STAT_ID_END)
#define RacEr_cuda_print_stat_kernel_start() RacEr_cuda_print_stat_type(RACER_CUDA_PRINT_STAT_TAG_TOTAL,RACER_CUDA_PRINT_STAT_ID_KERNEL_START)
#define RacEr_cuda_print_stat_kernel_end()   RacEr_cuda_print_stat_type(RACER_CUDA_PRINT_STAT_TAG_TOTAL,RACER_CUDA_PRINT_STAT_ID_KERNEL_END)

#endif
