/* See LICENSE file for copyright and license details. */

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

void die(const char *errstr, ...);
void *ecalloc(size_t, size_t);

#ifdef NO_STRL
size_t strlcpy(char *dst, const char *src, size_t size);
#endif
