#include "scale_math.h"

long ScaleMath_Average(const long *samples, unsigned char count)
{
    unsigned char i;
    long sum;
    long minimum;
    long maximum;

    if (count == 0 || samples == 0)
    {
        return 0;
    }

    sum = 0;
    minimum = samples[0];
    maximum = samples[0];
    for (i = 0; i < count; i++)
    {
        sum += samples[i];
        if (samples[i] < minimum)
        {
            minimum = samples[i];
        }
        if (samples[i] > maximum)
        {
            maximum = samples[i];
        }
    }

    if (count >= 3)
    {
        sum -= minimum;
        sum -= maximum;
        return sum / (long)(count - 2);
    }

    return sum / (long)count;
}

long ScaleMath_CalculateScale(long zero_raw, long load_raw, unsigned int known_grams)
{
    long delta;

    if (known_grams == 0)
    {
        return 0;
    }

    delta = load_raw - zero_raw;
    if (delta == 0)
    {
        return 0;
    }

    return delta / (long)known_grams;
}

long ScaleMath_WeightGrams(long raw, long zero_raw, long scale)
{
    if (scale == 0)
    {
        return 0;
    }

    return (raw - zero_raw) / scale;
}

unsigned char ScaleMath_IsStable(long previous, long current, unsigned long threshold)
{
    long delta;

    delta = current - previous;
    if (delta < 0)
    {
        delta = -delta;
    }

    return ((unsigned long)delta <= threshold) ? 1 : 0;
}

long ScaleMath_SignExtend24(unsigned long raw)
{
    raw &= 0x00ffffffUL;
    if ((raw & 0x00800000UL) != 0)
    {
        raw |= 0xff000000UL;
    }
    return (long)raw;
}
