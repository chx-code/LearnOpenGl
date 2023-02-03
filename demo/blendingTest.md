## 混合

### 1. 介绍
```text
混合(Blending)通常是实现物体透明度(Transparency)的一种技术。
```
```text
当绘制一个有不透明和透明物体的场景的时候，大体的原则如下：
 1. 先绘制所有不透明的物体。
 2. 对所有透明的物体排序。
 3. 按顺序绘制所有透明的物体。
```

### 2. 常用接口
```c++
// 混合开启接口
glEnable(GL_BLEND);

/*
 * sfactor : 设置源因子；
 * dfactor ：设置目标因子；
 * 
 * 选项	值
 * GL_ZERO	因子等于0
 * GL_ONE	因子等于1
 * GL_SRC_COLOR	因子等于源颜色向量C¯source
 * GL_ONE_MINUS_SRC_COLOR	因子等于1−C¯source
 * GL_DST_COLOR	因子等于目标颜色向量C¯destination
 * GL_ONE_MINUS_DST_COLOR	因子等于1−C¯destination
 * GL_SRC_ALPHA	因子等于C¯source 的alpha分量
 * GL_ONE_MINUS_SRC_ALPHA	因子等于1 − C¯source 的alpha 分量
 * GL_DST_ALPHA	因子等于C¯destination 的alpha 分量
 * GL_ONE_MINUS_DST_ALPHA	因子等于1− C¯destination 的alpha 分量
 * GL_CONSTANT_COLOR	因子等于常数颜色向量C¯constant
 * GL_ONE_MINUS_CONSTANT_COLOR	因子等于1−C¯constant
 * GL_CONSTANT_ALPHA	因子等于C¯constant的alpha分量
 * GL_ONE_MINUS_CONSTANT_ALPHA	因子等于1− C¯constant的alpha分量
 */
glBlendFunc(GLenum sfactor, GLenum dfactor)
```

### 3. 注意事项
```markdown
当采样纹理的边缘的时候，OpenGL会对边缘的值和纹理下一个重复的值进行插值（因为我们将它的环绕方式设置为了GL_REPEAT。这通常是没问题的，但是由于我们使用了透明值，纹理图像的顶部将会与底部边缘的纯色值进行插值。这样的结果是一个半透明的有色边框，你可能会看见它环绕着你的纹理四边形。要想避免这个，每当你alpha纹理的时候，请将纹理的环绕方式设置为GL_CLAMP_TO_EDGE：

glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
```