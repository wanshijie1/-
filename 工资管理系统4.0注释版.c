#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义职工结点的结构体
struct node
{
	char no[12];	   // 职工工号
	char name[40];	   // 姓名
	int month[12];	   // 月份
	float gz[12];	   // 月工资
	float total;	   // 年度总工资
	struct node *link; // 指向下一结点的指针
};

// 全局变量，指向链表的头结点
struct node *head = NULL;

// 函数声明
void insertNode(); // 插入职工节点到链表中。
struct node *findNode(char *no, int month);
void updateSalary();				  // 修改某个职工某个月的工资。
void deleteNode();					  // 删除某个职工的工资相关信息。
float calculateTotalSalary(char *no); // 统计某个职工年度总工资。
void sortNodes();					  // 对职工的月工资或年度总工资进行排序。（冒泡排序）
void displayRanking();				  // 输出职工的月工资或年度总工资排名结果
void saveData();					  // 保存数据到文件
void loadData();					  // 从文件读取数据
void jinyu();						  // 计算金鱼问题
void dayin();						  // 打印图案
int login();						  // 登录功能

int main()
{
	printf("请选择运行的程序\n");
	int choice;
	while (1)
	{
		printf("1. 金鱼问题\n");
		printf("2. 打印图案\n");
		printf("3. 工资管理系统\n");
		printf("4. 退出\n");
		printf("请选择操作：");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			jinyu();
			break;
		case 2:
			dayin();
			break;
		case 3:
			if (login())
			{
				loadData();
				while (1)
				{
					printf("\n工资管理系统\n");
					printf("1. 录入职工工资信息\n");
					printf("2. 查找职工某月工资信息\n");
					printf("3. 修改职工某月工资\n");
					printf("4. 删除职工工资信息\n");
					printf("5. 统计职工年度总工资\n");
					printf("6. 对职工工资进行排名\n");
					printf("7. 退出\n");
					printf("请选择操作：");
					scanf("%d", &choice);

					switch (choice)
					{
					case 1:
						insertNode();
						break;
					case 2:
					{
						char no[12];
						int month;
						printf("请输入要查询的职工工号：");
						scanf("%s", no);
						printf("请输入要查询的月份：");
						scanf("%d", &month);
						struct node *foundNode = findNode(no, month);
						if (foundNode != NULL)
						{
							printf("工号：%s，姓名：%s，月份：%d，工资：%.2f\n",
								   foundNode->no, foundNode->name, month, foundNode->gz[month - 1]);
						}
						else
						{
							printf("未找到该职工的工资信息。\n");
						}
						break;
					}
					case 3:
						updateSalary();
						break;
					case 4:
						deleteNode();
						break;
					case 5:
					{
						char no[12];
						printf("请输入要统计年度总工资的职工工号：");
						scanf("%s", no);
						float totalSalary = calculateTotalSalary(no);
						printf("工号：%s，年度总工资：%.2f\n", no, totalSalary);
						break;
					}
					case 6:
						sortNodes();
						displayRanking();
						break;
					case 7:
						saveData(); // 保存数据
						printf("退出工资管理系统。\n");
						break;
					default:
						printf("无效的选择，请重新输入。\n");
						break;
					}
					if (choice == 7)
					{
						break;
					}
				}
			}
			else
			{
				printf("登录失败，无法访问工资管理系统。\n");
			}
			break;
		case 4:
			printf("退出程序。\n");
			return 0;
		default:
			printf("无效的选择，请重新输入。\n");
			break;
		}
	}
}

void jinyu()
{
	int i, j, n = 0, x;			 // 声明变量 i、j、n 和 x，n 初始化为 0
	for (i = 23; n == 0; i += 2) // 从 i=23 开始循环，直到找到符合条件的数或 n 变为非零
	{
		for (j = 1, x = i; j <= 4 && x >= 11; j++) // 在每个 i 的循环中，从 j=1 开始循环，直到 j=4 或者 x 小于 11
		{
			if ((x + 1) % (j + 1) == 0) // 如果 (x+1)%(j+1) 的结果等于 0
				x -= (x + 1) / (j + 1); // 则更新 x 的值为 x-(x+1)/(j+1)
			else
			{
				x = 0; // 如果不满足上述条件，则将 x 置为 0 并跳出内层循环
				break;
			}
		}
		if (j == 5 && x == 11) // 如果内层循环正常结束，且 j=5 且 x=11
		{
			printf("%d\n", i); // 输出满足条件的 i 的值
			n = 1;			   // 将 n 置为非零，跳出外层循环
		}
	}
}

