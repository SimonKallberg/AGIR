#ifndef matrix_hpp
#define matrix_hpp

#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::endl;

template <typename T>
struct matrix_element {
    using type = T;
};

template<class T>
class matrix
{
    //declare a vector of vectors of type T
    vector<vector<T> > s ;
public:
    //Initialize the size of s to ROWS by COLS
    matrix(int inR, int inC)
        : s(inR, vector<T>(inC)), ROWS(inR), COLS(inC) {}
    
    //Initialize the size of s to 4 x 4 with 4 vectors
    matrix(Vector3 col1, Vector3 col2, Vector3 col3, Vector3 col4 = Vector3(0,0,0))
        : s(4, vector<T>(4)), ROWS(4), COLS(4)
    {
        matrix<T>& theMatrix = *this;
        theMatrix(0,0) = col1.x;
        theMatrix(1,0) = col1.y;
        theMatrix(2,0) = col1.z;
        
        theMatrix(0,1) = col2.x;
        theMatrix(1,1) = col2.y;
        theMatrix(2,1) = col2.z;
        
        theMatrix(0,2) = col3.x;
        theMatrix(1,2) = col3.y;
        theMatrix(2,2) = col3.z;
        
        theMatrix(0,3) = col4.x;
        theMatrix(1,3) = col4.y;
        theMatrix(2,3) = col4.z;
        
        theMatrix(3,3) = 1;
        
    }
    
    //Initialize the size of s to 4 x 1 with 1 vectors
    matrix(Vector3 col)
        : s(4, vector<T>(4)), ROWS(4), COLS(1)
    {
        matrix<T>& theMatrix = *this;
        
        theMatrix(0,0) = col.x;
        theMatrix(1,0) = col.y;
        theMatrix(2,0) = col.z;
        theMatrix(3,0) = 1;
        
    }
    
    typename matrix_element<T>::type& operator() (int row, int col);
    void readm();
    void printm();
    int ROWS = 800;
    int COLS = 800;
    void multiply(matrix<T>& B, matrix<T>& C);
    Vector3 multiply(Vector3 inDir);
};

template<typename T>
inline void matrix<T>::multiply(matrix<T>& lhs, matrix<T>& rhs) {

    matrix<T>& result = *this;
    
    if(lhs.COLS != rhs.ROWS) {
        std::cout << "Matrix dimensions do not match!" << std::endl;
        return;
    }
    //Matrix multiplication
    for(int i = 0; i < result.ROWS; i++) {
        for(int j = 0; j < result.COLS; j++) {
            for(int k = 0; k < lhs.COLS; k++) {
                //cout << lhs(i,k) << endl;
                auto lhsElem = lhs(i, k);
                auto rhsElem = rhs(k, j);
                result(i, j) += lhsElem * rhsElem;
            }
        }
    }
}

template<typename T>
inline Vector3 matrix<T>::multiply(Vector3 inDir) {

    matrix<T>& lhs = *this;
    matrix<T> rhs(inDir);
    matrix<T> result(Vector3(0,0,0));
    
    if(lhs.COLS != rhs.ROWS) {
        std::cout << "Matrix dimensions do not match!" << std::endl;
        return Vector3(0,0,0);
    }
    //Matrix multiplication
    for(int i = 0; i < result.ROWS; i++) {
        for(int j = 0; j < result.COLS; j++) {
            for(int k = 0; k < lhs.COLS; k++) {
                //cout << lhs(i,k) << endl;
                auto lhsElem = lhs(i, k);
                auto rhsElem = rhs(k, j);
                result(i, j) += lhsElem * rhsElem;
            }
        }
    }
    
    return Vector3(result(0,0), result(1,0), result(2,0));
}

template<class T>
typename matrix_element<T>::type& matrix<T>::operator() (int row, int col) {
    return s.at(row).at(col);
}

template<class T>
void matrix<T>::readm()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            cin >> this->s[i][j];
}
template<class T>
void matrix<T>::printm()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            cout << this->s.at(i).at(j) <<"\t";
        cout << endl;
    }
}


#endif
