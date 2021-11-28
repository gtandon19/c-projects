//partners: ddamani2, ronitk2
//similar to RealNumber.cpp
#include "ImaginaryNumber.h"
#include "helper.h"
ImaginaryNumber::ImaginaryNumber()
{
    number_type = 1;
    imaginary_component = 0;
    magnitude = 0;
    phase = 0;
}
ImaginaryNumber::ImaginaryNumber(double rval)
{
    number_type = 1;
    imaginary_component = rval;
    magnitude = rval;
    phase = calculate_phase(0,rval);
}
ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    number_type = other.get_number_type();
    imaginary_component = other.get_imaginary_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}
void ImaginaryNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    magnitude = rval;
    phase = calculate_phase(0,rval);
}
double ImaginaryNumber::get_imaginary_component() const
{
    return imaginary_component;
}
//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    return magnitude;
}
//Getter function for phase
double ImaginaryNumber::get_phase() const{
    return phase;
}
//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    double sum = get_imaginary_component() + arg.get_imaginary_component();
    return ImaginaryNumber(sum);
}
ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    double diff = get_imaginary_component() - arg.get_imaginary_component();
    return ImaginaryNumber(diff);
}
RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    double a = 0;
    double b = get_imaginary_component();
    double c = 0;
    double d = arg.get_imaginary_component();
    return RealNumber((a*c)-(b*d));
}
RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    double a = 0;
    double b = get_imaginary_component();
    double c = 0;
    double d = arg.get_imaginary_component();
    return RealNumber(((a*c)+(b*d))/((c*c)+(d*d)));
}
ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    double resReal = arg.get_real_component();
    double resImag = get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    double resReal = -1 * arg.get_real_component();
    double resImag = get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    double a = 0;
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = 0;
    return ImaginaryNumber((a*d)+(b*c));
}
ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    double a = 0;
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = 0;
    return ImaginaryNumber(((b*c)-(a*d))/((c*c)+(d*d)));
}
ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    double resReal = arg.get_real_component();
    double resImag = get_imaginary_component() + arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    double resReal = -1 * arg.get_real_component();
    double resImag = get_imaginary_component() - arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    double resReal = -1 * get_imaginary_component() * arg.get_imaginary_component();
    double resImag = get_imaginary_component() * arg.get_real_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    double a = 0;
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((((a*c)+(b*d))/((c*c)+(d*d))),
                         (((b*c)-(a*d))/((c*c)+(d*d))));
}
string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}
