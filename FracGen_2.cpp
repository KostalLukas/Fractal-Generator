/*
 * Fractal Set Generator v2.0
 * Lukas Kostal, 20.7.2022, Bratislava
 */

#include <iostream>
#include <complex>
#include <cmath>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

complex<double> mandelbrot(complex<double> z_in, complex<double> c) {
    complex<double> z_out = z_in * z_in + c;
    return(z_out);
}

complex<double> burning_ship(complex<double> z_in, complex<double> c) {
    complex<double> z_intermediate = {abs(real(z_in)), abs(imag(z_in))};
    complex<double> z_out = pow(z_intermediate, 2) + c;
    return(z_out);
}

int main() {

    double x_cent = -0.8;
    double y_cent = -1;
    double x_range = 0.04;
    double y_range = 0.06;
    int res = 5000;

    //add center position and zoom in here

    string filename = "Sinking Ship_2.ppm";

    double x;
    double y;

    complex<double> c;
    complex<double> z;

    int iter;
    int iter_max = 100;

    double z_abs;
    double thresh = 5;

    int intensity;

    double progress;

    int i_max = res;
    int j_max = res;
    double x_inc = 2*x_range/res;
    double y_inc = 2*y_range/res;

    ofstream image;
    image.open(filename);

    image << "P3" << endl;
    image << i_max << " " << j_max << endl;
    image << "255" << endl;

    auto starttim = std::chrono::system_clock::now();

    for (int j=0; j < j_max; j++) {
        for (int i=0; i < i_max; i++) {
            x = x_cent - x_range + i*x_inc;
            y = y_cent - y_range + j*y_inc;

            c = {x, y};
            z = 0;

            iter = 0;
            z_abs = 0;
            while (iter < iter_max && z_abs <= thresh) {
                z = burning_ship(z, c);
                z_abs = abs(z);
                iter ++;
            }

            intensity = floor((float)iter/(float)iter_max * 255);
            image << intensity << " " << intensity << " " << intensity << " " << endl;

        }
        if (remainder(j, res/100) == 0) {
            progress = ((float)j)/((float)j_max)*100;

            cout << "  " << progress << " % \t [";

            for (int k = 1; k <= 50; k++) {
                if (k <= ceil(progress/2)) {
                    cout << "#";
                }
                else {
                    cout << " ";
                }

            }

            cout << "] \r" << std::flush;
        }
    }

    image.close();

    auto endtim = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = endtim - starttim;

    cout << endl;
    cout << endl;
    cout << "Finished generating " << filename << endl;
    cout << "Region: x = (" << x_cent - x_range << ", " << x_cent + x_range << ") y = (" << y_cent - y_range << ", " << y_cent + y_range << ")" << endl;
    cout << "Resolution   = " << res << "x" << res << endl;
    cout << "Threshold    = " << thresh << endl;
    cout << "Iterations   = " << iter_max << endl;
    cout << "Time taken   = " << elapsed.count() << "s" << endl;

    return 0;
}


