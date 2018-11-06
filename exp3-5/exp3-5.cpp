
#include "../data structure/sqstack.cpp"
#include <iostream>
using namespace std;

//0不可走，1可走
int maze[6][6] = {  {0,0,0,0,0,0},
					{0,1,1,1,0,0},
					{0,1,0,1,1,0},
					{0,1,1,1,0,0},
					{0,0,1,1,1,0},
					{0,0,0,0,0,0} };
enum Direction {null=-1,right,down,left,up};



class Box {
public:
	//x,y记录坐标
	int x, y;
	//di记录查找方向
	Direction di;

	//默认方向向右
	Box(int i=1,int j=1) {
		x = i;
		y = j;
		di = Direction::null;
	}

	void PrintBox() {
		printf("x:%d, y:%d, pre:%d\n", x, y, di);
	}

	const Box MoveR() {
		Box newBox(x , y+1);
		return newBox;
	}	
	const Box MoveD() {
		Box newBox(x+1 , y);
		return newBox;
	}	
	const Box MoveL() {
		Box newBox(x, y-1);
		return newBox;
	}	
	const Box MoveU() {
		Box newBox(x -1, y );
		return newBox;
	}
};

bool FindPath(int xi, int yi, int xe, int ye);
void PrintPath(Sqstack<Box> stack);

int main()
{	
	cout <<  sizeof(maze) / sizeof(int) << endl;
	if (!FindPath(1,1,4,4)) {
		cout << "该迷宫无解!" << endl;
	}
	cin.get();
}

//从(xi,yi)到(xe,ye)
bool FindPath(int xi,int yi,int xe, int ye) {
	
	Box box(xi, yi);
	int i,j;
	int solution = 0;
	int minLength = sizeof(maze) / sizeof(int);	//最短长度的初始值是迷宫的总长度
	Direction di;	//记录当前查找的方向
	bool found;
	Sqstack<Box> stack;
	Sqstack<Box> minPath;
	stack.Push(box);
	maze[xi][yi] = -1;	//设置已走过
	
	while (!stack.IsEmpty()){
		box = stack.GetTop();
		i = box.x; j = box.y; di = box.di;

		if (i == xe && j == ye) {
			//路径条数加1
			solution++;
			printf("第%d条路径如下:\n",solution);
			PrintPath(stack);

			//寻找最短路径,这里用小于号,代表求第一条最短路径
			if (stack.GetCount() < minLength) {
				minLength = stack.GetCount();
				minPath = stack;
			}

			//打印完后回退一格
			maze[i][j] = 1;	//让终点变为可走
			stack.Pop();
			box = stack.GetTop();
			di = box.di;	
			di = (Direction)(di + 1);	//方向变为退格后得到格子的方向，再顺时针转动
		}
		//存储临时的格子
		Box temp;
		found = false;
		while (di<4 && !found)
		{		
			di = (Direction)(di + 1);
			switch (di){
				case Direction::right:
					temp = box.MoveR();
					break;
				case Direction::down:
					temp = box.MoveD();
					break;
				case Direction::left:
					temp = box.MoveL();
					break;
				case Direction::up:
					temp = box.MoveU();
					break;
			}			
			if (maze[temp.x][temp.y] == 1) 
				found = true;
		}

		if (found) {
			//重点--更新时要弹出再入栈
			//如果找到,更新box在栈的方向，弹出再进入
			box.di = di;
			stack.Pop();
			stack.Push(box);

			stack.Push(temp);	//可走的temp入栈
			maze[temp.x][temp.y] = -1;
		}
		else {
			//如果找不到,再退一格
			box = stack.Pop();
			maze[box.x][box.y] = 1;
		}
	}

	if (solution == 0)
		return false;
	cout << "第一条最短路径长为" << minLength << "，如下：" << endl;
	PrintPath(minPath);
	return true;
}

void PrintPath(Sqstack<Box> stack) {
	Box path[50];
	int i = 0;
	while (!stack.IsEmpty()){
		path[i++] = stack.Pop();
	}
	//由于起点会多入一次栈，少打印一次
	i--;
	for (; i >= 0; i--) {
		printf("(%d,%d)    ", path[i].x, path[i].y);		
	}
	cout << endl;
}