sources=Utils.cpp GPUMacros.cpp Options.cpp LineReader.cpp SNPReader.cpp main.cpp

cuda_sources=

src_dir = .
objs_dir = objs

#EpistSearch
objs += $(patsubst %.cu, $(objs_dir)/%.cu.o, $(cuda_sources))
objs += $(patsubst %.cpp, $(objs_dir)/%.cpp.o, $(sources))

mylibs = -lpthread -lm -lz -lgomp
EXEC = SNPReader

#compile optionsK
CCFLAGS += -O3 -fopenmp
CC = g++

NVCCFLAGS += -O3 $(GPU_ARCH_FLAGS) -rdc true -Xcompiler -fopenmp 
NVCC = nvcc -gencode=arch=compute_20,code=sm_20 -gencode=arch=compute_30,code=sm_30 -gencode=arch=compute_35,code=sm_35

all: dir $(objs) $(objs_wrapper)
	$(NVCC) $(NVCCFLAGS) -o $(EXEC) $(objs) $(mylibs)
	strip $(EXEC)

dir:
	mkdir -p $(objs_dir)


clean:
	-rm -rf $(objs_dir) $(EXEC)

$(objs_dir)/%.cpp.o: $(src_dir)/%.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

$(objs_dir)/%.cu.o: $(src_dir)/%.cu
	$(NVCC) --ptxas-options=-v $(NVCCFLAGS) -o $@ -c $<

