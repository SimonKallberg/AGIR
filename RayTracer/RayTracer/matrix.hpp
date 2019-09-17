#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::vector;
using std::endl;
const int ROWS = 800;
const int COLS = 800;

template <typename T>
struct matrix_element {
    using type = T;
};

template<class T>
class matrix
{
    //declare a vector of vectors of type T
    vector<vector<T>> s ;
public:
    //Initialize the size of s to ROWS by COLS
    matrix(): s(ROWS, vector<T>(COLS)) {}
    
    typename matrix_element<T>::type operator() (int row, int col);
    void readm();
    void printm();

};
template<class T>
typename matrix_element<T>::type matrix<T>::operator() (int row, int col) {
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
            cout << this->s.at(i).at(j).color.r <<"\t";
        cout << endl;
    }
}
