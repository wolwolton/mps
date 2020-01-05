#include <iostream>
#include <vector>
#include <memory>
//#include "mps.h"
#include "particle.h"
#include "mk_particle.h"
#include "export.h"
#include <Eigen/Core>
class A{
public:
    bool flg;
    int value;
    A():flg(false), value(0){}
};

void tst(std::vector<std::unique_ptr<Particle>>& array){
    for(auto &a: array){
        std::cout<<a->vel.norm() << std::endl;
    }
}


int main(){
    std::cout<<"TST"<<std::endl;
    std::vector<std::unique_ptr<Particle>> pcls;
    MakeParticle mk_pcls;
    std::cout<<"TST"<<std::endl;
    mk_pcls.make_bar(pcls);
    std::cout<<"TST"<<std::endl;
    /*
    std::vector<std::unique_ptr<A>> A_array;
    std::unique_ptr<A> p1(new A);
    std::unique_ptr<A> p2(new A);
    std::unique_ptr<A> p3(new A);
    std::unique_ptr<A> p4(new A);
    p1->value = 1;
    p2->value = 2;
    p3->value = 3;
    p4->value = 4;
    A_array.push_back(std::move(p1));
    A_array.push_back(std::move(p2)); 
    A_array.push_back(std::move(p3)); 
    A_array.push_back(std::move(p4));  
    tst(A_array);
    */
    //tst(pcls);
    
    Export ex;
    ex.exportPara("tst1.vtu", pcls);
    /*
    Mps mps(pcls);
    std::cout<<"TST"<<std::endl;
    mps.setDt((double)1e-3);
    mps.setMaxTime((double)2);
    mps.setDx((double)0.025);
    mps.setDimension(2);
    mps.setName("./output3/tst1_");
    std::cout<<"TST"<<std::endl;
    ex.exportPara("tst2.vtu", pcls);
    std::cout<<"TST"<<std::endl;
    mps.run();
    */
    return 0;
}