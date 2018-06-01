%{
#include <complex>
%}

%include <gostring.swg>
%typemap(gotype) std::complex<float> "complex64"
%typemap(gotype) std::complex<double> "complex128"