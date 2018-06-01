%{
#include <vector>
%}

%include "std_vector.i"

%template(VecFloat) std::vector<float>;
%template(VecDouble) std::vector<double>;