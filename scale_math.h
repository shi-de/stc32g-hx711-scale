#ifndef SCALE_MATH_H
#define SCALE_MATH_H

long ScaleMath_Average(const long *samples, unsigned char count);
long ScaleMath_CalculateScale(long zero_raw, long load_raw, unsigned int known_grams);
long ScaleMath_WeightGrams(long raw, long zero_raw, long scale);
unsigned char ScaleMath_IsStable(long previous, long current, unsigned long threshold);
long ScaleMath_SignExtend24(unsigned long raw);

#endif
