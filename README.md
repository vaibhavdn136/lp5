# lp5


### For running openmp programs run commands:- 


Compile: `g++ path/to/file/file_name.cpp -fopenmp`

Execute: `./a.out` [Linux] or `./a.exe` [Windows]
 
 

### Steps to run CUDA programs on Google Collab:
1. [Go to Google Collab](https://colab.research.google.com)
2. Create a new Notebook(.ipynb file).
3. Click on Runtime and change runtime type to GPU.
4. Now run `!pip install git+https://github.com/afnan47/cuda.git` in a cell.
5. On a new cell run `%load_ext nvcc_plugin`
6. Test the following code
```
%%cu
#include <iostream>
int main(){
  std::cout << "Hello World\n";
  return 0;
}
```

7. Remember to add `%%cu` before writing the C++ code for every CUDA program. CUDA is now set.
