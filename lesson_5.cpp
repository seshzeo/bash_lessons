#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void multiply_row_by_column(const vector<vector<int> >& A, const vector<vector<int> >& B, vector<vector<int> >& C, int row, int column) {
    int sum = 0;
    for (int i = 0; i < A[0].size(); i++) {
        sum += A[row][i] * B[i][column];
    }
    C[row][column] = sum;
}

vector<vector<int> > matrix_multiplication_threaded(const vector<vector<int> >& A, const vector<vector<int> >& B) {
    if (A[0].size() != B.size()) {
        throw invalid_argument("The number of columns must be equal to the number of rows");
    }

    int n = A.size();
    int m = B[0].size();
    vector<vector<int> > result(n, vector<int>(m, 0));

    vector<thread> threads;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            threads.push_back(thread(multiply_row_by_column, cref(A), cref(B), ref(result), i, j));
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    return result;
}

int main() {
    vector<vector<int> > A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int> > B = {{5, 6}, {7, 8}, {9, 10}};
    try {
        vector<vector<int> > C = matrix_multiplication_threaded(A, B);
        for (const auto& row : C) {
            for (const auto& element : row) {
                cout << element << ' ';
            }
            cout << endl;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
