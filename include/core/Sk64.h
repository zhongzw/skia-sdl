
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef Sk64_DEFINED
#define Sk64_DEFINED

#include "SkTypes.h"

/** \class Sk64

    Sk64 is a 64-bit math package that does not require long long support from the compiler.
*/
struct SK_API Sk64 {
private:
    int32_t  fHi;   //!< the high 32 bits of the number (including sign)
    uint32_t fLo;   //!< the low 32 bits of the number

public:
    int32_t hi() const { return fHi; }
    uint32_t lo() const { return fLo; }

    int64_t as64() const { return ((int64_t)fHi << 32) | fLo; }
    int64_t getLongLong() const { return this->as64(); }

    /** Returns non-zero if the Sk64 can be represented as a signed 32 bit integer
    */
    SkBool is32() const { return fHi == ((int32_t)fLo >> 31); }

    /** Returns non-zero if the Sk64 cannot be represented as a signed 32 bit integer
    */
    SkBool is64() const { return fHi != ((int32_t)fLo >> 31); }

    /** Return the signed 32 bit integer equivalent. Asserts that is32() returns non-zero.
    */
    int32_t get32() const { SkASSERT(this->is32()); return (int32_t)fLo; }

    /** Returns the square-root of the number as a signed 32 bit value. */
    int32_t getSqrt() const;

    /** Returns the number of leading zeros of the absolute value of this.
        Will return in the range [0..64]
    */
    int getClzAbs() const;

    /** Returns non-zero if the number is zero */
    SkBool  isZero() const { return (fHi | fLo) == 0; }

    /** Returns non-zero if the number is non-zero */
    SkBool  nonZero() const { return fHi | fLo; }

    /** Returns non-zero if the number is negative (number < 0) */
    SkBool  isNeg() const { return (uint32_t)fHi >> 31; }

    /** Returns non-zero if the number is positive (number > 0) */
    SkBool  isPos() const { return ~(fHi >> 31) & (fHi | fLo); }

    /** Returns -1,0,+1 based on the sign of the number */
    int     getSign() const { return (fHi >> 31) | Sk32ToBool(fHi | fLo); }

    /** Negate the number */
    void    negate();

    /** If the number < 0, negate the number
    */
    void    abs();

    /** Returns the number of bits needed to shift the Sk64 to the right
        in order to make it fit in a signed 32 bit integer.
    */
    int     shiftToMake32() const;

    /** Set the number to zero */
    void    setZero() { fHi = fLo = 0; }

    /** Set the high and low 32 bit values of the number */
    void    set(int32_t hi, uint32_t lo) { fHi = hi; fLo = lo; }

    /** Set the number to the specified 32 bit integer */
    void    set(int32_t a) { fHi = a >> 31; fLo = a; }

    /** Set the number to the product of the two 32 bit integers */
    void    setMul(int32_t a, int32_t b);

    /** extract 32bits after shifting right by bitCount.
        Note: itCount must be [0..63].
        Asserts that no significant high bits were lost.
    */
    int32_t getShiftRight(unsigned bitCount) const;

    /** Shift the number left by the specified number of bits.
        @param bits How far to shift left, must be [0..63]
    */
    void    shiftLeft(unsigned bits);

    /** Shift the number right by the specified number of bits.
        @param bits How far to shift right, must be [0..63]. This
        performs an arithmetic right-shift (sign extending).
    */
    void    shiftRight(unsigned bits);

    /** Shift the number right by the specified number of bits, but
        round the result.
        @param bits How far to shift right, must be [0..63]. This
        performs an arithmetic right-shift (sign extending).
    */
    void    roundRight(unsigned bits);

    /** Add the specified 32 bit integer to the number */
    void add(int32_t lo) {
        int32_t  hi = lo >> 31; // 0 or -1
        uint32_t sum = fLo + (uint32_t)lo;

        fHi = fHi + hi + (sum < fLo);
        fLo = sum;
    }

    /** Add the specified Sk64 to the number */
    void add(int32_t hi, uint32_t lo) {
        uint32_t sum = fLo + lo;

        fHi = fHi + hi + (sum < fLo);
        fLo = sum;
    }

    /** Add the specified Sk64 to the number */
    void    add(const Sk64& other) { this->add(other.fHi, other.fLo); }

    /** Subtract the specified Sk64 from the number. (*this) = (*this) - num
    */
    void    sub(const Sk64& num);

    /** Subtract the number from the specified Sk64. (*this) = num - (*this)
    */
    void    rsub(const Sk64& num);

    /** Multiply the number by the specified 32 bit integer
    */
    void    mul(int32_t);

    enum DivOptions {
        kTrunc_DivOption,   //!< truncate the result when calling div()
        kRound_DivOption    //!< round the result when calling div()
    };

    /** Divide the number by the specified 32 bit integer, using the specified
        divide option (either truncate or round).
    */
    void    div(int32_t, DivOptions);

    friend bool operator==(const Sk64& a, const Sk64& b) {
        return a.fHi == b.fHi && a.fLo == b.fLo;
    }

    friend bool operator!=(const Sk64& a, const Sk64& b) {
        return a.fHi != b.fHi || a.fLo != b.fLo;
    }

    friend bool operator<(const Sk64& a, const Sk64& b) {
        return a.fHi < b.fHi || (a.fHi == b.fHi && a.fLo < b.fLo);
    }

    friend bool operator<=(const Sk64& a, const Sk64& b) {
        return a.fHi < b.fHi || (a.fHi == b.fHi && a.fLo <= b.fLo);
    }

    friend bool operator>(const Sk64& a, const Sk64& b) {
        return a.fHi > b.fHi || (a.fHi == b.fHi && a.fLo > b.fLo);
    }

    friend bool operator>=(const Sk64& a, const Sk64& b) {
        return a.fHi > b.fHi || (a.fHi == b.fHi && a.fLo >= b.fLo);
    }

    // Private to unittests. Parameter is (skiatest::Reporter*)
    static void UnitTestWithReporter(void* skiatest_reporter);
};

#endif
