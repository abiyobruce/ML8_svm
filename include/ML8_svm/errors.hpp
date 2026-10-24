// errors.hpp: the exceptions thrown by the library.
// Owner: Travor (M6)
//
// Public functions check their input and throw one of these exceptions
// instead of returning a wrong result.
//
//   std::runtime_error
//        |
//     SvmError                  base class: catch it to catch any library error
//        |-- InvalidArgument    a value is not allowed (negative lambda, empty
//        |                      dataset, only one class, ...)
//        |-- DimensionMismatch  sizes do not match (dot product of a 3-vector
//        |                      and a 4-vector, X and y of different length, ...)
//        |-- FileError          a file cannot be opened or read
//        `-- NotFitted          a model or scaler is used before fit()
//
// Usage:
//   throw ml8_svm::InvalidArgument("lambda must be >= 0");
//
//   try { model.predict(x); }
//   catch (const ml8_svm::NotFitted& e) { /* fit() was not called */ }
//   catch (const ml8_svm::SvmError& e)  { /* any other library error */ }
//
// Header-only: each class only inherits the constructors of its base class.
#pragma once

#include <stdexcept>
#include <string>

namespace ml8_svm {

// Base class of every exception thrown by this library.
// The using-declaration reuses the constructors of std::runtime_error, so
// SvmError("message") works directly.
struct SvmError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

// A function received a value that is not allowed.
struct InvalidArgument : SvmError {
    using SvmError::SvmError;
};

// Two objects that must have matching sizes do not.
struct DimensionMismatch : SvmError {
    using SvmError::SvmError;
};

// A file could not be found, opened or read.
struct FileError : SvmError {
    using SvmError::SvmError;
};

// A model or scaler was used before fit() was called.
struct NotFitted : SvmError {
    using SvmError::SvmError;
};

}  // namespace ml8_svm
