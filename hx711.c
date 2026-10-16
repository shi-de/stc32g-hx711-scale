#include "STC32G.h"
#include "intrins.h"
#include "hx711.h"
#include "scale_math.h"

#define HX711_DT  P41
#define HX711_SCK P40
#define HX711_WAIT_TIMEOUT_MS 150U
#define HX711_MAX_SAMPLES 8

extern volatile unsigned int Time1ms;

void HX711_Init(void)
{
    P4M1 = (P4M1 & (unsigned char)~0x03) | 0x02;
    P4M0 = (P4M0 & (unsigned char)~0x03) | 0x01;
    HX711_DT = 1;
    HX711_SCK = 0;
}

unsigned char HX711_IsReady(void)
{
    return (HX711_DT == 0) ? 1 : 0;
}

unsigned char HX711_Read(long *value)
{
    unsigned int start_ms;
    unsigned char bit_count;
    unsigned long raw;

    if (value == 0)
    {
        return 0;
    }

    start_ms = Time1ms;
    while (HX711_DT != 0)
    {
        if ((unsigned int)(Time1ms - start_ms) >= HX711_WAIT_TIMEOUT_MS)
        {
            return 0;
        }
        _nop_();
    }

    raw = 0;
    for (bit_count = 0; bit_count < 24; bit_count++)
    {
        raw <<= 1;
        HX711_SCK = 1;
        _nop_();
        if (HX711_DT != 0)
        {
            raw |= 1UL;
        }
        HX711_SCK = 0;
        _nop_();
    }

    HX711_SCK = 1;
    _nop_();
    HX711_SCK = 0;
    _nop_();

    *value = ScaleMath_SignExtend24(raw);
    return 1;
}

long HX711_ReadAverage(unsigned char count, unsigned char *ok)
{
    unsigned char i;
    long samples[HX711_MAX_SAMPLES];

    if (ok == 0)
    {
        return 0;
    }
    *ok = 0;

    if (count == 0)
    {
        return 0;
    }
    if (count > HX711_MAX_SAMPLES)
    {
        count = HX711_MAX_SAMPLES;
    }

    for (i = 0; i < count; i++)
    {
        if (!HX711_Read(&samples[i]))
        {
            return 0;
        }
    }

    *ok = 1;
    return ScaleMath_Average(samples, count);
}
