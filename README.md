Work-in-progress (dynamic!) allocation-free matrix implementation.

Requires C++23

`Matrix` is for when the dimensions are known at compile time, and stores it's data inline with `std::array`.

DynamicMatrix stores all of its data inline with zero allocations, but it doesn't work with `new` currenty due to C++ language limitations (currently looking for a workaround)

It achives this by using `alloca` in a `__forceinline` method to allocate in the caller's stack frame, and the copy constructor copies the data around with the same trick. MSVC ignores `__forceinline` in Debug, so you need to use Release otherwise it will be memory bugs. Pretty ironic for a keyword with "force" in the name