#include <iostream>
#include <fstream>
#include "particle.h"
#include "export.h"

int Export::exportPara(const std::string name, const std::vector<Particle> &pcls){
    std::ofstream ofs(name);
    if (!ofs)
    {
        ofs.close();
        return -1;
    }
    int pcls_count = pcls.size();
    ofs << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
    ofs << "<VTKFile xmlns='VTK' byte_order='LittleEndian' version='0.1' type='UnstructuredGrid'>" << std::endl;
    ofs << "<UnstructuredGrid>" << std::endl;
    ofs << "<Piece NumberOfCells='"<< pcls_count << "' NumberOfPoints='" << pcls_count << "'>"<<  std::endl;
    ofs << "<Points>" << std::endl;
    ofs << "<DataArray NumberOfComponents='3' type='Float32' Name='Position' format='ascii'>" << std::endl;

    for(auto pcl : pcls){
        ofs << pcl.pos.x() << " " << pcl.pos.y() << " " << pcl.pos.z() << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "</Points>" << std::endl;
    ofs << "<PointData>" << std::endl;
    ofs << "<DataArray NumberOfComponents='1' type='Int32' Name='ParticleType' format='ascii'>" << std::endl;
    for(auto pcl : pcls){
        ofs << pcl.typ << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "<DataArray NumberOfComponents='1' type='Float32' Name='Velocity' format='ascii'>" << std::endl;
    for(auto pcl  : pcls){
        ofs << (float)pcl.vel.norm() << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "<DataArray NumberOfComponents='1' type='Float32' Name='pressure' format='ascii'>" << std::endl;
    for(auto pcl  : pcls){
        ofs << (float)pcl.prr << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "</PointData>" << std::endl;
    ofs << "<Cells>" << std::endl;
    ofs << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << std::endl;
    for(int i=0;i<pcls_count; i++){
        ofs << i << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "<DataArray type='Int32' Name='offsets' format='ascii'>" << std::endl;
    for(int i=0;i<pcls_count; i++){
        ofs << i+1 << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "<DataArray type='UInt8' Name='types' format='ascii'>" << std::endl;
    for(int i=0;i<pcls_count; i++){
        ofs << 1 << std::endl;
    }
    ofs << "</DataArray>" << std::endl;
    ofs << "</Cells>" << std::endl;
    ofs << "</Piece>" << std::endl;
    ofs << "</UnstructuredGrid>" << std::endl;
    ofs << "</VTKFile>" << std::endl; 
    ofs.close();
    return 0;
}

int Export::exportPara(const std::string name,int i, const std::vector<Particle> &pcls){
    std::string fname = name+std::to_string(i)+".vtu";
    std::cout<<fname<<std::endl;
    return exportPara(fname,pcls);
}