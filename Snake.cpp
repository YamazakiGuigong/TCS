// 导入头文件
#include <iostream>
// 导入命名空间
using namespace std;
// 使用类封装地图的生成及渲染
class map
{
private:
    int width, height;

public:
    // 获取地图的宽度和高度
    void GetMapSize(int width, int height)
    {
        width = width;
        height = height;
    }
    // 渲染地图边界
    void RenderMap(int width, int height)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || i == height - 1)
                {
                    cout << "# ";
                }
                else
                {
                    if (j == 0 || j == width - 1)
                    {
                        cout << "# ";
                    }
                    else
                    {
                        cout << "  ";
                    }
                }
            }
            cout << endl;
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
    // 获取地图的宽度和高度
    int width, height;
    std::cout << "请输入地图的宽度和高度" << std::endl;
    std::cin >> width >> height;
    // 渲染地图
    m.GetMapSize(width, height);
    m.RenderMap(width, height);
    return 0;
}
