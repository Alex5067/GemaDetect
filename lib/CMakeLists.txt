add_library(Neu STATIC Neu.h Neu.cpp)

execute_process (
    COMMAND bash -c "pip3 install numpy==1.26.4"
)

execute_process (
    COMMAND bash -c "pip3 install monai==1.3.2"
)

execute_process (
    COMMAND bash -c "pip3 install torch==2.3.0"
)