#include "Rational.hpp" 
#include<iostream> 
#include<vector>
#include<cassert>
#include <iomanip>
#include <sstream>
class Matrix{
public:
//constructor
    Matrix(std::size_t row=0,std::size_t column=0,Rational value=0);
    std::size_t row() const;
    std::size_t column() const;
//get matrix
    void getmatrix(std::size_t row,std::size_t column);
//access members
    Rational at(std::size_t i,std::size_t j) const;
    Rational &at(std::size_t i,std::size_t j);
    Rational operator()(std::size_t i,std::size_t j) const;
    Rational &operator()(std::size_t i,std::size_t j);
//operator overload
    friend std::ostream &operator<<(std::ostream &out, const Matrix &a);
    friend Matrix operator+(const Matrix &a,const Matrix &b);
    Matrix& operator+=(const Matrix &b);
    friend Matrix operator-(const Matrix &a);
    friend Matrix operator-(const Matrix &a,const Matrix &b);
    Matrix& operator-=(const Matrix &b);
    friend Matrix operator*(Rational s,const Matrix &a);
    friend Matrix operator*(const Matrix &a,Rational s);
    friend Matrix operator*(const Matrix &a,const Matrix &b);
//identity
    static Matrix identity(std::size_t n);
//power
    Matrix power(int a) const;
//transpose
    Matrix transpose() const;
//ERO
    Matrix& swap_two_lines(std::size_t s,std::size_t t);
    Matrix& multiply_one_line(Rational a,std::size_t s);
    Matrix& add_one_to_another(Rational a,std::size_t s,std::size_t t);
//REF
    Matrix& find_std_leading(std::size_t &s_r,std::size_t &s_c);
    Matrix& reduce_by_std_leading(std::size_t &s_r,std::size_t &s_c);
    Matrix& change_leading_to_one(std::size_t &s_r,std::size_t &s_c);
    Matrix& one_REF(std::size_t &s_r,std::size_t &s_c);
    Matrix& REF();
//RREF
    std::size_t find_the_leading_one_in_line_s(std::size_t s);
    Matrix& change_column_to_zero(std::size_t row_lead,std::size_t col_lead);
    Matrix& RREF();
//rank
    std::size_t rank();
//null & col
    Matrix null();
    bool  is_variable(std::size_t s);
    Matrix col();
//solve equation
    Matrix augmented(Matrix const &b) const;
    Matrix solve(Matrix b);
//ERO for det
    Matrix& swap_two_lines(std::size_t s,std::size_t t, Rational &det);
    Matrix& multiply_one_line(Rational a,std::size_t s, Rational &det);
    Matrix& add_one_to_another(Rational a,std::size_t s,std::size_t t, Rational &det);
//REF for deç
    Matrix& find_std_leading(std::size_t &s_r,std::size_t &s_c, Rational &det);
    Matrix& reduce_by_std_leading(std::size_t &s_r,std::size_t &s_c, Rational &det);
    Matrix& change_leading_to_one(std::size_t &s_r,std::size_t &s_c, Rational &det);
    Matrix& one_REF(std::size_t &s_r,std::size_t &s_c, Rational &det);
    Matrix& REF( Rational &det);
//det
    bool is_square() const;
    Rational det();
//reverse
    Matrix inverse() const;
//eigen
    Matrix eigenvalue();
    Matrix eigenvector();
private:
    std::size_t row_;
    std::size_t column_;
    std::vector <Rational> data;
};




int main(){
    Matrix a(3,4);
    a.getmatrix(3,4);  // 输入矩阵
    std::size_t s_r=0,s_c=0;
    std::cout << "after ref" <<std::endl;
    std::cout << a.REF() <<std::endl;

    std::cout << "after rref"<< std::endl;
    std::cout << a.RREF() << std::endl;
    std::cout <<"rank" << std::endl;
    std::cout << a.rank() << std::endl;
    std::cout << "null" << std::endl;
    std::cout << a.null();      
    std::cout << "col" << std::endl;
    std::cout << a.col();      
    return 0;
}



//constructor
Matrix::Matrix(std::size_t row,std::size_t column,Rational value)
: row_(row), column_(column), data(row * column, value) {}
std::size_t Matrix::row() const{
    return row_;
}
std::size_t Matrix::column() const{
    return column_;
}



//get matrix
void Matrix::getmatrix(std::size_t row,std::size_t column){
    row_=row;
    column_=column;
    data.resize(row_ * column_);
    for(std::size_t i=0;i<row_;i++){
        std::cout<< "enter row"<<i+1<<std::endl;
        for(std::size_t j=0;j<column_;j++){
            std::cin >> data[i*column_+j];
        }
    }
}



