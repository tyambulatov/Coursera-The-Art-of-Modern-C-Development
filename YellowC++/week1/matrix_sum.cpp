#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix
{
public:
    Matrix()
    {
        rows = 0;
        cols = 0;
    }
    Matrix(int num_rows, int num_cols)
    {
        Reset(num_rows, num_cols);
    }
    void Reset(int new_rows, int new_cols)
    {
        //обнуление всех элементов
        if (new_rows < 0 || new_cols < 0)
        {
            throw out_of_range("");
        }

        if (new_rows == 0 || new_cols == 0)
        {
            new_rows = new_cols = 0;
        }

        rows = new_rows;
        cols = new_cols;
        grid.assign(new_rows, vector<int>(new_cols));
    }
    int At(int nRows, int nCols) const
    {
        return grid.at(nRows).at(nCols);
    }

    int &At(int nRows, int nCols)
    {
        return grid.at(nRows).at(nCols);
    }

    int GetNumRows() const
    {
        return rows;
    }
    int GetNumColumns() const
    {
        return cols;
    }

private:
    vector<vector<int>> grid;
    int rows;
    int cols;
};

bool RowsColumnsCompare(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.GetNumRows() == rhs.GetNumRows() & lhs.GetNumColumns() == rhs.GetNumColumns())
    {
        return true;
    }
    return false;
}

// * оператор ввода для класса Matrix из потока istream
istream &operator>>(istream &stream, Matrix &newMatrix)
{
    int n, m;
    stream >> n >> m;

    newMatrix = Matrix(n, m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            stream >> newMatrix.At(i, j);
        }
    }
    return stream;
}

// * оператор вывода класса Matrix в поток ostream
ostream &operator<<(ostream &stream, const Matrix &matrix)
{
    stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
    for (int i = 0; i < matrix.GetNumRows(); ++i)
    {
        for (int j = 0; j < matrix.GetNumColumns(); ++j)
        {
            if (j > 0)
            {
                stream << ' ';
            }
            stream << matrix.At(i, j);
        }
        stream << endl;
    }
    return stream;
}

// * оператор проверки на равенство двух объектов класса Matrix
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
    if (RowsColumnsCompare(lhs, rhs))
    {
        for (int i = 0; i < lhs.GetNumRows(); ++i)
        {
            for (int j = 0; j < lhs.GetNumColumns(); ++j)
            {
                if (rhs.At(i, j) != lhs.At(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
// * оператор сложения двух объектов класса Matrix
Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    if (!RowsColumnsCompare(lhs, rhs))
    {
        throw invalid_argument("");
    }

    Matrix tmpMatrix(lhs.GetNumRows(), rhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); ++i)
    {
        for (int j = 0; j < lhs.GetNumColumns(); ++j)
        {
            tmpMatrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return tmpMatrix;
}

int main()
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
