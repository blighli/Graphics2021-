#### 实验环境

* 使用IDEvs2019，并配合C++的包管理工具vckpg

* glfw3.3.5+glew2.2.0+glm0.9.9.8+SOIL+Assimp

#### 文件说明

* model_loading.frag 为模型的片段着色器脚本
* model_loading.vs为模型的顶点着色器脚本
* Homework3.cpp为主程序，Shader.h、Camera.h、Mesh.h、Model.h为封装好的着色器类
* 模型在nanosuit文件夹中

#### 功能

* 以模型为中心的平移旋转和缩放：按住鼠标右键上下左右移动，可以转动模型，滚动鼠标可以控制模型的缩放。
* 以视点为中心的场景漫游：按住Shift，鼠标上下左右移动可改变视角，WASD可以控制观察点。

#### 运行

可以自己编译运行，也可以使用编译好的可执行文件Homework3.exe，在文件夹Release中

##### 注意

* 如果自己编译运行，需要将model_loading.frag 、model_loading.vs 、模型所在文件夹nanosuit放在Homework3.cpp所在目录下；
* 如果运行可执行文件Homework3.exe，需要将model_loading.frag 、model_loading.vs 、模型所在文件夹nanosuit放在Homework3.exe所在目录。