//access members
Rational Matrix::at(std::size_t i,std::size_t j) const{
    assert(i < row_ && j < column_);
    return data[i * column_ + j];
}
Rational &Matrix::at(std::size_t i,std::size_t j){
    assert(i < row_ && j < column_);
    return data[i * column_ + j];
}
Rational Matrix::operator()(std::size_t i,std::size_t j) const{
    assert(i < row_ && j < column_);
    return data[i * column_ + j];
}
Rational &Matrix::operator()(std::size_t i,std::size_t j){
    assert(i < row_ && j < column_);
    return data[i * column_ + j];
}
//operator overload
std::ostream &operator<<(std::ostream &out, const Matrix &a){
    std::vector<std::size_t> col_width(a.column(), 0);

    // 计算每列最大宽度
    for(std::size_t j = 0; j < a.column(); j++){
        for(std::size_t i = 0; i < a.row(); i++){
            std::ostringstream oss;
            oss << a(i,j);
            col_width[j] = std::max(col_width[j], oss.str().length());
        }
    }

    // 输出矩阵，每列固定宽度，左对齐
    for(std::size_t i = 0; i < a.row(); i++){
        for(std::size_t j = 0; j < a.column(); j++){
            std::ostringstream oss;
            oss << a(i,j);
            out << std::left << std::setw(col_width[j]) << oss.str();
            if (j != a.column() - 1) out << ' ';  // 列间空格
        }
        out << std::endl;
    }

    return out;
}
Matrix operator+(const Matrix &a,const Matrix &b){
    assert(a.column()==b.column() && a.row()==b.row());
    Matrix c{a.row(),a.column(),0};
    for(std::size_t i=0;i<a.row();i++){
        for(std::size_t j=0;j<a.column();j++){
            c.data[i*c.column()+j]=a.data[i*c.column()+j]+b.data[i*c.column()+j];
        }
    }
    return c;
}
Matrix& Matrix::operator+=(const Matrix& b){
    assert(row_ == b.row_ && column_ == b.column_);
    for (std::size_t i = 0; i < row_ * column_; ++i) {
        data[i] += b.data[i];
    }
    return *this;
}
Matrix operator-(const Matrix &a){
    Matrix c{a.row(),a.column(),0};
    for(std::size_t i=0;i<a.row();i++){
        for(std::size_t j=0;j<a.column();j++){
            c.data[i*a.column()+j]=-a.data[i*a.column()+j];
        }
    }
    return c;
}
Matrix operator-(const Matrix &a,const Matrix &b){
    return a+(-b);
}
Matrix& Matrix::operator-=(const Matrix &b){
    assert(row_ == b.row_ && column_ == b.column_);
    for (std::size_t i = 0; i < row_ * column_; ++i) {
        data[i] -= b.data[i];
    }
    return *this;
}
Matrix operator*(Rational s,const Matrix &a){
    Matrix c{a.row(),a.column(),0};
    for(std::size_t i=0;i<a.row();i++){
        for(std::size_t j=0;j<a.column();j++){
            c.data[i*a.column()+j]=s*a.data[i*a.column()+j];
        }
    }
    return c;
}
Matrix operator*(const Matrix &a,Rational s){
    return s*a;
}
Matrix operator*(const Matrix &a,const Matrix &b){
    assert(a.column()==b.row());
    Matrix c{a.row(),b.column(),0};
    for(std::size_t i=0;i<a.row();i++){
        for(std::size_t j=0;j<b.column();j++){
            for(std::size_t k=0;k<a.column();k++){
                c(i,j)+=a(i,k)*b(k,j);
            }
        }
    }
    return c;
}

//identity
Matrix Matrix::identity(std::size_t n){
    Matrix result(n, n, 0);
    for(std::size_t i = 0; i < n; i++) {
        result(i, i) = 1;
    }
    return result;
}

// power
Matrix Matrix::power(int a) const{
    assert(row_==column_ &&a>);
    Matrix temp=identity(row_);
    for(;a>0;a--){
        temp=(*this)*temp;
    }
    return temp;
}

// transpose
Matrix Matrix::transpose() const{
    Matrix temp{column_,row_};
    for(std::size_t i=0;i<row_;i++){
        for(std::size_t j=0;j<column_;j++){
            temp(j,i)=(*this)(i,j);
        }
    }
    return temp;
}


//ERO
Matrix& Matrix::swap_two_lines(std::size_t s, std::size_t t) {
    assert(s < row_ && t < row_);

    for (std::size_t i = 0; i < column_; ++i) {
        Rational temp = (*this)(s, i);
        (*this)(s, i) = (*this)(t, i);
        (*this)(t, i) = temp;
    }

    return *this;
}

