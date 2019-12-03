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
 * @file kernel.cpp
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
#include <kernel/log.h>

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
extern "C" void inlow_main()
{
    Log::initTerminal();
    Log::printf("Zero in your target, and go for it.\n");
    Log::printf("I'm INLOW!\n");
    Log::printf("I'm %d years old!\n", 2);
    Log::printf("unsigned int max %u\n", 4294967295);
    Log::printf("unsigned int min %u\n", 0);
    Log::printf("signed int max %d\n", 2147483647);
    Log::printf("signed int min %d\n", -2147483647);
    Log::printf("hex number 0x%x\n", 4294967295);
}
