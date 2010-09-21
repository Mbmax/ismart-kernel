
#ifndef splash_h
#define splash_h

extern void Splash_IRQVSYNC(void);
extern void Splash_Init(char *ani_path);
extern void Splash_Free(void);
extern bool Splash_Update(void);

#endif
