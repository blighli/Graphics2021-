********
## 任务：复杂三维模型显示
#### 1、支持以下三维模型文件格式中至少1种：
##### OBJ、3DS、STL
#### 2、支持多个光源的光照效果，使用着色器渲染
#### 3、支持多种视点浏览方式
##### 以模型为中心的平移旋转和缩放
##### 以视点为中心的场景漫游
********
#### 使用框架/库 glfw-3.3.5、glew-2.2.0-win32、glad、glm-0.9.9、assimp-5.0.1（Open Asset Import Library，模型导入库）
###### 注：Assimp库需编译好的DLL文件（assimp-vc142-mtd.dll）拷贝到工程的相应目录下
#### 编译器vs2019，项目运行采用x64
##### 参考：https://learnopengl-cn.github.io/
********
### 使用说明：
#### 1.功能键“Esc”做窗口退出键。
#### 2.功能键“WASD”做窗口上下左右移动（即，物体、模型相反移动）键，W上、S下、A左、D右。
#### 3.功能键“JK”做窗口远近移动（即，物体缩放）键，J近（物体放大）、K远（物体缩小）。
#### 4.功能键“ZXCVB”做模型选择、切换键，Z-nanosuit.obj、X-rp_manuel_animated_001_dancing.fbx、C-Dragon_Baked_Actions_fbx_7.4_binary.fbx、V-Dragon 2.5_fbx.fbx、B-Dragon 2.5_stl.stl。
#### 5.功能键“01234”(横排数字键、小键盘数字键均可)做多光源照射模式选择、切换，0为默认多光源、1为DESERT多光源、2为FACTORY多光源、3为HORROR多光源、4为BIOCHEMICAL LAB多光源。
#### 6.鼠标移动做俯仰角(Pitch)和偏航角(Yaw)变换，即实现上下看、左右看。
#### 7.滚鼠标轮的功能同键“JK”，前滚J、后滚K。
********
### 光源附加图例（左图为默认多光源）：
<img src="./lighting_0.png" width="280"/> <img src="./multiple_lights_atmospheres.png" width="280"/><br/>
### 运行截图：
#### nanosuit.obj（由左至右分别对应默认、DESERT、FACTORY、HORROR、BIOCHEMICAL LAB多光源）
<img src="./运行截图/1.Z-nanosuit-0.png" width="190" height="145"/> <img src="./运行截图/1.Z-nanosuit-1.png" width="190" height="145"/> <img src="./运行截图/1.Z-nanosuit-2.png" width="190" height="145"/> <img src="./运行截图/1.Z-nanosuit-3.png" width="190" height="145"/> <img src="./运行截图/1.Z-nanosuit-4.png" width="190" height="145"/> <br/>
#### rp_manuel_animated_001_dancing.fbx
<img src="./运行截图/2.X-manuel-0.png" width="280"/> <img src="./运行截图/1.Z-nanosuit-1.png" width="280"/> <img src="./运行截图/1.Z-nanosuit-2.png" width="280"/> <img src="./运行截图/1.Z-nanosuit-3.png" width="280"/> <img src="./运行截图/1.Z-nanosuit-4.png" width="280"/> <br/>
#### Dragon_Baked_Actions_fbx_7.4_binary.fbx
#### Dragon 2.5_fbx.fbx
#### Dragon 2.5_stl.stl
<img src="./运行截图/4.png" width="280"/> <img src="./运行截图/5.png" width="280"/> <img src="./运行截图/6.png" width="280"/><br/>
********
### 实现说明：
#### 1.项目支持以下三维模型文件：obj、3DS、stl、fbx等，其中obj、stl、fbx有模型截图实例，3DS模型不完整、未截图（具体文件见./models）,文件调用代码如下：
``` c++
    // load models
    Model ourModel0("./models/nanosuit/nanosuit.obj");//ok，learnopengl-cn
    Model ourModel1("./models/Manuel_fbx/rp_manuel_animated_001_dancing.fbx");//人ok，sourceimages纹理
    Model ourModel2("./models/Dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx");//龙1ok
    Model ourModel3("./models/Dragon/Dragon 2.5_fbx.fbx");//龙2ok
    Model ourModel4("./models/Dragon/Dragon 2.5_stl.stl");//龙3ok
    //Model ourModel5("./models/SUV/1.obj");//SUV车，不完整
    //Model ourModel6("./models/SUV/1.3DS");//SUV车，不完整
    //Model ourModel("./models/bugatti/bugatti.obj");//车，没纹理
    //Model ourModel("./models/wolf/Wolf_obj.obj");//狼，没纹理
    //Model ourModel("./models/spot/spot_triangulated_good.obj");//牛，没纹理文件.mtl
```
#### 2、项目支持多个光源的光照效果，使用了着色器渲染。有5种多光源照射，具体见“光源附加图例”。
#### 3、项目支持多种视点浏览方式，包括以模型为中心的平移旋转和缩放、以视点为中心的场景漫游，具体操作见“使用说明”。
********
