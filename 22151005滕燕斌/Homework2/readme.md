#### 实验环境

* 使用IDEvs2019，并配合C++的包管理工具vckpg

* glfw3.3.5+glew2.2.0+glm0.9.9.8+SOIL

#### 文件说明

* ShaderHomework2_Obj.frag 为地球片段着色器脚本
* ShaderHomework2_Obj.vs 为地球顶点着色器脚本
* ShaderHomework2_Lighting.frag 为地球片段着色器脚本
* ShaderHomework2_Lighting.vs 为地球顶点着色器脚本
* earth.jpg 与 sun.jpg 为需要使用的纹理图片
* Homework2.cpp为主程序，Shader.h为封装好的着色器类

#### 功能

* 按下鼠标右边并拖动，可完成观察视角的变换
* 按键W、A、S、D可以完成观察点的移动
* 按键上下左右，可实现物体的旋转

#### 运行

可以自己编译运行，也可以使用编译好的可执行文件Homework2.exe，在文件夹Release中

##### 注意

* 如果自己编译运行，需要将ShaderHomework2_Obj.frag 、ShaderHomework2_Obj.vs 、ShaderHomework2_Lighting.frag、ShaderHomework2_Lighting.vs、earth.jpg 与sun.jpg放在Homework2.cpp所在目录下；
* 如果运行可执行文件Homework2.exe，需要将ShaderHomework2_Obj.frag 、ShaderHomework2_Obj.vs 、ShaderHomework2_Lighting.frag、ShaderHomework2_Lighting.vs、earth.jpg 与sun.jpg放在Homework2.exe所在目录。

