cmake_minimum_required(VERSION 3.2.2)
project(darknet)

# to run this on Windows use this:
# cmake -G "Visual Studio 14 2015 Win64" -D GPU=1 ..

find_package(Threads REQUIRED)

IF(GPU)
  find_package(CUDA REQUIRED)
ENDIF()

IF(UNIX)
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-write-strings -Wall -Wfatal-errors ")
ELSE()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CONSOLE /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE ")
ENDIF()


if(OPENCV)
    # Be sure to set environment variable OpenCV_DIR pointing to your local opencv build
    find_package(OpenCV REQUIRED)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOPENCV ")       
    include_directories( ${OpenCV_INCLUDE_DIRS} )
ENDIF()

LIST(APPEND NVCC_OPTIONS "-gencode arch=compute_30,code=sm_30")
LIST(APPEND NVCC_OPTIONS "-gencode arch=compute_35,code=sm_35")
LIST(APPEND NVCC_OPTIONS "-gencode arch=compute_50,code=[sm_50,compute_50]")
LIST(APPEND NVCC_OPTIONS "-gencode arch=compute_52,code=[sm_52,compute_52]")
LIST(APPEND NVCC_OPTIONS "-DGPU")

###########
## Build ##
###########


## Declare the executable

LIST(APPEND DARKNET_SOURCES "gemm.cpp")
LIST(APPEND DARKNET_SOURCES "utils.cpp")
LIST(APPEND DARKNET_SOURCES "cuda.cpp")
LIST(APPEND DARKNET_SOURCES "deconvolutional_layer.cpp")
LIST(APPEND DARKNET_SOURCES "convolutional_layer.cpp")
LIST(APPEND DARKNET_SOURCES "list.cpp")
LIST(APPEND DARKNET_SOURCES "image.cpp")
LIST(APPEND DARKNET_SOURCES "activations.cpp")
LIST(APPEND DARKNET_SOURCES "im2col.cpp")
LIST(APPEND DARKNET_SOURCES "col2im.cpp")
LIST(APPEND DARKNET_SOURCES "blas.cpp")
LIST(APPEND DARKNET_SOURCES "crop_layer.cpp")
LIST(APPEND DARKNET_SOURCES "dropout_layer.cpp")
LIST(APPEND DARKNET_SOURCES "maxpool_layer.cpp")
LIST(APPEND DARKNET_SOURCES "softmax_layer.cpp")
LIST(APPEND DARKNET_SOURCES "data.cpp")
LIST(APPEND DARKNET_SOURCES "matrix.cpp")
LIST(APPEND DARKNET_SOURCES "network.cpp")
LIST(APPEND DARKNET_SOURCES "connected_layer.cpp")
LIST(APPEND DARKNET_SOURCES "cost_layer.cpp")
LIST(APPEND DARKNET_SOURCES "parser.cpp")
LIST(APPEND DARKNET_SOURCES "option_list.cpp")
LIST(APPEND DARKNET_SOURCES "darknet.cpp")
LIST(APPEND DARKNET_SOURCES "detection_layer.cpp")
LIST(APPEND DARKNET_SOURCES "captcha.cpp")
LIST(APPEND DARKNET_SOURCES "route_layer.cpp")
LIST(APPEND DARKNET_SOURCES "writing.cpp")
LIST(APPEND DARKNET_SOURCES "box.cpp")
LIST(APPEND DARKNET_SOURCES "nightmare.cpp")
LIST(APPEND DARKNET_SOURCES "normalization_layer.cpp")
LIST(APPEND DARKNET_SOURCES "avgpool_layer.cpp")
LIST(APPEND DARKNET_SOURCES "coco.cpp")
LIST(APPEND DARKNET_SOURCES "dice.cpp")
LIST(APPEND DARKNET_SOURCES "yolo.cpp")
LIST(APPEND DARKNET_SOURCES "detector.cpp")
LIST(APPEND DARKNET_SOURCES "layer.cpp")
LIST(APPEND DARKNET_SOURCES "compare.cpp")
LIST(APPEND DARKNET_SOURCES "regressor.cpp")
LIST(APPEND DARKNET_SOURCES "classifier.cpp")
LIST(APPEND DARKNET_SOURCES "local_layer.cpp")
LIST(APPEND DARKNET_SOURCES "swag.cpp")
LIST(APPEND DARKNET_SOURCES "shortcut_layer.cpp")
LIST(APPEND DARKNET_SOURCES "activation_layer.cpp")
LIST(APPEND DARKNET_SOURCES "rnn_layer.cpp")
LIST(APPEND DARKNET_SOURCES "gru_layer.cpp")
LIST(APPEND DARKNET_SOURCES "rnn.cpp")
LIST(APPEND DARKNET_SOURCES "rnn_vid.cpp")
LIST(APPEND DARKNET_SOURCES "crnn_layer.cpp")
LIST(APPEND DARKNET_SOURCES "demo.cpp")
LIST(APPEND DARKNET_SOURCES "tag.cpp")
LIST(APPEND DARKNET_SOURCES "cifar.cpp")
LIST(APPEND DARKNET_SOURCES "go.cpp")
LIST(APPEND DARKNET_SOURCES "batchnorm_layer.cpp")
LIST(APPEND DARKNET_SOURCES "art.cpp")
LIST(APPEND DARKNET_SOURCES "region_layer.cpp")
LIST(APPEND DARKNET_SOURCES "reorg_layer.cpp")
LIST(APPEND DARKNET_SOURCES "lsd.cpp")
LIST(APPEND DARKNET_SOURCES "super.cpp")
LIST(APPEND DARKNET_SOURCES "voxel.cpp")
LIST(APPEND DARKNET_SOURCES "tree.cpp")

IF(GPU)
IF (CUDA_FOUND)
	IF(UNIX)		
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGPU ")
	ELSE()
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	ENDIF()

	include_directories(
			${CUDA_INCLUDE_DIRS}
	)

	LIST(APPEND DARKNET_SOURCES "convolutional_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "deconvolutional_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "activation_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "im2col_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "col2im_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "blas_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "crop_layer_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "dropout_layer_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "maxpool_layer_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "network_kernels.cu")
	LIST(APPEND DARKNET_SOURCES "avgpool_layer_kernels.cu")

	set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} ${NVCC_OPTIONS}")
	
	message(STATUS "Creating CUDA darknet build, CUDA_NVCC_FLAGS=${CUDA_NVCC_FLAGS}")
	cuda_add_executable(darknet
		${DARKNET_SOURCES}
		)

ELSE()
	message(FATAL_ERROR "CUDA is not installed, so cannot build the GPU build")
ENDIF()
ELSE()
add_executable(darknet ${DARKNET_SOURCES})
ENDIF()
			
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${CXX_EXP_LIB})

if(OPENCV)
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
ENDIF()