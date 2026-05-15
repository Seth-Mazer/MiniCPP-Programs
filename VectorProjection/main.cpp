#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>

//inner product function
std::pair<double,double> innerproducts(const std::vector<double> &u, const std::vector<double> &v){
    double ip1 = 0, ip2 = 0;
    //computing inner product, ui * vi
    for (int i = 0; i < std::size(u); i++){
        ip1 += u[i] * v[i];
        ip2 += v[i] * v[i];
    }

    return {ip1,ip2};
};

//main function
int main() {

    //initializing vectors
    std::vector<double> u, v;
    double temp;

    //asking user to manually input each vector entry.. u1,u2,u3 etc.
    std::cout<<"Input each component of u (enter letter when done) \n";
    while (std::cin >> temp){
        u.push_back(temp);
    };
    //clearing the input from the loop break
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout<<"Input each component of v (enter letter when done) \n";
    while (std::cin >> temp){
        v.push_back(temp);
    };
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    //vector math:
    //check dims are valid, if so pass vectors to inner product func, to returns inner products,
    //then compute (uTv/vTv)u / c*u
    if(size(u) == size(v)){

        //creating uTv and vTv, passing to ip func, then unpacking returned computations to uTv and vTv
        double uTv, vTv;
        std::tie(uTv,vTv) = innerproducts(u,v);
        double c = (uTv/vTv);
        //std::vector<double> projUV;
        std::cout << "Projection of U onto V is: \n";
        for (int i = 0; i < std::size(v); i++) {
            std::cout << std::setprecision(15) << c*v[i] << "\n";
        }


    } else {
        std::cout << "ip not valid: dim mismatch";
    }

    return 0;
}
