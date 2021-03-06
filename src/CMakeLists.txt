find_package(Boost REQUIRED COMPONENTS system filesystem serialization)
find_package(CGAL REQUIRED COMPONENTS Core)
find_package(PCL 1.7 REQUIRED COMPONENTS common io)

rock_library(maps
    SOURCES
        grid/ElevationMap.cpp
        grid/TraversabilityMap3d.cpp
        grid/OccupancyGridMap.cpp
        grid/TSDFVolumetricMap.cpp
        tools/BresenhamLine.cpp
        tools/VoxelTraversal.cpp
        tools/TSDFPolygonMeshReconstruction.cpp
        tools/TSDF_MLSMapReconstruction.cpp
    HEADERS
        LocalMap.hpp
        grid/Index.hpp
        grid/GridMap.hpp
        grid/LevelList.hpp        
        grid/LayeredGridMap.hpp
        grid/MultiLevelGridMap.hpp        
        grid/ElevationMap.hpp
        grid/SurfacePatches.hpp
        grid/MLSConfig.hpp
        grid/MLSMap.hpp
        grid/TraversabilityMap3d.hpp
        grid/AccessIterator.hpp
        grid/GridAccessInterface.hpp
        grid/GridFacade.hpp        
        grid/VectorGrid.hpp        
        grid/VectorGridAccess.hpp
        grid/DiscreteTree.hpp
        grid/VoxelGridMap.hpp
        grid/OccupancyGridMapBase.hpp
        grid/OccupancyGridMap.hpp
        grid/OccupancyConfiguration.hpp
        grid/TSDFVolumetricMap.hpp
        geometric/Point.hpp
        geometric/LineSegment.hpp
        geometric/GeometricMap.hpp
        geometric/ContourMap.hpp
        tools/BresenhamLine.hpp
        tools/Overlap.hpp
        tools/VoxelTraversal.hpp
        tools/TSDFSurfaceReconstruction.hpp
        tools/TSDFPolygonMeshReconstruction.hpp
        tools/TSDF_MLSMapReconstruction.hpp
        tools/MarchingCubes.hpp
        tools/SurfaceIntersection.hpp
        operations/GridInterpolation.hpp
    DEPS_PKGCONFIG 
        base-types 
        base-logging
        pcl_common-${PCL_VERSION_MAJOR}.${PCL_VERSION_MINOR}
        pcl_io-${PCL_VERSION_MAJOR}.${PCL_VERSION_MINOR}
    DEPS_PLAIN
        Boost_SYSTEM 
        Boost_FILESYSTEM 
        Boost_SERIALIZATION
        CGAL
)
