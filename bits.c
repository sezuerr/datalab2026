/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!(x&&y)&&(x^y))
    {
        return 0;
    }
    else
    {
        return !((x>>31)^(y>>31));
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int pos=0;
    int shift;

    shift=((v>>16)>0)<<4;
    pos=pos|shift;
    v=v>>shift;

    shift=((v>>8)>0)<<3; 
    pos=pos|shift;
    v=v>>shift;

    shift=((v>>4)>0)<<2;
    pos=pos|shift;
    v=v>>shift;

    shift=((v>>2)>0)<<1;
    pos=pos|shift;
    v=v>>shift;

    shift=(v>>1)>0;
    pos=pos|shift;

    return pos;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift=n<<3;
    int mshift=m<<3;

    int nbyte=(x>>nshift)&0xFF;
    int mbyte=(x>>mshift)&0xFF;

    int mask=~((0xFF<<nshift)|(0xFF<<mshift));

    return (x&mask)|(nbyte<<mshift)|(mbyte<<nshift);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {

    unsigned result=0;
    int i=32;
    
    while(i){
        result=(result<<1)|(v&1);
        v=v>>1;
        i--;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    
    int mask=~(~0<<(32+~n)<<1);
    return (x>>n)&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int x0=x^(~0);
    x0|=x0>>1;
    x0|=x0>>2;
    x0|=x0>>4;
    x0|=x0>>8;
    x0|=x0>>16;
    x=x&(~x0);

    x=(x&0x55555555)+((x>>1)&0x55555555);
    x=(x&0x33333333)+((x>>2)&0x33333333);
    x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
    x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
    x=(x&0x0000FFFF)+((x>>16)&0x0000FFFF);
    return x;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {

    unsigned ux = x;
    unsigned s = ux & 0x80000000;
    int e = 31;
    int shift;
    unsigned f;
    unsigned rest;
    unsigned half;

    if (x == 0)
        return 0;

    if (s)
        ux = -ux;

    while (!(ux >> e))
        e = e - 1;

    unsigned exp = e + 127;

    shift = e - 23;

    if (shift <= 0) {
        f = ux << (-shift);
    } else {
        f = ux >> shift;
        rest = ux & ((1 << shift) - 1);
        half = 1 << (shift - 1);

        if (rest > half)
            f++;
        else if (rest == half)
            if (f & 1)
                f++;

        if (f >> 24) {
            exp++;
            f = f >> 1;
        }
    }

    f &= 0x7FFFFF;

    return s | (exp << 23) | f;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0) {
        frac = frac << 1;
        return sign | frac;
    }

    if (exp < 255) {
        exp = exp + 1;
        return sign | (exp << 23) | frac;
    }

    return uf;
}
/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned high;
    unsigned val;
    int e;

    if (!exp)
        return 0;

    if (!(exp - 0x7FF))
        return 0x80000000;

    e = exp - 1023;

    if (e < 0)
        return 0;

    if (e > 30)
        return 0x80000000;

    high = (uf2 & 0xFFFFF) | 0x100000;

    if (e < 20)
        val = high >> (20 - e);
    else
        val = (high << (e - 20))
            | (uf1 >> (52 - e));

    if (sign)
        return -val;

    return val;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    int exp;

    if (x > 127)
        return 0x7F800000;

    if (x < -149)
        return 0;

    if (x < -126)
        return 1 << (x + 149);

    exp = x + 127;
    return exp << 23;
}
