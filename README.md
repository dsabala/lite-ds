# Lightweight Data Structures for Embedded Systems

**Lite-DS** is a lightweight library of data structures specifically designed for bare-metal embedded systems.

## Modules

- [cirbuf](lite-ds/cirbuf/README.md): Circular buffer implementation.
- [msg-queue](lite-ds/cirbuf/README.md): FIFO message queue.
- [mem-pool](lite-ds/mem-pool/README.md): Memory pool for efficient memory management.

## Advantages and Limitations

### Advantages
- **Dependency-free**: Relies only on the C standard library, with no external dependencies
- **Permissive license**: Can be freely used in proprietary software
- **Simple interface**: Inspired by the design principles of large, well-known libraries
- **Easy CMake integration**: Straightforward setup (see the CMake section below)
- **Unit test coverage**: Provides a higher level of trustworthiness

### Limitations
- **Not thread-safe**: Users must ensure thread safety in multi-threaded environments
- **Not a replacement for RTOS primitives**: In RTOS environments, it is often better to use the primitives provided by the RTOS
- **Uses dynamic memory allocation**: Dynamic memory is employed to achieve better encapsulation and a consistent interface
- **Uses assertions**: Assertions are used to improve safety without the cognitive overhead of explicitly handling trivial errors like null pointers

Additional design decisions are documented in the README files for each module.

## Quick Build

### **1. Configure CMake**
```sh
cmake -B build -D LITEDS_BUILD_TESTS=1
```

### **2. Build and test the Library**
```sh
cd build
make all test
```

## CMake Integration

1. Add this project to your codebase, either as a submodule or by copying it directly into your project
2. Include it in your build system using ```add_subdirectory(lite-ds)```
3. Link the library to your target with ```target_link_libraries(your-artifact PRIVATE lite-ds)```

## Epilogue

When I was applying for a Software Engineer position,
I found it somewhat annoying that companies expected a deep understanding of data structures and algorithms.
However, when I needed implementations of a few simple algorithms tailored to my use case,
I ended up creating this small library.
Writing these data structures wasn’t about innovation but about necessity - building the foundation for the domain logic of the applications I work on.
In the process, I gained a deeper understanding of how these data structures function, and now I see why such knowledge is a justified requirement.
