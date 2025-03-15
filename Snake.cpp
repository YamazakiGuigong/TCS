// 导入头文件
#include <cpp-terminal/terminal.hpp>
#include <cpp-terminal/input.hpp>
#include <cpp-terminal/iostream.hpp>
#include <cpp-terminal/screen.hpp>
#include <cpp-terminal/cursor.hpp>
#include <iostream>
// 使用类封装地图的生成及渲染
class map
{
private:
    int width, height;

public:
    // 获取地图的宽度和高度
    void GetMapSize()
    {
        Term::terminal.setOptions(Term::Option::Cooked);
        Term::cout << "请输入地图的宽度:" << std::endl;
        Term::cin >> width;
        Term::cout << "请输入地图的高度:" << std::endl;
        Term::cin >> height;
        width = width;
        height = height;
        Term::cout << Term::clear_screen() << std::flush;
    }
    // 渲染地图边界
    void RenderMapBoundary()
    {
        Term::cout << Term::cursor_move(0, 0);
        for (int i = 0; i < height+2; i++)
        {
            for (int j = 0; j < width+2; j++)
            {
                if (i == 0 || i == height + 1)
                {
                    Term::cout << "# ";
                }
                else
                {
                    if (j == 0 || j == width + 1)
                    {
                        Term::cout << "# ";
                    }
                    else
                    {
                        Term::cout << "  ";
                    }
                }
            }
            Term::cout << "\n";
        }
    }
};
// 使用类封装蛇的生成及渲染
class Snake
{
};
// 使用类封装食物的生成及渲染
class food
{
};
// 使用类封装游戏的状态
class state
{
};
// 游戏主函数
int main()
{
    // 创建地图对象
    map m;
    // 获取地图大小
    m.GetMapSize();
    // 渲染地图边界
    m.RenderMapBoundary();
    return 0;
}
