SET(LIB_TYPE STATIC) #set the lib type

FIND_PACKAGE(ZLIB)

ADD_LIBRARY(vtk_utils ${LIB_TYPE} pvd_utils.c pvd_utils.h data_utils.c data_utils.h vtk_polydata_grid.c vtk_polydata_grid.h vtk_unstructured_grid.c vtk_unstructured_grid.h)

IF(ZLIB_FOUND)
    SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I \"${ZLIB_INCLUDE_DIRS}\" -DCOMPILE_ZLIB")
    TARGET_LINK_LIBRARIES(vtk_utils string ${ZLIB_LIBRARIES} yxml m )
ELSE()
    TARGET_LINK_LIBRARIES(vtk_utils string yxml m)
ENDIF(ZLIB_FOUND)

set_property(TARGET vtk_utils PROPERTY POSITION_INDEPENDENT_CODE ON)

#######################################################################

