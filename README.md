C++ Base Project
---
Creates a C++ base project. Handles environment variable setting, unit testing, and debugging via lldb.

### DirEnv
Loads environment variables from .envrc in your shell.

#### Installation
Please view the following on how to install DirEnv. [https://github.com/direnv/direnv](https://github.com/direnv/direnv).

### Debugging
Two small bash scripts are included that pertain to debugging: `set_breakpoints` and `debug`. `set_breakpoints` will parse all of your C++ files for `//-BREAKPOINT-` comments. This automatically configures a script for LLDB to set a breakpoint in your application. To run your program with all your breakpoints set, run the `debug` command.

### Testing
Included is the Catch test framework. All tests belong in the `test/` directory. Running `make tests` will generate your test suite. 