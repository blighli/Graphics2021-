#### models下应有如图所示文件：
<img src="./models文件.png" width="600"/> <br/>
##### 由于文件大小原因，部分未成功上传，文件具体说明如下：
##### 大多模型下载自网站：https://free3d.com
##### 具体模型文件及网址说明如下：
##### 1.bugatti文件夹（上传失败），对应“Bugatti Chiron 2017 Sports Car 3D模型(6e48z1kc7r40-bugatti.zip”（上传失败），代码：
``` c++
    Model ourModel0("./models/bugatti/bugatti.obj");//车，没纹理
```
##### 下载来自：https://free3d.com/3d-model/bugatti-chiron-2017-model-31847.html
##### 2.Dragon文件夹（上传成功），对应“Black Dragon Rigged And Game Ready 3D模型(gdoi5oiog8hs-Black-Dragon-NEW-27.03.2017.zip”（上传失败），代码：
``` c++
    Model ourModel2("./models/Dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx");//龙1ok
    Model ourModel3("./models/Dragon/Dragon 2.5_fbx.fbx");//龙2ok
    Model ourModel4("./models/Dragon/Dragon 2.5_stl.stl");//龙3ok
```
##### 下载来自：https://free3d.com/3d-model/black-dragon-rigged-and-game-ready-92023.html
##### 3.koenigsegg文件夹（上传成功），对应“Koenigsegg Agera 3D模型(82-koenigsegg-agera).zip”（上传成功），未采用，
##### 下载来自：https://free3d.com/3d-model/koenigsegg-agera-72095.html
##### 4.Manuel_fbx文件夹（fbx文件失败，其他成功），对应“Manuel Animated 001 Dancing 3D模型(22-rp_manuel_animated_001_dancing_fbx.zip”（上传失败），代码：
``` c++
    Model ourModel1("./models/Manuel_fbx/rp_manuel_animated_001_dancing.fbx");//人ok，sourceimages纹理
```
##### 下载来自：https://free3d.com/3d-model/manuel-animated-001-dancing-256270.html
##### 注：sourceimages文件夹（上传成功）为Manuel_fbx的纹理文件夹
##### 5.moon文件夹（上传成功），对应“Moon Photorealistic 2K 3D模型(44-moon-photorealistic-2k.rar”（上传成功），未采用（Project02可采用，但实际实现未采用模型），
##### 下载来自：https://free3d.com/3d-model/moon-photorealistic-2k-853071.html
##### 6.nanosuit文件夹（上传成功），对应“nanosuit.rar”（图中未显示，上传成功），代码：
``` c++
    Model ourModel0("./models/nanosuit/nanosuit.obj");//ok，learnopengl-cn
```
##### 下载来自：https://learnopengl-cn.github.io/data/nanosuit.rar
##### 注：此模型为LearnOpenGL采用
##### 7.spot文件夹（上传成功），代码：
``` c++
    //Model ourModel("./models/spot/spot_triangulated_good.obj");//牛，没纹理文件.mtl
```
##### 此模型来自：GAMES101-现代计算机图形学入门课程，Assignment3
##### 8.SUV文件夹（上传成功），对应“SUV 3D模型(68-transportation-001.zip”（上传成功），代码：
``` c++
    //Model ourModel5("./models/SUV/1.obj");//SUV车，不完整
    //Model ourModel6("./models/SUV/1.3DS");//SUV车，不完整
```
##### 下载来自：https://free3d.com/3d-model/transportation-3d-model-164657.html
##### 9.wolf文件夹（上传成功），对应“Wolf Rigged And Game Ready 3D模型(k2yeh64fmm0w-Wolf-Rigged-and-Game-Ready.zip”（上传失败），代码：
``` c++
    //Model ourModel("./models/wolf/Wolf_obj.obj");//狼，没纹理
```
##### 下载来自：https://free3d.com/3d-model/wolf-rigged-and-game-ready-42808.html
##### 10.“Hand Wash 3D模型(50-dettoll-bottle.rar”（上传成功），未采用，
##### 下载来自：https://free3d.com/3d-model/dettol-hand-wash-802488.html
