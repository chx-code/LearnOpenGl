## 模板测试

### 1. 简介
```text
    模板缓冲操作允许我们在渲染片段时将模板缓冲设定为一个特定的值。
    通过在渲染时修改模板缓冲的内容，我们写入了模板缓冲。
    在同一个（或者接下来的）渲染迭代中，我们可以读取这些值，来决定丢弃还是保留某个片段。
```

### 2. 常用接口
```c++
// 启用模板测试。在这一行代码之后，所有的渲染调用都会以某种方式影响着模板缓冲。
glEnable(GL_STENCIL_TEST);

// 需要在每次迭代之前清除模板缓冲。
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

// glStencilMask允许我们设置一个位掩码(Bitmask)，它会与将要写入缓冲的模板值进行与(AND)运算。
// 默认情况下设置的位掩码所有位都为1，不影响输出，但如果我们将它设置为0x00，写入缓冲的所有模板值最后都会变成0.这与深度测试中的glDepthMask(GL_FALSE)是等价的。
glStencilMask(0xFF); // 每一位写入模板缓冲时都保持原样
glStencilMask(0x00); // 每一位在写入模板缓冲时都会变成0（禁用写入）
```

### 3. 模板函数
- 用于控制模板测试过程中进行的操作
```c++
/*
 * glStencilFunc: 描述了OpenGL应该对模板缓冲内容做什么;
 * func：设置模板测试函数(Stencil Test Function)。这个测试函数将会应用到已储存的模板值上和 ref 值上。
 * ref：设置了模板测试的参考值(Reference Value)。模板缓冲的内容将会与这个值进行比较。可用的选项有：GL_NEVER、GL_LESS、GL_LEQUAL、GL_GREATER、GL_GEQUAL、GL_EQUAL、GL_NOTEQUAL和GL_ALWAYS。它们的语义和深度缓冲的函数类似。
 * mask：设置一个掩码，它将会与参考值和储存的模板值在测试比较它们之前进行与(AND)运算。初始情况下所有位都为1。
 */
glStencilFunc(GLenum func, GLint ref, GLuint mask);
```
```c++
/*
 * glStencilOp: 确定应该如何更新缓冲
 * sfail：模板测试失败时采取的行为。
 * dpfail：模板测试通过，但深度测试失败时采取的行为。
 * dppass：模板测试和深度测试都通过时采取的行为。
 * 每个选项都可以选用以下的其中一种行为：
 *
 *  行为	            描述
 * GL_KEEP	    保持当前储存的模板值
 * GL_ZERO	    将模板值设置为0
 * GL_REPLACE	将模板值设置为glStencilFunc函数设置的ref值
 * GL_INCR	    如果模板值小于最大值则将模板值加1
 * GL_INCR_WRAP	与GL_INCR一样，但如果模板值超过了最大值则归零
 * GL_DECR	    如果模板值大于最小值则将模板值减1
 * GL_DECR_WRAP	与GL_DECR一样，但如果模板值小于0则将其设置为最大值
 * GL_INVERT	按位翻转当前的模板缓冲值
 */
glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
```