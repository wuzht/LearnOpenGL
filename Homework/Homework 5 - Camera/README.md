# Homework 5 - Camera

## 1 Basic

### 1.1 投影 (Projection)

* 把上次作业绘制的cube放置在(-1.5, 0.5, -1.5)位置，要求6个面颜色不一致
* 正交投影(orthographic projection)：实现正交投影，使用多组(left, right, bottom, top, near, far)参数，
  比较结果差异
* 透视投影(perspective projection)：实现透视投影，使用多组参数，比较结果差异

### 1.2 视角变换 (View Changing)

把cube放置在(0, 0, 0)处，做透视投影，使摄像机围绕cube旋转，并且时刻看着cube中心

### 1.3 ImGui

在GUI里添加菜单栏，可以选择各种功能。 Hint: 使摄像机一直处于一个圆的位置，可以参考以下公式：

```c++
camPosX=sin(clock()/1000.0)*Radius;
camPosZ=cos(clock()/1000.0)*Radius;
```

原理很容易理解，由于圆的公式 $a^2+b^2=1​$ ，以及有 $sin^2x+cos^2x=1​$ ，所以能保证摄像机在XoZ平面的
一个圆上。

### 1.4 

在现实生活中，我们一般将摄像机摆放的空间 **View matrix** 和被拍摄的物体摆设的空间 **Model matrix** 分开，但
是在OpenGL中却将两个合二为一设为 **ModelView matrix**，通过上面的作业启发，你认为是为什么呢？在报
告中写入。（Hints：你可能有不止一个摄像机）

## 2 Bonus

### 2.1 Camera 类

实现一个camera类，当键盘输入`w,a,s,d` ，能够前后左右移动；当移动鼠标，能够视角移动("look around")，
即类似FPS(First Person Shooting)的游戏场景
Hint: camera类的头文件可以参考如下（同样也可以自己定义，只要功能相符即可）：

```c++
class Camera{
public:
    ...
    void moveForward(GLfloat const distance);
    void moveBack(GLfloat const distance);
    void moveRight(GLfloat const distance);
    void moveLeft(GLfloat const distance);
    ...
    void rotate(GLfloat const pitch, GLfloat const yaw);
    ...
private:
    ...
    GLfloat pfov,pratio,pnear,pfar;
    GLfloat cameraPosX,cameraPosY,cameraPosZ;
    GLfloat cameraFrontX,cameraFrontY,cameraFrontZ;
    GLfloat cameraRightX,cameraRightY,cameraRightZ;
    GLfloat cameraUpX,cameraUpY,cameraUpZ;
    ...
};
```

PS. `void rotate(GLfloat const pitch, GLfloat const yaw)` 里的`pitch` 、`yaw` 均为欧拉角（参考上方References）