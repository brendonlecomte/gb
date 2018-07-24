#ifndef OP_CODES_H
#define OP_CODES_H

extern void(*op_codes[256])(void);
extern void(*prefix_cb[256])(void);

#endif // OP_CODES_H
