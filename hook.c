/*
 * COMPILE:
 * gcc -fPIC -shared hook.c -o hook.so
 */

#include <gmp.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#define GMP_PATH "/lib/x86_64-linux-gnu/libgmp.so.10"

// mpz_add
typedef void (*MPZ_ADD_FUNC)(mpz_ptr, mpz_srcptr, mpz_srcptr);

void mpz_add (mpz_ptr w, mpz_srcptr u, mpz_srcptr v) {
    void* handler = NULL;
    char* error = NULL;
    MPZ_ADD_FUNC real_mpz_add = NULL;
    handler = dlopen(GMP_PATH, RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "err:%s\n", dlerror());
        exit(1);
    }
    dlerror();
    //此处取对应函数地址,
    *(void **) (&real_mpz_add) = dlsym(handler, "__gmpz_add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "err:%s", error);
        exit(1);
    }
    gmp_printf("[mpz_add] u + v = w\n");
    gmp_printf("u = %Zd\n", u);
    gmp_printf("v = %Zd\n", v);
    real_mpz_add(w, u, v);
    gmp_printf("w = %Zd\n", w);
    gmp_printf("\n");
    dlclose(handler);
}

// mpz_sub
typedef void (*MPZ_SUB_FUNC)(mpz_ptr, mpz_srcptr, mpz_srcptr);

void mpz_sub (mpz_ptr w, mpz_srcptr u, mpz_srcptr v) {
    void* handler = NULL;
    char* error = NULL;
    MPZ_SUB_FUNC real_mpz_sub = NULL;
    handler = dlopen(GMP_PATH, RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "err:%s\n", dlerror());
        exit(1);
    }
    dlerror();
    //此处取对应函数地址,
    *(void **) (&real_mpz_sub) = dlsym(handler, "__gmpz_sub");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "err:%s", error);
        exit(1);
    }
    gmp_printf("[mpz_sub] u - v = w\n");
    gmp_printf("u = %Zd\n", u);
    gmp_printf("v = %Zd\n", v);
    real_mpz_sub(w, u, v);
    gmp_printf("w = %Zd\n", w);
    gmp_printf("\n");
    dlclose(handler);
}


// mpz_mul
typedef void (*MPZ_MUL_FUNC)(mpz_ptr, mpz_srcptr, mpz_srcptr);

void mpz_mul (mpz_ptr w, mpz_srcptr u, mpz_srcptr v) {
    void* handler = NULL;
    char* error = NULL;
    MPZ_MUL_FUNC real_mpz_mul = NULL;
    handler = dlopen(GMP_PATH, RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "err:%s\n", dlerror());
        exit(1);
    }
    dlerror();
    //此处取对应函数地址,
    *(void **) (&real_mpz_mul) = dlsym(handler, "__gmpz_mul");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "err:%s", error);
        exit(1);
    }
    gmp_printf("[mpz_mul] u * v = w\n");
    gmp_printf("u = %Zd\n", u);
    gmp_printf("v = %Zd\n", v);
    real_mpz_mul(w, u, v);
    gmp_printf("w = %Zd\n", w);
    gmp_printf("\n");
    dlclose(handler);
}


// mpz_mod
typedef void (*MPZ_MOD_FUNC)(mpz_ptr, mpz_srcptr, mpz_srcptr);

void mpz_mod (mpz_ptr w, mpz_srcptr u, mpz_srcptr v) {
    void* handler = NULL;
    char* error = NULL;
    MPZ_MOD_FUNC real_mpz_mod = NULL;
    handler = dlopen(GMP_PATH, RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "err:%s\n", dlerror());
        exit(1);
    }
    dlerror();
    //此处取对应函数地址,
    *(void **) (&real_mpz_mod) = dlsym(handler, "__gmpz_mod");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "err:%s", error);
        exit(1);
    }
    gmp_printf("[mpz_mod] u mod v = w\n");
    gmp_printf("u = %Zd\n", u);
    gmp_printf("v = %Zd\n", v);
    real_mpz_mod(w, u, v);
    gmp_printf("w = %Zd\n", w);
    gmp_printf("\n");
    dlclose(handler);
}


// mpz_invert
typedef int (*MPZ_INVERT_FUNC)(mpz_ptr, mpz_srcptr, mpz_srcptr);

int mpz_invert (mpz_ptr w, mpz_srcptr u, mpz_srcptr v) {
    void* handler = NULL;
    char* error = NULL;
    MPZ_INVERT_FUNC real_mpz_invert = NULL;
    int func_result;
    handler = dlopen(GMP_PATH, RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "err:%s\n", dlerror());
        exit(1);
    }
    dlerror();
    //此处取对应函数地址,
    *(void **) (&real_mpz_invert) = dlsym(handler, "__gmpz_invert");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "err:%s", error);
        exit(1);
    }
    gmp_printf("[mpz_invert] w = u^-1 mod v\n");
    gmp_printf("u = %Zd\n", u);
    gmp_printf("v = %Zd\n", v);
    func_result = real_mpz_invert(w, u, v);
    gmp_printf("w = %Zd\n", w);
    gmp_printf("\n");
    dlclose(handler);
    return func_result;
}