void dayin() // 打印图形
{
	int n; // 声明一个整型变量n
	printf("请输入n的值（n<=9）:");
	scanf("%d", &n);					 // 从用户输入中读取n的值
	int totalSpaces = (n + 1) * n / 2.0; // 计算总的空格数
	// 打印上半部分
	for (int row = 1; row <= n; row++) // 外层循环控制行数
	{
		int spacesInRow = (row + 1) * row / 2.0; // 计算当前行的空格数
		// 打印空格
		for (int space = 1; space <= totalSpaces - spacesInRow; space++) // 内层循环控制空格数
		{
			printf(" ");
		}
		// 打印数字和间隔
		for (int pattern = 1; pattern <= 3; pattern++) // 内层循环控制打印数字和间隔
		{
			if (pattern == 1 || pattern == 3) // 在第1和第3个模式下打印数字
			{
				// 打印数字
				for (int i = 1; i <= row; i++)
				{
					printf("%d", row);
				}
			}
			else // 在第2个模式下打印间隔空格
			{
				// 打印间隔空格
				int spaces = (spacesInRow - 1) * 2 - 1;
				for (int i = 1; i <= spaces; i++)
				{
					printf(" ");
				}
			}
		}
		printf("\n"); // 打印换行符
	}

	// 打印下半部分
	for (int row = 1; row <= n - 1; row++) // 外层循环控制行数
	{
		int spacesInRow = (n - row + 1) * (n - row) / 2.0; // 计算当前行的空格数

		// 打印空格
		for (int space = 1; space <= totalSpaces - spacesInRow; space++) // 内层循环控制空格数
		{
			printf(" ");
		}

		// 打印数字和间隔
		for (int pattern = 1; pattern <= 3; pattern++) // 内层循环控制打印数字和间隔
		{
			if (pattern == 1 || pattern == 3) // 在第1和第3个模式下打印数字
			{
				// 打印数字
				for (int i = n - 1; i >= row; i--)
				{
					printf("%d", n - row);
				}
			}
			else // 在第2个模式下打印间隔空格
			{
				// 打印间隔空格
				int spaces = (spacesInRow - 1) * 2 - 1;
				for (int i = 1; i <= spaces; i++)
				{
					printf(" ");
				}
			}
		}
		printf("\n"); // 打印换行符
	}
}

int login()
{
	char username[20]; // 定义一个长度为20的字符数组，用于存储用户名
	char password[20]; // 定义一个长度为20的字符数组，用于存储密码
	printf("请输入用户名：");
	scanf("%s", username); // 从用户输入中读取用户名，并将其存储到username数组中
	printf("请输入密码：");
	scanf("%s", password); // 从用户输入中读取密码，并将其存储到password数组中
	// 简单示例，用户名为admin，密码为123456
	// 使用strcmp函数比较输入的用户名和密码与预设值是否一致
	if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0)
	{
		printf("登录成功！\n");
		return 1; // 返回1表示登录成功
	}
	else
	{
		printf("登录失败！\n");
		return 0; // 返回0表示登录失败
	}
}

void insertNode()
{
	struct node *newNode = (struct node *)malloc(sizeof(struct node)); // 创建一个新的节点
	printf("请输入职工工号：");
	scanf("%s", newNode->no); // 从用户输入中读取职工工号，并将其存储到newNode的no成员中
	printf("请输入职工姓名：");
	scanf("%s", newNode->name); // 从用户输入中读取职工姓名，并将其存储到newNode的name成员中
	for (int i = 0; i < 12; i++)
	{
		printf("请输入职工%d月工资：", i + 1);
		scanf("%f", &newNode->gz[i]); // 循环读取用户输入的12个月的工资，并将其存储到newNode的gz数组中
	}
	newNode->total = 0; // 初始化工资总和为0
	for (int i = 0; i < 12; i++)
	{
		newNode->total += newNode->gz[i]; // 计算工资总和，将每个月的工资累加到total成员中
	}
	newNode->link = head; // 将新节点的link指向头节点，即将新节点插入到链表的头部
	head = newNode;		  // 更新头节点为新节点
	printf("录入成功！\n");
}
struct node *findNode(char *no, int month)
{
	struct node *current = head; // 从头节点开始遍历链表
	while (current != NULL)
	{
		if (strcmp(current->no, no) == 0)
		{					// 比较当前节点的工号和给定工号是否一致
			return current; // 如果找到匹配的节点，则返回当前节点
		}
		current = current->link; // 没有找到匹配节点，则继续遍历下一个节点
	}
	return NULL; // 遍历完整个链表仍未找到匹配节点，则返回NULL
}

void updateSalary()
{
	char no[12];
	int month;
	printf("请输入要修改工资的职工工号：");
	scanf("%s", no); // 从用户输入中读取职工工号，并将其存储到no数组中
	printf("请输入要修改工资的月份：");
	scanf("%d", &month); // 从用户输入中读取要修改工资的月份
	struct node *foundNode = findNode(no, month); // 调用findNode函数查找具有给定工号和月份的节点
	if (foundNode != NULL)
	{
		printf("请输入新的工资：");
		scanf("%f", &foundNode->gz[month - 1]); // 从用户输入中读取新的工资，并将其存储到相应月份的工资数组中
		printf("修改成功！\n");
	}
	else
	{
		printf("未找到该职工的工资信息。\n");
	}
}


