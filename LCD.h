#include"types.h"
void Init_Lcd(void);
void WriteLcd(U8 byte);
void CmdLcd(U8 cmd);
void CharLcd(U8 asciival);
void StrLcd(S8 *);
void u32Lcd(U32);
void s32Lcd(S32);
void f32Lcd(F32,U32);
void BuildCGRAM(U8 *,U8);
