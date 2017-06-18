/* stdarg.h
 * from linux
 */
#ifndef __LIB_STDARG_H
#define __LIB_STDARG_H

typedef signed int     s32;

#ifndef va_arg
typedef char *va_list;
/*
 * Storage alignment properties
 */
#define  _AUPBND                (sizeof (s32) - 1)
#define  _ADNBND                (sizeof (s32) - 1)

/*
 * Variable argument list macro definitions
 */
#define _bnd(X, bnd)        (((sizeof (X)) + (bnd)) & (~(bnd)))

/* 把ap指向第一个可变参数A */
#define va_start(ap, A)     (void) ((ap) = (((char *) &(A))     \
                                    + (_bnd (A, _AUPBND))))
/* ap指向下一个参数并返回当前参数的值 */                                    
#define va_arg(ap, T)       (*(T *)(((ap) += (_bnd (T, _AUPBND))) \
                                    - (_bnd (T, _ADNBND))))
/* 清除ap */                                    
#define va_end(ap)          (void) 0

#endif	/* va_arg */
#endif  /* __LIB_STDARG_H */