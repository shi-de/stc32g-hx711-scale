#ifndef HX711_H
#define HX711_H

void HX711_Init(void);
unsigned char HX711_IsReady(void);
unsigned char HX711_Read(long *value);
long HX711_ReadAverage(unsigned char count, unsigned char *ok);

#endif