Matrix &Matrix::multiply_one_line(Rational a, std::size_t s)
{
    for(std::size_t i=0;i<column_;i++){
        (*this)(s,i)=a*(*this)(s,i);
    }
    return *this;
}
Matrix& Matrix::add_one_to_another(Rational a,std::size_t s,std::size_t t){
    for (std::size_t i = 0; i < column_; ++i) {
    Rational temp = (*this)(s, i)*a;
    (*this)(t, i) += temp;
    }
    return *this;
}

// REF
Matrix& Matrix::find_std_leading(std::size_t &s_r,std::size_t &s_c){
    while (s_c < column_) {
        for(std::size_t i = s_r; i < row_; i++) { 
            if((*this)(i, s_c) != 0) {
                if(i != s_r) swap_two_lines(s_r, i);
                return *this;
            }
        }
        s_c++; 
    }
    return *this;
}

Matrix &Matrix::reduce_by_std_leading(std::size_t &s_r,std::size_t &s_c){
    if(s_c>=column_){
        return *this;
    }
    for(std::size_t i=s_r+1;i<row_;i++){
        Rational a=-(*this)(i,s_c)/(*this)(s_r,s_c);
        add_one_to_another(a,s_r,i);
    }
    return *this;
}

Matrix &Matrix::change_leading_to_one(std::size_t &s_r, std::size_t &s_c){
    if(s_c>=column_){
        return *this;
    }
    Rational a = 1 / (*this)(s_r, s_c);
    multiply_one_line(a, s_r);
    return *this;
}

Matrix &Matrix::one_REF(std::size_t &s_r,std::size_t &s_c){
    Matrix::find_std_leading(s_r,s_c);
    change_leading_to_one(s_r,s_c);
    reduce_by_std_leading(s_r,s_c);
    s_r++;
    s_c++;
    return *this;
}

Matrix& Matrix::REF(){
    std::size_t s_r=0;
    std::size_t s_c=0;
    while(s_r<row_ && s_c<column_){
        one_REF(s_r,s_c);
    }
    return *this;
}


//RREF
std::size_t Matrix::find_the_leading_one_in_line_s(std::size_t s){
    for(std::size_t j=0;j<column_;j++){
        if((*this)(s,j)==1){
            return j;
        }
    }
    return column_;
}

Matrix &Matrix::change_column_to_zero(std::size_t row_lead,std::size_t col_lead){
    if(col_lead>=column_){
        return *this;
    }
    for(std::size_t i=row_lead;i-- >0;){
        Rational temp=-(*this)(i,col_lead);
        add_one_to_another(temp,row_lead,i);
    }
    return *this;
}

Matrix &Matrix::RREF(){
    REF();
    for(std::size_t i=row_;i-->0;){
        std::size_t s=find_the_leading_one_in_line_s(i);
        if(s < column_)    {
            change_column_to_zero(i, s);
        }
    }
    return *this;
}


//rank
std::size_t Matrix::rank(){
    Matrix tmp = *this;
    tmp.REF();
    std::size_t sum=0;
    for(std::size_t i=0;i<tmp.row();i++){
        std::size_t s=tmp.find_the_leading_one_in_line_s(i);
        if(s!=tmp.column()){
            sum++;
        }
    }
    return sum;
}


//null & col
Matrix Matrix::null(){
    Matrix temp=(*this);
    temp.RREF();
    if(rank()==temp.column_){
        return Matrix{temp.column_,0,0};
    }
    std::size_t a=0;
    Matrix null{temp.column_,temp.column_-temp.rank(),0};
    for(std::size_t j=0;j<temp.column_;j++){
        if(temp.is_variable(j)){
            std::size_t k=0;
            for(std::size_t i=0;i<j;i++){
                if(!temp.is_variable(i)){
                    null(i,a)=-temp(k,j);
                    k++;
                }
            }
            null(j,a)=1;
            a++;
        }
    }
    return null;
}

bool Matrix::is_variable(std::size_t s){
    for(std::size_t i=0;i<row_;i++){
        if(find_the_leading_one_in_line_s(i)==s){
            return false;
        }
    }
    return true;
}

Matrix Matrix::col(){
    Matrix temp=(*this);
    temp.RREF();
    Matrix col{row_,temp.rank(),0};
    std::size_t a=0;
    for(std::size_t j=0;j<temp.column_;j++){
        if(!temp.is_variable(j)){
            for(std::size_t i=0;i<row_;i++){
                col(i,a)=(*this)(i,j);
            }
            a++;
        }
    }
    return col;
}


