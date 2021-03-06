/* stdio.h
 */

#ifndef __LIB_STDIO_H
#define __LIB_STDIO_H

#include <stdint.h>

uint32_t printf(const char *fmt, ...);
uint32_t sprintf(char *buf, const char *fmt, ...);

#endif  /* __LIB_STDIO_H */
