# Creating shared and static library

<ins>**Step 1**</ins>: Prepare folder tree following the below image

![alt text](assets_/folderTree.png)

<ins>**Step 2**</ins>: In folder Inc -> add header files. In folder Src -> add source files and file main

- You can see example in folder "Ex1" 

<ins>**Step 3**</ins>: Prepare and explain Makefile
- ***CUR_DIR***: The current directory (. refers to the directory where the Makefile is located).
- ***SRC_DIR***: Directory which contain the source code files.
- ***INC_DIR***: Directory which contain header files.
- ***BIN_SHARED_DIR***: Directory where the final executable using the shared library will be placed.
- ***BIN_STATIC_DIR***: Directory where the final executable using the static library will be placed.
- ***OBJ_DIR***: Directory for object files (intermediate files generated during compilation).
- ***OBJ_SHARED_DIR***: Directory for object files used to build the shared library.
- ***OBJ_STATIC_DIR***: Directory for object files used to build the static library.
- ***LIB_DIR***: Directory where the libraries (static and shared) will be stored.
- ***LIB_SHARED_DIR***: Directory for the shared library (libAddAnswerShared.so).
- ***LIB_STATIC_DIR***: Directory for the static library (libAddAnswerStatic.a).
- ***C_FLAGS***: Compiler flags. Here, **-I$(INC_DIR)** tells the compiler to look for header files in the **INC_DIR** directory.

- ***Target `create_dirs`***: Creates the required directory structure before compilation to prevent "No such file or directory" errors. This ensures all output folders exist before any build process starts.

- ***Target `create_objs`***: This target compiles the source files (add.c, ans.c, main.c) into object files (.o).
Shared Library Objects:  
    - **fPIC**: Generates position-independent code, which is required for shared libraries; object files are placed in **OBJ_SHARED_DIR**.  
    - Static Library Objects: Object files are placed in **OBJ_STATIC_DIR**.  
    - Main Program Object: The **main.c** file is compiled into an object file and placed in **OBJ_DIR**.  

- ***Target `create_shared_lib`***: This target creates a shared library (libAddAnswerShared.so) from the object files (add.o and ans.o).  
    - **shared**: Tells the compiler to create a shared library. The library is placed in **LIB_SHARED_DIR**. 

- ***Target `create_static_lib`***: This target creates a static library (libAddAnswerStatic.a) from the object files (add.o and ans.o).  
    - **ar rcs**: The ar command is used to create static libraries. rcs stands for:  
    - **r**: Replace existing files in the archive.  
    - **c**: Create the archive if it doesn’t exist.  
    - **s**: Write an index into the archive.  
=> The library is placed in LIB_STATIC_DIR.  
- ***Target `all`***: This is the default target (run when you type make). It depends on create_objs, create_shared_lib, and create_static_lib, so those targets are executed first.  

- ***Shared Library Linking***:  
    - Links main.o with the shared library (libAddAnswerShared.so).  
    - **L$(LIB_SHARED_DIR)**: Tells the linker where to find the shared library.  
    - **lAddAnswerShared**: Links the shared library (the lib prefix and .so suffix are omitted).  
=> The resulting executable is placed in BIN_SHARED_DIR.  

- ***Static Library Linking***:  
    - Links main.o with the static library (libAddAnswerStatic.a).  
    - **L$(LIB_STATIC_DIR)**: Tells the linker where to find the static library.  
    - **lAddAnswerStatic**: Links the static library (the lib prefix and .a suffix are omitted).  
=> The resulting executable is placed in BIN_STATIC_DIR.  

- ***Target `clean`***: This target cleans up the project by removing all generated files (object files, libraries, and executables) for a clean rebuild. This is helpful before rebuilding from scratch or committing to version control.

- ***Target run***: Two additional targets are provided to run the executables directlywithout manually setting the environment variables:
    - ***`run-shared`***: 
        - Builds everything (if not yet build) and run the executables that uses the shared library
        - Internally, it executes:
        ```bash
        LD_LIBRARY_PATH=$(LIB_SHARED_DIR):$LD_LIBRARY_PATH ./bin/shared/use-shared-library
        ```
        => This ensures the program can locate the shared library automatically without requiring manual export.
    - ***`run-static`***:
        - Builds and runs the executable linked with the static library.
        - Static binaries already contain all library code, so they do not require environment setup.

- ***Usage summary***:

    | Action                       | Command           |
    | ---------------------------- | ----------------- |
    | Build everything             | `make`            |
    | Clean all build outputs      | `make clean`      |
    | Run the program (shared lib) | `make run-shared` |
    | Run the program (static lib) | `make run-static` |
