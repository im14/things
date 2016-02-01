/* small wrapper to enable extglobs in find
 * needs glibc
 * gcc -shared -fPIC extglob.c -o extglob.so -ldl
 * LD_PRELOAD=$PWD/extglob.so find . -name '!(*.c|*.so)'
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <fnmatch.h>

int (*orig)(const char *p, const char *s, int f);

__attribute__((constructor)) void foo() {
  orig = dlsym(RTLD_NEXT, "fnmatch");
}

int fnmatch(const char *pattern, const char *string, int flags) {
  return orig(pattern, string, flags|FNM_EXTMATCH);
}
