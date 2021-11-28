//partners: ddamani2, ronitk2


#include "RealNumber.h"
#include "helper.h"
RealNumber::RealNumber()
{ //initializing to default
    number_type = 0;
    real_component = 0;
    magnitude = 0;
    phase = 0;
}
RealNumber::RealNumber(double rval)
{ //using the values given in parenthesis
    number_type = 0;
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval,0);
}
RealNumber::RealNumber( const RealNumber& other )
{ //copying from parenthesis to current
    number_type =0;
    real_component = other.get_real_component();
    magnitude = abs(other.get_magnitude());
    phase = other.get_phase();
}
void RealNumber::set_real_component (double rval)
{ //setting via copying from parenthesis value
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval,0);
}
//these return values needed:
double RealNumber::get_real_component() const
{
    return real_component;
}
double RealNumber::get_magnitude() const{
    return magnitude;
}
double RealNumber::get_phase() const{
    return phase;
}
RealNumber RealNumber::operator + (const RealNumber& arg)
{ //implementation of + overloading
    double sum = get_real_component() + arg.get_real_component();
    return RealNumber(sum);
}
RealNumber RealNumber::operator - (const RealNumber& arg)
{//implementation of - overloading
    double diff = get_real_component() - arg.get_real_component();
    return RealNumber(diff);
}
RealNumber RealNumber::operator * (const RealNumber& arg)
{ //implementation of * overloading
    double prod = get_real_component() * arg.get_real_component();
    return RealNumber(prod);
}
RealNumber RealNumber::operator / (const RealNumber& arg)
{ //implementation of / overloading
    double quot = get_real_component() / arg.get_real_component();
    return RealNumber(quot);
}
ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
//implementation of + overloading
    double resReal = get_real_component();
    double resImag = arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
//implementation of - overloading
    double resReal = get_real_component();
    double resImag = -1 * arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
//implementation of * overloading
    double resImag = get_real_component() * arg.get_imaginary_component();
    return ImaginaryNumber(resImag);
}
ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
//implementation of / overloading
    double a = get_real_component();
    double b = 0;
    double c = 0;
    double d = arg.get_imaginary_component();
    return ImaginaryNumber(((b*c)-(a*d))/((c*c)+(d*d)));
}
ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
//implementation of + overloading
    double resReal = get_real_component() + arg.get_real_component();
    double resImag = arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
//implementation of - overloading
    double resReal = get_real_component() - arg.get_real_component();
    double resImag = -1 * arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
//implementation of * overloading
    double resReal = get_real_component() * arg.get_real_component();
    double resImag = get_real_component() * arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
//implementation of / overloading
    double a = get_real_component();
    double b = 0;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((((a*c)+(b*d))/((c*c)+(d*d))),
                         (((b*c)-(a*d))/((c*c)+(d*d))));
}
string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
