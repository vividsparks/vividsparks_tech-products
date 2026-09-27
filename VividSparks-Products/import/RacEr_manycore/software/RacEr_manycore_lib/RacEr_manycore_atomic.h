#ifndef _RACER_MANYCORE_ATOMIC_H
#define _RACER_MANYCORE_ATOMIC_H

inline int RacEr_amoswap (int* p, int val)
{
  int result;
  asm volatile ("amoswap.w %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoswap_aq (int* p, int val)
{
  int result;
  asm volatile ("amoswap.w.aq %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoswap_rl(int* p, int val)
{
  int result;
  asm volatile ("amoswap.w.rl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoswap_aqrl(int* p, int val)
{
  int result;
  asm volatile ("amoswap.w.aqrl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}


inline int RacEr_amoor (int* p, int val)
{
  int result;
  asm volatile ("amoor.w %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoor_aq (int* p, int val)
{
  int result;
  asm volatile ("amoor.w.aq %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoor_rl (int* p, int val)
{
  int result;
  asm volatile ("amoor.w.rl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoor_aqrl (int* p, int val)
{
  int result;
  asm volatile ("amoor.w.aqrl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoadd (int* p, int val)
{
  int result;
  asm volatile ("amoadd.w %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoadd_aq (int* p, int val)
{
  int result;
  asm volatile ("amoadd.w.aq %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoadd_rl (int* p, int val)
{
  int result;
  asm volatile ("amoadd.w.rl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

inline int RacEr_amoadd_aqrl (int* p, int val)
{
  int result;
  asm volatile ("amoadd.w.aqrl %[result], %[val], 0(%[p])" \
                : [result] "=r" (result) \
                : [p] "r" (p), [val] "r" (val));
  return result;
}

#endif