void deleteNode()
{
	char no[12];
	printf("请输入要删除工资信息的职工工号：");
	scanf("%s", no); // 从用户输入中读取要删除工资信息的职工工号
	struct node *current = head;
	struct node *prev = NULL;
	while (current != NULL)
	{
		if (strcmp(current->no, no) == 0)
		{ // 比较当前节点的工号与给定工号是否一致
			if (prev != NULL)
			{
				prev->link = current->link; // 如果不是头节点，则将前一个节点的link指向当前节点的下一个节点
			}
			else
			{
				head = current->link; // 如果是头节点，则更新头节点为当前节点的下一个节点
			}
			free(current); // 释放当前节点的内存
			printf("删除成功！\n");
			return;
		}
		prev = current;			 // 更新prev为当前节点
		current = current->link; // 更新current为下一个节点
	}
	printf("未找到该职工的工资信息。\n");
}


float calculateTotalSalary(char *no)
{
	struct node *foundNode = findNode(no, 0); // 调用findNode函数查找具有给定工号的节点
	if (foundNode != NULL)
	{
		return foundNode->total; // 返回找到的节点的工资总和
	}
	else
	{
		return 0; // 如果未找到节点，则返回0
	}
}

void sortNodes()
{
	struct node *current = head; // 当前节点，从头节点开始
	struct node *sorted = NULL;	 // 已排序部分的头节点
	while (current != NULL)
	{
		struct node *next = current->link; // 保存下一个节点的指针
		// 找到插入位置
		if (sorted == NULL || sorted->total < current->total)
		{
			current->link = sorted;
			sorted = current; // 将当前节点作为已排序部分的新头节点
		}
		else
		{
			struct node *temp = sorted;

			// 在已排序部分找到正确的插入位置
			while (temp->link != NULL && temp->link->total >= current->total)
			{
				temp = temp->link;
			}

			current->link = temp->link;
			temp->link = current; // 将当前节点插入到正确的位置
		}
		current = next; // 继续处理下一个节点
	}
	head = sorted; // 更新头节点为已排序部分的头节点
	printf("排序成功！\n");
	// 输出排序后的结果
	printf("排序后的结果：\n");
	current = head;
	while (current != NULL)
	{
		printf("工号：%s，姓名：%s，年度总工资：%.2f\n", current->no, current->name, current->total);
		current = current->link;
	}
}


void displayRanking()
{
	struct node *current = head; // 当前节点，从头节点开始
	int rank = 1;				 // 排名
	printf("职工工号\t姓名\t年度总工资\n");
	while (current != NULL)
	{
		printf("%s\t%s\t%.2f\n", current->no, current->name, current->total); // 输出当前节点的工号、姓名和年度总工资
		current = current->link;											  // 移动到下一个节点
		rank++;																  // 增加排名
	}
}

void saveData()
{
	FILE *fp = fopen("data.txt", "w"); // 打开名为"data.txt"的文件，以写入模式打开
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	struct node *current = head; // 当前节点，从头节点开始
	while (current != NULL)
	{
		fprintf(fp, "%s %s ", current->no, current->name); // 将当前节点的工号和姓名写入文件，用空格分隔
		for (int i = 0; i < 12; i++)
		{
			fprintf(fp, "%.2f ", current->gz[i]); // 将当前节点的每个月的工资写入文件，用空格分隔
		}
		fprintf(fp, "%.2f\n", current->total); // 将当前节点的年度总工资写入文件，换行
		current = current->link; // 移动到下一个节点
	}
	fclose(fp); // 关闭文件
	printf("数据保存成功！\n");
}


void loadData()
{
	FILE *fp = fopen("data.txt", "r"); // 打开名为"data.txt"的文件，以读取模式打开
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	struct node *current = head; // 当前节点，从头节点开始
	while (current != NULL)
	{
		struct node *next = current->link;
		free(current);	// 释放当前节点的内存
		current = next; // 移动到下一个节点
	}
	head = NULL; // 将头节点设为NULL，清空链表
	char line[200]; // 用于存储读取的每一行数据
	while (fgets(line, sizeof(line), fp))
	{																	   // 逐行读取文件内容
		struct node *newNode = (struct node *)malloc(sizeof(struct node)); // 创建新节点
		char *token = strtok(line, " "); // 使用空格分隔每一行的数据，获取工号
		strcpy(newNode->no, token); // 将工号复制到新节点的工号字段
		token = strtok(NULL, " ");	  // 继续获取下一个数据，即姓名
		strcpy(newNode->name, token); // 将姓名复制到新节点的姓名字段
		for (int i = 0; i < 12; i++)
		{
			token = strtok(NULL, " ");	  // 继续获取下一个数据，即每个月的工资
			newNode->gz[i] = atof(token); // 将工资转换为浮点数并存储到新节点的工资数组中
		}
		token = strtok(NULL, " ");	  // 继续获取下一个数据，即年度总工资
		newNode->total = atof(token); // 将年度总工资转换为浮点数并存储到新节点的年度总工资字段
		newNode->link = head; // 将新节点链接到链表头部
		head = newNode;		  // 更新头节点为新节点
	}
	fclose(fp); // 关闭文件
	printf("数据加载成功！\n");
}