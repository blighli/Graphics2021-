## 任务：复杂三维模型显示

#### 1、支持以下三维模型文件格式中至少1种：

##### OBJ、3DS、STL

#### 2、支持多个光源的光照效果，使用着色器渲染

#### 3、支持多种视点浏览方式

##### 以模型为中心的平移旋转和缩放

##### 以视点为中心的场景漫游



## dependence

- glfw 3.3
- glad
- assimp 5.0
- DirectX SDK jun 10
- glm 0.9



## Outputs

![](D:\1-研究生课程\三维动画\git\graphics2021\22151081何辰纲\作业3\outputs1.png)

采用了四处点光源，中心处另叠加了一层聚光光源。

模型`nanosuit.obj` 来自于 `http://tf3dm.com/3d-model/crysis-2-nanosuit-2-97837.html`

## Controls

鼠标操控视角，W/A/S/D操作视角的移动

鼠标滚轮操作放大缩小。