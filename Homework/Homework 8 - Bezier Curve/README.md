# Homework 8 - Bezier Curve

> **Introduction**
>
> 本次作业要求大家实现一个Bezier Curve的绘制小工具。此工具可以接受鼠标输入。

主要代码在 `ShadowMapping` 类中，着色器代码在 `GLSL` 文件夹中，分别是 `shadow_mapping_depth.vs, shadow_mapping_depth.fs` 和 `shadow_mapping.vs, shadow_mapping.fs` 。

[TOC]

## 1 Basic

> 1. 用户能通过左键点击添加Bezier曲线的控制点，右键点击则对当前添加的最后一个控制点进行消除
> 2. 工具根据鼠标绘制的控制点实时更新Bezier曲线。
> 
> *Hint:* 大家可查询捕捉mouse移动和点击的函数方法

### 1.1 实现结果

实现结果见演示视频

<table>
    <tr>
        <td><center><img src="assets/1_o.png">角度1</center></td>
        <td><center><img src="assets/2_o.png">角度2</center></td>
    </tr>
</table>
### 1.2 实现方法



## 2 Bonus

> 可以动态地呈现Bezier曲线的生成过程。


## 3 References

* [阴影映射](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/03%20Shadows/01%20Shadow%20Mapping/)
* [Shadow Mapping](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping)