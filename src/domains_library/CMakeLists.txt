SET(LIB_TYPE MODULE ../libraries_common/common_data_structures.h) #set the lib type

############## DEFAULT STIM LIBRARY 2006 ##############################
ADD_LIBRARY(default_domains ${LIB_TYPE} ${COMMON_SRC} domain.c domain_helpers.c domain_helpers.h)
TARGET_LINK_LIBRARIES(default_domains utils alg string config_helpers)
#########################################################

