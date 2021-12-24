## 任务：
### 使用glfw和glew搭建OpenGL基本框架
#### 也可以使用glut或者Qt等其他框架
### 实现基本模型绘制
#### 绘制立方体、圆球或者茶壶
### 实现相机控制
#### 支持从不同视角和距离观察模型
********
#### 使用框架/库 glfw-3.3.5、glew-2.2.0-win32、glad、glm-0.9.9
#### 编译器vs2019，项目运行采用x64
##### 参考：https://learnopengl-cn.github.io/
********
### 使用说明：
#### 1.功能键“Esc”做窗口退出键。
#### 2.功能键“WASD”做窗口上下左右移动（即，物体相反移动）键，W上、S下、A左、D右
#### 3.功能键“JK”做窗口远近移动（即，物体缩放）键，J近（物体放大）、K远（物体缩小）
#### 4.功能键“C”做切换键（即，画立方体block与画球体block切换），默认先画立方体
#### 5.功能键“↑↓”做纹理变换键，默认采用纹理1：wall.jpg(下左)、纹理2：awesomeface.png(下右)，“↑”凸显纹理2、隐藏纹理1，“↓”凸显纹理1、隐藏纹理2
#### <img src="wall.jpg" width="200"/><img src="awesomeface.png" width="200"/><br/>
#### 6.鼠标移动做俯仰角(Pitch)和偏航角(Yaw)变换，即实现上下看、左右看
#### 7.滚鼠标轮的功能同键“JK”，前滚J、后滚K
********
### 运行截图：
<img src="./运行截图/block.png" width="180"/>    <img src="./运行截图/block-j.png" width="180"/>
<img src="./运行截图/block-mouse-keyboard.png" width="180"/>    <img src="./运行截图/block-mouse-keyboard2.png" width="180"/><br/>
<img src="./运行截图/sphere.png" width="180"/>    <img src="./运行截图/sphere-mouse-wasd.png" width="180"/>    <img src="./运行截图/sphere-mouse-wasd2.png" width="180"/>
<img src="./运行截图/sphere-mouse-keyboard.png" width="180"/>    <img src="./运行截图/sphere-mouse-keyboard2.png" width="180"/><br/>
#### 注：如图，在实现过程中默认给绘制模型加了颜色渲染，绘制立方体、球体均为10个，其中4个自旋转
