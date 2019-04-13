# Homework 1 - Learning about CG

## Basic

回答下面的问题：

1. 结合上述参考链接（或其他参考资料），谈谈自己对计算机图形学的理解。

   根据维基百科和百度百科的说法，计算机图形学(Computer Graphics，简称CG)是一种使用数学算法将二维或三维图形转化为计算机显示器的栅格形式的科学。简单地说，计算机图形学的主要研究内容就是研究如何在计算机中表示图形、以及利用计算机进行图形的计算、处理和显示的相关原理与算法。

   计算机图形学是数字图像处理或计算机视觉的逆过程。数字图像处理是使用计算机对外界获得的数字图像进行处理。计算机视觉试图从图像中来理解和识别其中的特定信息，研究如何使计算机从数字图像或视频中获得高层次的理解。而计算机图形学所做的是相反工作，它使用计算机来研究图形的表示、生成、处理和显示。

   计算机图形学使用计算机在硬件和软件的帮助下，创建计算机图形，关注数字合成与操作视觉的图形内容，包括二维图形、三维图像以及影像处理。主要研究内容就是研究如何在计算机中表示图形、以及利用计算机进行图形的计算、处理和显示的相关原理与算法。图形通常由点、线、面、体等几何元素和灰度、色彩、线型、线宽等非几何属性组成。从处理技术上来看，图形主要分为两类，一类是基于线条信息表示的，如工程图、等高线地图、曲面的线框图等，另一类是明暗图，也就是通常所说的真实感图形。

   计算机图形学主要包括四个重要内容，分别是建模、渲染、动画和人机交互。

   计算机图形学的应用广泛，如图形硬件、图形标准、图形交互技术、光栅图形生成算法、曲线曲面造型、实体造型、真实感图形计算与显示算法、非真实感绘制，以及计算可视化、计算机动画、自然景物仿真、虚拟现实等。

2. 结合上述参考链接（或其他参考资料），回答什么是OpenGL? OpenGL ES? Web GL? Vulkan? DirectX?

   * OpenGL

     开放式图形库 (OpenGL) 是一种跨语言、跨平台的应用程序编程接口 (API)，用于渲染二维和三维矢量图形。API 通常用于与图形处理单元 (GPU) 交互，以实现硬件加速渲染。OpenGL 包含了一系列可以操作图形、图像的函数，然而，OpenGL 本身并不是一个 API，它仅仅是一个由Khronos 组织制定并维护的规范 (Specification)。

   * OpenGL ES

     OpenGL for Embedded Systems (OpenGL ES 或 GLES) 是 OpenGL 计算机图形渲染应用程序编程接口 (API) 的一个子集，用于渲染二维和三维计算机图形，如视频游戏所使用的图形，通常使用图形处理单元 (GPU) 加速硬件。它专为智能手机、平板电脑、视频游戏机和 PDA 等嵌入式系统设计。OpenGLES 是"历史上部署最广泛的 3D 图形 API"。

     API 是跨语言和多平台的。库 glut 和 glu 不适用于 OpenGL ES。OpenGL ES 由非盈利技术联盟Khronos 集团管理。Vulkan 是 Khronos 的下一代 API，专为移动和桌面设备提供更简单的高性能驱动程序。

   * Web GL

     WebGL (Web Graphics Library) 是一种 JavaScript API，用于在不使用插件的情况下在任何兼容的网页浏览器中呈现交互式2D和3D图形。WebGL完全集成到浏览器的所有网页标准中，可将影像处理和效果的GPU加速使用方式当做网页Canvas的一部分。WebGL元素可以加入其他HTML元素之中并与网页或网页背景的其他部分混合。WebGL程序由JavaScript编写的句柄和OpenGL Shading Language（GLSL）编写的着色器代码组成，该语言类似于C或C++，并在计算机的图形处理器（GPU）上运行。WebGL由非营利Khronos Group设计和维护。

   * Vulkan

     Vulkan是一个低开销、跨平台的二维、三维图形与计算的应用程序接口（API），最早由科纳斯组织在2015年游戏开发者大会（GDC）上发表。与OpenGL类似，Vulkan针对全平台即时3D图形程序（如电子游戏和交互媒体）而设计，并提供高性能与更均衡的CPU与GPU占用，这也是Direct3D 12和AMD的Mantle的目标。与Direct3D（12版之前）和OpenGL的其他主要区别是，Vulkan是一个底层API，而且能执行并行任务。除此之外，Vulkan还能更好地分配多个CPU核心的使用。

   * DirectX

     Microsoft DirectX是一组应用程序编程接口（API），用于在Microsoft平台上处理与多媒体相关的任务，尤其是游戏编程和视频。最初，这些API的名称都以Direct开头，例如Direct3D，DirectDraw，DirectMusic，DirectPlay，DirectSound等。DirectX这个名称被创造为所有这些API的简写术语（X.代表特定的API名称）并很快成为该集合的名称。当微软后来着手开发游戏机时，X被用作Xbox这个名称的基础，表明控制台是基于DirectX技术的。

     Direct3D（DirectX中的3D图形API）广泛用于开发Microsoft Windows和Xbox系列游戏机的视频游戏。Direct3D也被其他软件应用程序用于可视化和图形任务，如CAD/CAM工程。由于Direct3D是DirectX最广泛宣传的组件，因此经常会看到“DirectX”和“Direct3D”的名称可以互换使用。

     DirectX主要基于C++编程语言实现，遵循COM架构。

