SET(LIB_TYPE MODULE) #set the lib type
if(CUDA_FOUND)
    CUDA_ADD_LIBRARY(default_update_monodomain ${LIB_TYPE}  update_monodomain.c)
    set(CUDA_LIBRARIES PUBLIC ${CUDA_LIBRARIES})
    TARGET_LINK_LIBRARIES(default_update_monodomain PUBLIC alg)
ELSE()
    ADD_LIBRARY(default_update_monodomain ${LIB_TYPE} update_monodomain.c)
    TARGET_LINK_LIBRARIES(default_update_monodomain alg)
ENDIF(CUDA_FOUND)


#########################################################

