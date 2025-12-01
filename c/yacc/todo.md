# TODO

- [ ] Switch to `fread()` and `fwrite()` without breaking case `stdin`.
- [ ] Implement CL options.
    - [ ] <code>-n, --number</code> Print line numbers starting at 1 for every
    output line.
    - [ ] <code>-b, --number-nonblank</code> Only print line numbers for lines
    containing text. (Exclude empty lines.) (Overwrites `-n`.)
    - [ ] <code>-E, --show-ends</code> Display a `$` character at the end of
    every line.
- [ ] Update [README](./README.md) and the `help` option after every feature
implemented.
