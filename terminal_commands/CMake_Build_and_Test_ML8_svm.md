# Build and Test ML8_svm with CMake

Run these commands from the project root, where `CMakeLists.txt` is located:

```powershell
cmake -S . -B cmake-build-vs -G "Visual Studio 18 2026" -A x64 -DBUILD_TESTING=ON -DML8_SVM_BUILD_EXAMPLES=ON
cmake --build cmake-build-vs --config Debug --parallel 1
ctest --test-dir cmake-build-vs -C Debug --output-on-failure
```