// solve solution
Matrix Matrix::augmented(Matrix const &b) const {
    assert(row_==b.row_ && b.column_==1);
    Matrix temp{row_,column_+1};
    for(std::size_t i=0;i<row_;i++){
        for(std::size_t j=0;j<column_+1;j++){
            if(j!=column_){
                temp(i,j)=(*this)(i,j);
            }else{
                temp(i,j)=b(i,0);
            }
        }
    }
    return temp;
}

Matrix Matrix::solve(Matrix b){
    assert(row_ == b.row_ && b.column_ == 1);
    Matrix temp=augmented(b);
    temp.RREF();
    if(rank()!=temp.rank()){
        return {0,0,0};
    }
    Matrix answer{column_,1,0};
    std::size_t k=0;
    for(std::size_t j=0;j<column_;j++){
        if(!temp.is_variable(j)){
            answer(j,0)=temp(k,temp.column_-1);
            k++;
        }
        
    }
    return answer;
}


//ERO for det
Matrix& Matrix::swap_two_lines(std::size_t s, std::size_t t, Rational &det) {
    swap_two_lines(s, t);  // 调用无det版本
    det*=-1;
    return *this;
}
Matrix& Matrix::multiply_one_line(Rational a,std::size_t s, Rational &det){
    multiply_one_line(a,s);
    det*=1/a;
    return *this;
}
Matrix& Matrix::add_one_to_another(Rational a,std::size_t s,std::size_t t, Rational &det){
    add_one_to_another(a,s,t);
    return *this;
}


// REF for det
Matrix& Matrix::find_std_leading(std::size_t &s_r,std::size_t &s_c, Rational &det){
    while (s_c < column_) {
        for(std::size_t i = s_r; i < row_; i++) { 
            if((*this)(i, s_c) != 0) {
                if(i != s_r) swap_two_lines(s_r, i, det);
                return *this;
            }
        }
        s_c++; 
    }
    return *this;
}

Matrix &Matrix::reduce_by_std_leading(std::size_t &s_r,std::size_t &s_c, Rational &det){
    if(s_c>=column_){
        return *this;
    }
    for(std::size_t i=s_r+1;i<row_;i++){
        Rational a=-(*this)(i,s_c)/(*this)(s_r,s_c);
        add_one_to_another(a,s_r,i, det);
    }
    return *this;
}

Matrix &Matrix::change_leading_to_one(std::size_t &s_r, std::size_t &s_c, Rational &det){
    if(s_c>=column_){
        return *this;
    }
    Rational a = 1 / (*this)(s_r, s_c);
    multiply_one_line(a, s_r, det);
    return *this;
}

Matrix &Matrix::one_REF(std::size_t &s_r,std::size_t &s_c, Rational &det){
    Matrix::find_std_leading(s_r,s_c, det);
    change_leading_to_one(s_r,s_c, det);
    reduce_by_std_leading(s_r,s_c, det);
    s_r++;
    s_c++;
    return *this;
}

Matrix& Matrix::REF( Rational &det){
    std::size_t s_r=0;
    std::size_t s_c=0;
    while(s_r<row_ && s_c<column_){
        one_REF(s_r,s_c, det);
    }
    return *this;
}



//det
bool Matrix::is_square() const{
    return column_==row_;
}

Rational Matrix::det(){
    assert(is_square());
    Rational det=1;
    Matrix temp=(*this);
    temp.REF(det);
    return det;
}


//reverse
Matrix Matrix::inverse() const{
    Matrix temp2=(*this);
    assert(is_square() && temp2.rank()==row_);
    Matrix temp{row_, 2*column_};
    for(std::size_t i=0;i<temp.row_;i++){
        for(std::size_t j=0;j<temp.column_;j++){
            if(j<column_){
                temp(i,j)=(*this)(i,j);
            }else if(i+column_==j){
                temp(i,j)=1;
            }
        }
    }
    temp.RREF();
    Matrix inverse{row_,column_};
    for(std::size_t i=0;i<row_;i++){
        for(std::size_t j=0;j<column_;j++){
            inverse(i,j)=temp(i,j+column_);
        }
    }
    return inverse;
} 

//


//1
//怎么用rational，要先g++ -std=c++11 matrix_class.cpp Rational.cpp -o matrix
//再用./matrix运行
//2
//如何对其输出，让每一列对其。 用 setw  ostringstream
//3
//还是从（0，0）开始
//4
//std::size_t 不能用i>=0做判断因为永远成立，应该用i-->0来判断
//如果用i--，i初始值就应该是row_lead了，这样不会跑头，也可以跑到0
//5
//行列经常弄反
//6
//面向对象编程，不能再void了
