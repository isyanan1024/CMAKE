# 为什么需要Cmake？

makefile在不同的系统下有不同的写法，因此需要Cmake根据不同的系统自动编写makefile文件

# Demo1

## 单目录单文件

main.cpp

```C++
#include <iostream>
using namespace std;

double power(double base,double exponent)
{	
	int res=base;
	if(base==1)
	{
	return 1;
	}
	for(int i=1;i<exponent;i++)
	{
		res=res*base;
	}
	return res;
}

int main(int argc,char *argv[])
{
	if(argc<3)
	{
		cout<<"Usage:"<<argv[0]<<endl;
		return 1;
	}
	double base =atof(argv[1]);
	int exponent=atoi(argv[2]);
	cout<<"result"<<endl<<power(base,exponent);
	return 0;
}
```

**注意**：argc是命令行总的参数个数，argv[]是argc个参数，其中第0个参数是程序的全名，以后的参数
命令行后面跟的用户输入的参数

CMakeLists.txt

```cmake
#声明cmake版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

#使用C++11的特性
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#项目名
PROJECT(demo1)

#生成可执行文件，第一个参数是可执行文件的名字，第二个参数是依赖项
ADD_EXECUTABLE(demo1  main.cpp)
```

# Demo2

## 单目录多文件

main.cpp

```C++
#include <iostream>
#include "mymath.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Usage:" << argv[0] << endl;
		return 1;
	}

	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	cout << "result = " << power(base, exponent) << endl;
}
```

mymath.hpp

```C++
#ifndef MYMATH_H
#define MYMATH_H

double power(double, double);

#endif
```

mymath.cpp

```C++
#include "mymath.hpp"

double power(double base, double exponent)
{
	int res = base;
	if(base == 1){
		return 1;
	}
	for(int i = 1; i < exponent; i++)
	{
		res *= base;
	}
	return res;
}
```

CMakeLists.txt

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(demo2)

ADD_EXECUTABLE(demo2 main.cpp mymath.cpp)
```

**注意**：可以将多个cpp文件加到一个列表中，写法如下

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(demo2)

#发现一个目录下所有源代码文件并存储在一个变量中
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

ADD_EXECUTABLE(demo2 ${DIR_SRCS})
```

# Demo3

## 多目录多文件

|-- CMakeLists.txt
|-- demo.cpp
|-- demo3
 -- mylib
    |-- CMakeLists.txt
    |-- mymath.cpp
    |- mymath.hpp

main.cpp

```c++
#include <iostream>
#include "mymath.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Usage:" << argv[0] << endl;
		return 1;
	}

	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	cout << "result = " << power(base, exponent) << endl;
}
```

CMakeLists.txt

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(demo3)

#向当前工程添加存放源文件的子目录
ADD_SUBDIRECTORY(./mylib)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

ADD_EXECUTABLE(demo3 ${DIR_SRCS})

#为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(demo3 Mylib)
```

mylib/mymath.cpp

```C++
#include "mymath.hpp"

double power(double base, double exponent)
{	
	int res = base;
	for(int i = 1; i < exponent; i++)
	{
		res *= base;
	}
	return res;
}
```

mylib/mymath.hpp

```C++
#ifndef MYMATH_H
#define MYMATH_H

double power(double, double);

#endif
```

mylib/CMakeLists.txt

```cmake
aux_source_directory(. DIR_LIB_SRCS)

#生成动态库或静态库
add_library(Mylib STATIC ${DIR_LIB_SRCS})
```

**注意**：STATTIC表示静态库(以后不更新了)，SHARED表示动态库(以后还要更新)

# Demo4

## 多目录文件标准工程

.
|-- CMakeLists.txt
|-- build
|-- mylib
|   |-- CMakeLists.txt
|   |-- mymath.cpp
|   `-- mymath.hpp
`

|-- src
    |-- CMakeLists.txt
    `-- demo.cpp

CMakeLists.txt

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

PROJECT(demo4)

ADD_SUBDIRECTORY(./mylib)

ADD_SUBDIRECTORY(./src) 
```

mylib/CMakeLists.txt

```cmake
AUX_SOURCE_DIRECTORY(./ DIR_LIB_SRCS)

#设置库存放的位置，PROJECT_BINARY_DIR表示build的位置，就是cmake执行的位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_LIBRARY(Mylib STATIC ${DIR_LIB_SRCS})
```

mylib/mymath.cpp

```C++
#include "mymath.hpp"

double power(double base, double exponent)
{
	int res = base;
	for(int i = 1; i < exponent; i++)
	{
		res *= base;
	}

	return res;
}
```

mylib/mymath.hpp

```C++
#ifndef MYMATH_H
#define MYMATH_H

double power(double, double);

#endif
```

src/CMakeLists.txt

```cmake
#向工程添加多个特定的头文件搜索路径，PROJECT_SOURCE_DIR表示根目录路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR/mylib})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#设置可执行文件的位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

AUX_SOURCE_DIRECTORY(./ DIR_SRCS)

ADD_EXECUTABLE(demo4 ${DIR_SRCS})

TARGET_LINK_LIBRARIES(demo4 Mylib)
```

src/demo.cpp

```C++
/*
* @Author: Yan An
* @Date:   2020-07-21 14:12:59
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 15:22:24
*/
#include <iostream>
#include "../mylib/mymath.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	cout << "result = " << power(base, exponent) << endl;
}
```

```shell
cd build

cmake ..
make

./bin/demo4 2 3
```

# Demo5

## 自定义编译选项

在src中的CMakeLists.txt文件添加

```cmake
#ADD_DEFINITIONS(-DUSE_MYMATH)
```

修改src/demo.cpp中的内容为

```C++
#include <iostream>
#ifdef USE_MYMATH
	#include "../mylib/mymath.hpp"
#else
	#include <math.h>
#endif
using namespace std;

int main(int argc, char *argv[])
{
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	#ifdef USE_MYMATH
		cout << "MYMATH" << endl;
		cout << "result = " << power(base, exponent) << endl;
	#else
		cout << "OTHERMATH" << endl;
		cout << "result = " << pow(base, exponent) << endl;

	#endif
}
```

```
mkdir build 

cd build
cmake ..
make
./bin/demo5 2 3
```

