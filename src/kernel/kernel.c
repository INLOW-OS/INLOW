/* MIT License
 * 
 * Copyright (c) 2019 by Qv Junping
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file kernel.c
 * @author 屈俊平 (qvjunping@gmail.com)
 * @date 2019-10-14
 * @version 0.1
 * 
 * @brief 内核C语言入口文件
 * 
 * 本文件主要实现了inlow_main()函数，此函数由汇编程序loader.s调用。
 * 现在这个文件很简单，就是在屏幕上输出一行字符。
 * 
 * @see https://blog.inlow.online/2019/01/05/Hello-World/
 */

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint8_t */

/**
 * @brief 内核入口文件
 * 
 * 此文件现在只在屏幕上输出一行字符，这里要了解的是显示内存的知识。
 * 0xB8000是x86的VGA文本模式缓存地址，要显示文字，向这个内存地址写数据即可，
 * 每个VGA buffer都是BBBBFFFFCCCCCCCC的结构，其中B表示背景色，F表示前景色，
 * C表示ASCII字符，也就是两个字节描述一个VGA文本模式下的字符。
 * 
 * 颜色对应如下：
 *   BLACK         = 0
 *   BLUE          = 1
 *   GREEN         = 2
 *   CYAN          = 3
 *   RED           = 4
 *   MAGENTA       = 5
 *   BROWN         = 6
 *   LIGHT_GREY    = 7
 *   DARK_GREY     = 8
 *   LIGHT_BLUE    = 9
 *   LIGHT_GREEN   = A
 *   LIGHT_CYAN    = B
 *   LIGHT_MAGENTA = C
 *   LIGHT_RED     = D
 *   LIGHT_BROWN   = E
 *   WHITE         = F
 */
void inlow_main()
{
    uint8_t *video = (uint8_t*)0xB8000; /**< VGA文本模式内存首地址 */
    const char *words = "Zero in your target, and go for it.";
    const uint16_t init_color = 0x77;   /**< 初始化颜色：灰色 */
    const uint16_t font_color = 0x79;   /**< 文本颜色：灰底蓝字 */


    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j =0; j < 80; j++)
        {
            video[2 * (80 * i + j)] = ' ';
            video[2 * (80 * i + j) + 1] = init_color;
        }
    }

    for (size_t i = 80 * 10 + 18; i < 80 * 10 + 18 + 35; i++)
    {
        video[2 * i] = words[i - 80 * 10 - 18];
        video[2 * i + 1] = font_color;
    }
}
