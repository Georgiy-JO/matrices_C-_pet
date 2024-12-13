#ifndef MATRIX_EXCEPTIONS
#define MATRIX_EXCEPTIONS


class MatrixError : public std::exception{
    std::string msg;
    public:
        MatrixError(const char* error="Unknown error!"): msg(error){}
        MatrixError(const MatrixError& other): msg(other.msg){}
        const char* what() const noexcept override {return msg.c_str();}
};
class DimentionError:public MatrixError{
    public:
    DimentionError(const char* error="Matrix sizes error: matrix dimentions should be positive."): MatrixError(error){}
};
class DataError:public MatrixError{
    public:
    DataError(const char* error="Incorrect data: imposible to input / calculate due to data error (inf, nan, etc)."): MatrixError(error){}
};
class DimentionEqualityError:public MatrixError{
    public:
    DimentionEqualityError(const char* error="Calculation impossible: matrices' dimentions are not equal."): MatrixError(error){}
};
class DimentionAlignmentError:public MatrixError{
    public:
    DimentionAlignmentError(const char* error="Calculation impossible: the number of columns of the first matrix does not equal the number of rows of the second matrix."): MatrixError(error){}
};
class MemoryAllocationError:public MatrixError{
    public:
    MemoryAllocationError(const char* error="Memory alocation problem: congratulations, you got it somehow!"): MatrixError(error){}
};
class OutOfRangeError:public MatrixError{
    public:
    OutOfRangeError(const char* error="Out of range error: you are trying to reach element out of matrix."): MatrixError(error){}
};
class MatrixSetError:public MatrixError{
    public:
    MatrixSetError(const char* error="Matrix not set or does not exist."): MatrixError(error){}
};
class SquarenessError:public MatrixError{
    public:
    SquarenessError(const char* error="The matrix is not square"): MatrixError(error){}
};
class NonInvertibleError:public MatrixError{
    public:
    NonInvertibleError(const char* error="The matrix is not invertable:the determinant is zero."): MatrixError(error){}
};
class InputError:public MatrixError{
    public:
    InputError(const char* error="Input parameter or data error."): MatrixError(error){}
};

#endif // MATRIX_EXCEPTIONS