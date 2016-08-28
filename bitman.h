#ifndef _bit_man_h_
#define _bit_man_h_

#include <stdint.h>
#include <limits.h>

/*----------------  CONSTANTS -----------------------------------------------*/
/* Mask for u8 integer */
#define U8_MASK_1BIT_LOW        ((uint8_t)0x55)
#define U8_MASK_1BIT_HIGH       ((uint8_t)0xAA)
#define U8_MASK_2BIT_LOW        ((uint8_t)0x33)
#define U8_MASK_2BIT_HIGH       ((uint8_t)0xCC)
#define U8_MASK_4BIT_LOW        ((uint8_t)0x0F)
#define U8_MASK_4BIT_HIGH       ((uint8_t)0xF0)

/* Mask for u16 integer */
#define U16_MASK_1BIT_LOW       ((uint16_t)0x5555)
#define U16_MASK_1BIT_HIGH      ((uint16_t)0xAAAA)
#define U16_MASK_2BIT_LOW       ((uint16_t)0x3333)
#define U16_MASK_2BIT_HIGH      ((uint16_t)0xCCCC)
#define U16_MASK_4BIT_LOW       ((uint16_t)0x0F0F)
#define U16_MASK_4BIT_HIGH      ((uint16_t)0xF0F0)
#define U16_MASK_8BIT_LOW       ((uint16_t)0x00FF)
#define U16_MASK_8BIT_HIGH      ((uint16_t)0xFF00)

/* Mask for u32 integer */
#define U32_MASK_1BIT_LOW       ((uint32_t)0x55555555)
#define U32_MASK_1BIT_HIGH      ((uint32_t)0xAAAAAAAA)
#define U32_MASK_2BIT_LOW       ((uint32_t)0x33333333)
#define U32_MASK_2BIT_HIGH      ((uint32_t)0xCCCCCCCC)
#define U32_MASK_4BIT_LOW       ((uint32_t)0x0F0F0F0F)
#define U32_MASK_4BIT_HIGH      ((uint32_t)0xF0F0F0F0)
#define U32_MASK_8BIT_LOW       ((uint32_t)0x00FF00FF)
#define U32_MASK_8BIT_HIGH      ((uint32_t)0xFF00FF00)
#define U32_MASK_16BIT_LOW      ((uint32_t)0x0000FFFF)
#define U32_MASK_16BIT_HIGH     ((uint32_t)0xFFFF0000)

/* Mask for u64 integer */
#define U64_MASK_1BIT_LOW       ((uint64_t)0x5555555555555555)
#define U64_MASK_1BIT_HIGH      ((uint64_t)0xAAAAAAAAAAAAAAAA)
#define U64_MASK_2BIT_LOW       ((uint64_t)0x3333333333333333)
#define U64_MASK_2BIT_HIGH      ((uint64_t)0xCCCCCCCCCCCCCCCC)
#define U64_MASK_4BIT_LOW       ((uint64_t)0x0F0F0F0F0F0F0F0F)
#define U64_MASK_4BIT_HIGH      ((uint64_t)0xF0F0F0F0F0F0F0F0)
#define U64_MASK_8BIT_LOW       ((uint64_t)0x00FF00FF00FF00FF)
#define U64_MASK_8BIT_HIGH      ((uint64_t)0xFF00FF00FF00FF00)
#define U64_MASK_16BIT_LOW      ((uint64_t)0x0000FFFF0000FFFF)
#define U64_MASK_16BIT_HIGH     ((uint64_t)0xFFFF0000FFFF0000)
#define U64_MASK_32BIT_LOW      ((uint64_t)0x00000000FFFFFFFF)
#define U64_MASK_32BIT_HIGH     ((uint64_t)0xFFFFFFFF00000000)

#define UX_MASK_XBIT_L(w,n)     (U##w##_MASK_##n##BIT_LOW)
#define UX_MASK_XBIT_H(w,n)     (U##w##_MASK_##n##BIT_HIGH)