3. `gl.h` `glu.h` `glew.h` 的作用分别是什么?

   * `gl.h`

     GL (Graphics Library) 是OpenGL 1.1版的基本头文件。它提供OpenGL所使用的函数和常量声明。这意味着，如果要使用1.1版以外的任何功能，则必须在此基础上添加任何扩展库。

   * `glu.h`

     GLU（OpenGL utilities library, OpenGL实用库）所使用的函数和常量声明。GLU库属于OpenGL标准的一部分。不过它已经非常过时了，也没有更新很久了，不应该在任何现代OpenGL程序中使用。

   * `glew.h`

     OpenGL Extension Wrangler Library (GLEW) 是用于查询和加载OpenGL扩展功能的跨平台C/C++库。当你初始化这个库时，它提供了有效的机制，在运行时检查你的平台和显卡，以确定在目标平台上支持哪些OpenGL扩展。所有OpenGL扩展都显示在一个头文件中，该头文件是由官方扩展列表中的机器生成的。`glew.h`隐式包含常规的OpenGL头文件，因此不需要再包含`GL/gl.h`。

4. 使用GLFW和freeglut的目的是什么？

   在编写OpenGL程序时，我们首先要做的就是创建一个OpenGL上下文(Context)和一个用于显示的窗口。然而，这些操作在每个系统上都是不一样的，OpenGL有目的地从这些操作抽象(Abstract)出去。这意味着我们不得不自己处理创建窗口，定义OpenGL上下文以及处理用户输入。

   幸运的是，一些库已经提供了这些功能，如GLFW和GLUT。

   GLFW (OpenGL FrameWork, OpenGL 框架) 是一个轻量级实用的专门针对OpenGL的C语言程序库，它提供了一些渲染物体所需的最低限度的接口。它使程序员能够创建和管理Windows和OpenGL上下文，定义窗口参数以及处理用户输入，如处理操纵杆、键盘和鼠标输入。

   FreeGLUT 是 GLUT (OpenGL Utility Toolkit, OpenGL实用工具包) 库的开放源代码替代品。GLUT（或FreeGLUT）允许用户在各种平台上创建和管理包含OpenGL上下文的窗口，还可以读取鼠标、键盘和操纵杆功能。FreeGLUT旨在完全替代GLUT，并且只有几个不同之处。

5. 结合上述参考链接（或其他参考资料），选择一个SIGGRAPH 2017/2018上 你最喜欢的专题，介绍该专题是做什么的，使用了什么CG技术？（不少于100字）

   在每年 SIGGRAPH 大会上，计算机动画节 (Computer Animation Festival) 是活动中备受瞩目的一部分，每年展示来自于全世界最具创新性和优秀的计算机动画作品。

   计算机动画是用于生成动画图像的过程。更通用的术语计算机生成图像（CGI）包括静态场景和动态图像，而计算机动画仅指移动图像。现代计算机动画通常使用三维计算机图形，尽管二维计算机图形仍然用于风格化、低带宽和更快的实时渲染。有时，动画的目标是计算机本身，但有时电影也一样。

   要创作计算机动画，必须应用到许多CG技术。对于三维动画，对象（模型）是建立在计算机监视器（模型）上的，而三维图形则装配有一个虚拟骨架。对于二维图形动画，单独的对象（插图）和单独的透明层与虚拟骨架一起使用或不使用。然后，动画师在关键帧上移动人物的四肢、眼睛、嘴巴、衣服等。关键帧之间的外观差异由计算机在称为粗花或变形的过程中自动计算出来。最后，渲染动画。




## Optional

### VS2017配置OpenGL

参考博客：

- [【PT君的OpenGL】第一天【VS2017+OpenGL环境的配置(固定管线+可编程管线)】](https://blog.csdn.net/qq_19003345/article/details/76098781)
- [创建窗口 - LearnOpenGL CN](https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/)



## References

* [什么是计算机图形学？](http://staff.ustc.edu.cn/~lgliu/Resources/CG/What_is_CG.htm)

* [OpenGL - LearnOpenGL CN](https://learnopengl-cn.github.io/01%20Getting%20started/01%20OpenGL/)

* [Wikipedia](https://en.wikipedia.org)

* [Difference between OpenGL files glew.h and gl.h/glu.h](https://stackoverflow.com/questions/12122631/difference-between-opengl-files-glew-h-and-gl-h-glu-h)

* [glew, glee与 gl glu glut glx glext的区别和关系](https://blog.csdn.net/delacroix_xu/article/details/5881942)

  
