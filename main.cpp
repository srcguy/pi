#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

long double pi, k, m = 0.0, a, b;

string alg;

int main()
{
    omp_set_num_threads(3); //number of threads

    #pragma omp parallel
    {
    #pragma omp single
        cout << "omp_get_num_threads: " << omp_get_num_threads() << endl;
        cout << "thread ID: " << omp_get_thread_num() << endl;
        cout << "omp_get_max_threads: " << omp_get_max_threads() << endl;
    }

    cout << "Chudnovsky?" << endl;
    cin >> alg;
    if (alg == "Y" or alg == "y") {
        cout << "Enter k:";
        cin >> k;
        for (int n = 0; n < k; n++) {
            a = pow(-1.0, n) * tgamma((6 * n) + 1) * (13591409 + 545140134 * n);
            b = tgamma((3 * n) + 1) * pow(tgamma(n + 1), 3.0) * pow(640320.0, (3 * n) + 1.5);
            m = m + a / b;
        }
        m = m * 12;
        pi = 1 / m;
        cout.precision(50);
        cout << pi << endl;
        cout << "3,141592653589793238462643383279502884197169399375105" << endl;
    }
    else {
        cout << "k = 100 000 000" << endl;
        #pragma omp parallel for reduction(+:m)
        for (int n = 0; n < 100000000; n++) { //if number of iterations is variable - error C3017
            m += pow(-1.0, n) / (2.0 * n + 1.0);
        }
        pi = m * 4;
        cout.precision(50);
        cout << pi << endl;
        cout << "3,141592653589793238462643383279502884197169399375105" << endl;
    }
    return 0;
}
