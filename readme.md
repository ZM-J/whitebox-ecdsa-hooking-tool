# Static cryptanalysis tool for whitebox ECDSA

---

This repo contains a C source code which hooks the calls to GMP functions, and gives us opportunity to inspect the intermediate inputs/results of some whitebox ECDSA implementation.

This trick is described in Section 4.1 of the paper: [ECDSA White-Box Implementations: Attacks and Designs from WhibOx 2021 Contest](https://eprint.iacr.org/2022/385.pdf).

This repo only hooks the calls of `mpz_add`, `mpz_sub`, `mpz_mul`, `mpz_mod`, and `mpz_invert`. For more hooking, please follow the process provided in the C source code. Any pull requests is welcome.

To learn more about attacks on whitebox ECDSA, please refer:

*  [whitebox_ECDSA_attack_tool](https://github.com/Ledger-Donjon/whitebox_ECDSA_attack_tool) and its corresponding [blogpost](https://blog.ledger.com/whitebox_ecdsa/)
*  [WhibOx Contest](https://whibox.io/contests/2021/)
*  [ECDSA White-Box Implementations: Attacks and Designs from WhibOx 2021 Contest](https://eprint.iacr.org/2022/385.pdf)
*  [Attacks Against White-Box ECDSA and Discussion of Countermeasures - A Report on the WhibOx Contest 2021](https://eprint.iacr.org/2022/448.pdf)

## Usage

1. check the path of the GMP shared object using `ldd`, and fix `GMP_PATH` defined in `hook.c`.

```
$ ldd ./wb
./wb: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.34' not found (required by ./wb)
        linux-vdso.so.1 (0x00007ffed7268000)
        libgmp.so.10 => /lib/x86_64-linux-gnu/libgmp.so.10 (0x00007fe401dd2000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fe401be0000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fe401e6b000)
```

2. Compile the C code:

```
gcc -fPIC -shared hook.c -o hook.so
```

3. Apply `LD_PRELOAD` trick to the destination binary. Since this step will output all inputs and outputs of hooked computation, consider redirecting the output to a log file.

4. Analyze the log file.

In the example, we will see the multiplication of the elliptic curve generator is computed first to obtain `r`. Moreover, the `s` of the ECDSA signature is computed last using `s = k^-1 (z + r d)`.

Therefore, we can guess the value of `k` by inspecting the input of `mpz_invert`.

Note that other techniques might also be needed to attack whitebox ECDSA implementations, e.g., biased nonces, DCA, fault injections.