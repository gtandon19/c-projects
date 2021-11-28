//partners:ronitk2, ddamani2

//using same pattern as real numbers

#include "ComplexNumber.h"
#include "helper.h"
ComplexNumber::ComplexNumber()
{
    number_type = 2;
    real_component = 0;
    imaginary_component = 0;
    magnitude = 0;
    phase = 0;
}
ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    number_type = 2;
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    magnitude = sqrt((rval_real_component*rval_real_component) +
      (rval_imaginary_component*rval_imaginary_component));
    phase = calculate_phase(rval_real_component,rval_imaginary_component);
}
ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    number_type = other.get_number_type();
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
}
void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
    magnitude = sqrt((rval*rval) +
      (get_imaginary_component()*get_imaginary_component()));
    phase = calculate_phase(rval,get_imaginary_component());
}
double ComplexNumber::get_real_component() const
{
    return real_component;
}
void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    magnitude = sqrt((rval*rval) +
      (get_real_component()*get_real_component()));
    phase = calculate_phase(get_real_component(),rval);
}
double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}
double ComplexNumber::get_magnitude() const{
    return magnitude;
}
double ComplexNumber::get_phase() const{
    return phase;
}
ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    double resReal = get_real_component() + arg.get_real_component();
    double resImag = get_imaginary_component() + arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    double resReal = get_real_component() - arg.get_real_component();
    double resImag = get_imaginary_component() - arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(((a*c)-(b*d)),((a*d)+(b*c)));
}
ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((((a*c)+(b*d))/((c*c)+(d*d))),
                         (((b*c)-(a*d))/((c*c)+(d*d))));
}
ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    double resReal = get_real_component() + arg.get_real_component();
    double resImag = get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    double resReal = get_real_component() - arg.get_real_component();
    double resImag = get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = 0;
    return ComplexNumber(((a*c)-(b*d)),((a*d)+(b*c)));
}
ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = arg.get_real_component();
    double d = 0;
    return ComplexNumber((((a*c)+(b*d))/((c*c)+(d*d))),
                         (((b*c)-(a*d))/((c*c)+(d*d))));
}
ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    double resReal = get_real_component();
    double resImag = get_imaginary_component() + arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    double resReal = get_real_component();
    double resImag = get_imaginary_component() - arg.get_imaginary_component();
    return ComplexNumber(resReal,resImag);
}
ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = 0;
    double d = arg.get_imaginary_component();
    return ComplexNumber(((a*c)-(b*d)),((a*d)+(b*c)));
}
ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    double a = get_real_component();
    double b = get_imaginary_component();
    double c = 0;
    double d = arg.get_imaginary_component();
    return ComplexNumber((((a*c)+(b*d))/((c*c)+(d*d))),
                         (((b*c)-(a*d))/((c*c)+(d*d))));
}
string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
   
    return my_output.str();
}