/*---------------- FUNCTION MACROS ------------------------------------------*/


/** \brief  Calculate the result of clearing a bit at a specified position of an 
 *          integer.
 *  \param   v   an integer value.
 *  \param   n   the position of the bit to be cleared. Condition:
 *              0 <= n < (sizeof(v)*CHAR_BIT)
 *              otherwise, result is undefined.
 */
#define CLEAR_BIT(v,n)          ((v) & (~(1 << (n))))

/** Calculate the result of setting a bit at a specified position of an 
 *  integer 
 *  \param   v   an integer value.
 *  \param   n   the position of the bit to be set.
 *              0 <= n < (sizeof(v)*CHAR_BIT)
 *              otherwise, result is undefined.
 */
#define SET_BIT(v,n)            ((v) | (1 << (n)))

/** Calculate the result of toggling a bit at a specified position of an
 *  integer
 *  \param   v   an integer value.
 *  \param   n   the position of the bit to be toggled.
 *              0 <= n < (sizeof(v)*CHAR_BIT)
 *              otherwise, result is undefined.
 *  explanation:
 *  XORing with 1 negates the bit, XORing with 0 gives the same bit.
 */
#define TOGGLE_BIT(v,n)         ((v) ^ (1 << (n)))

/** Calculate the result of changing a bit at a specified position of an
 *  integer.
 *  \param   v   an integer value.
 *  \param   n   the position of the bit to be toggled.
 *              0 <= n < (sizeof(v)*CHAR_BIT)
 *              otherwise, result is undefined.
 *  \param   b   the bit value
 *              b = 0 or 1. Otherwise, result is undefined.
 */
#define REPLACE_BIT(v,n,b)      (((v)  & (~(1 << (n)))) | ((b) << (n)))

/** \brief  Merge bits from two values according to a mask.
 *  naive: (v1 & (~m)) | (v2 & m)
 *  if m is constant, two implementations have the same performance.
 *  if m is a variable, the second implementation takes 3 instructions
 *  while the naive one takes 4 instructions. So in general, the second
 *  implmentation is better.
 *  \param  v1  The value to merge in non-masked bits
 *  \param  v2  The value to merge in masked bits
 *  \param  m   The mask
 *  
 */
#define MERGE_BIT(v1,v2,m)      ((v1) ^ (((v1) ^ (v2)) & m))

/** Calculate the value after clearing the least significant bit that is set.
 *  v should be a constant or variable. passing a function returning an integer
 *  is not recommended.
 *      int x = 1; x = CLEAR_LSBSET(x);             // OK
 *      int x = CLEAR_LSBSET(0x21);                 // OK
 *
 *      int x = CLEAR_LSBSET(foo());                // NO-NO
 *  do this:
 *      int x = foo();
 *      x = CLEAR_LSBSET(x);
 *  Explanation:   
 *  subtraction of 1 from a number toggles all the bit until the least
 *  significant bit that is set.  So if we subtract a number by 1 and do bitwise
 *  & with itself (n & (n-1)), we unset the righmost set bit.
 */
#define CLEAR_LSBSET(v)         ((v)&((v)-1))

/** Retrieve the sign bit of a signed integer */
#define SIGN_BIT(v)             (((v) >> ((sizeof(v)*(CHAR_BIT)) - 1)))

/*---------------- FUNCTION PROTOTYPES --------------------------------------*/

/* bit reversal */
uint8_t     BitReverseU8(uint8_t value);
uint16_t    BitReverseU16(uint16_t value);
uint32_t    BitReverseU32(uint32_t value);
uint64_t    BitReverseU64(uint64_t value);

/* bit count */
size_t      BitSetCountU8(uint8_t value);
size_t      BitSetCountU16(uint16_t value);
size_t      BitSetCountU32(uint32_t value);
size_t      BitSetCountU64(uint64_t value);



#endif /* ifndef _bit_man_h_ */