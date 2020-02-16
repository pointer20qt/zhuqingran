#include<iostream>
using namespace std;
#include<string.h>
#include<string>
#include<list>
#include<vector>
#include<stack>
#include<memory>//内存 智能指针
#include<Initializer_List>
//#define NDEBUG //所有断言失效
//#include<assert.h>//断言头文件
#include<algorithm>//算法
//异常 就是错误
void task38()
{
	vector <int> arr{ 1, 2, 3, 4, 5, 6 };
	//int arr[]={ 1, 2, 3, 4, 5, 6 };
	try
	{
		while (1)
		{
			system("pause");//按任意键继续
			auto p = new int(1024 * 1024 * 25);//100MB
			cout << p << endl;
		}
	}
	catch (exception &d)//该异常是所有标准 C++ 异常的父类。
	{
		cout << "父类所捕获" << endl;
	}
	catch (bad_alloc &b)//在使用new分配内存空间时，内存空间不够时就会抛出该异常。
	{
		cout << b.what() << endl;
	}
	try
	{
		for (int i = 0; i < 7; i++)
		{
			cout << arr.at(i) << endl; // arr[0]重载了[]运算符 效率好 性能好 安全性低	//arr.at(0);安全性高
		}
		throw 2;//抛出异常  没try catch 就关闭 发送任意类型对象
		cout << "打印完了" << endl;
	}
	catch (int test)//整数异常
	{
		cout << "发生了异常，异常对象" << test << endl;
	}
	catch (out_of_range &e)//数组越界异常 throw out_of_range("数组越界");
	{
		cout << "数组越界异常" << endl;
	}
	//捕获所以c++异常
	catch (...)
	{
		cout << "出现了异常" << endl;
	}
	cout << "程序最后一句" << endl;
}
//struct 默认所以成员都是公有的
struct m
{
	int value;
};
//封装:所有成员变量私有，外部只能通过公有函数来访问 
//拷贝构造  深拷贝 浅拷贝 什么时候拷贝
//class默认所有成员私有
//析构先析构子类 构造先构造基类
//delete 不让编译器生成默认
//default 让编译器生成默认的
class principal
{
	string name;
public:
	principal(string sname)
	{
		this->name = sname;
	}
	~principal()
	{
		cout << name << "下班了" << endl;
	}
	void wash()
	{
		cout << "洗浴" << endl;
	}
};
class A
{
public:
	A()
	{
		cout << "无参构造A" << endl;
	}
	A(const A &)
	{
		cout << "拷贝构造A" << endl;
	}

};
class school
{
	//private 私有 只有本类使用
	//protected://受保护 本类 和派生类 子类 可以使用
public:
	string schoolName;//学校名
	string schoolType;//学校类别 小学 初中 高中 大学
	string address;//学校地址
	//构造方法  this 是自动传进去一个参数，因为所有成员方法都需要传一个this指针
	//school() = default;//默认的构造函数将所有成员对象，调用其默认构造方法 ==school(){}
	char *ptr;
	A test;
	principal *master;
	~school()//析构
	{
		cout << schoolName << "析构函数" << endl;
		delete master;
	}
	//浅拷贝
	school()
	{
		cout << "无参构造" << endl;
	}
	school(string schoolName, string schoolType, string address)
	{
		cout << "普通构造函数" << endl;
		this->schoolName = schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new principal("杨老师");
	}
	//拷贝出一个一样的 const 只读不能修改  深拷贝
	school(const school &p) :schoolName(p.schoolName), schoolType(p.schoolType), address(p.address)//初始化参数列表
	{
		test = p.test;
		master = new principal(*p.master);
		cout << this->schoolName << "调用了拷贝构造函数" << endl;
	}
	//类默认的移动构造和默认的拷贝构造效果
	school(school &&other) :schoolType(other.schoolType), address(other.address), schoolName(other.schoolName)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}
	virtual void SchoolOpens()
	{
		cout << this->schoolName << "开学了" << endl;
	}
	//递归调用所有成员对象的拷贝构造方法，如果不是对象，就复制
	//school(const school &p):schoolName(p.schoolName),schoolType(p.schoolType),address(p.address)//const ==只读{}
};
void initSchool(school *_this, string schoolName, string schoolType, string address)
{
	_this->schoolName = schoolName;
	_this->schoolType = schoolType;
	_this->address = address;
}
void  swap(school A, school B)
{
	school tem = A;//school tem(A); 调用拷贝构造
	//A = B;//赋值拷贝 构造拷贝
	//B = tem;
}
void school_run(school *_this)
{
	cout << _this->schoolName << "开学了" << endl;
}
void task39()
{
	// * s=(school*)malloc(sizeof(school));//c语言创建school类型 school大小空间
	//initSchool(s, "大庆指针", "就业培训机构", "大庆");
	//school_run(s);
	school *s2 = new school("指针", "就业培训机构", "大庆");
	s2->SchoolOpens();
	system("pause");
	delete s2;
	system("pause");
}
void run()
{
	school s1("指针", "就业培训机构", "大庆");
	school s2("大庆指针", "就业培训机构", "大庆");
	swap(s1, s2);
}
//编译器会优化
school getschool()
{
	school s2("指针", "就业培训机构", "大庆");//会构造
	return school(s2);
}
//移动构造
void task40()
{
	school s1(getschool());
	s1.schoolName = "八一农大";
	school s2("指针", "就业培训机构", "大庆");
	school s3(std::move(s2));//移动构造
}
typedef int I;
using I = int;
//函数返回类型是void 接受参数是int const std::string&,两种不同语法的写法不同
typedef void(*FP)(int, const std::string&); //using FP=void (*)(int,const std::string&);
void task41()
{
	int x1 = 5;
	int x2 = 12;
	swap(x1, x2);
	run();
	cout << "下一句代码" << endl;
}
//右值和左值区别，右值引用和左值引用
//本质上 指针与引用一样 school &r1=*s1 r1.master==(*s1)master;
void task42()
{
	int *p = nullptr;//空指针  
	int &r = *(int *)(nullptr);//int类型
}
//友元
class C
{
public:
	C(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	void Getxy();
	friend double Distance(C &a, C &b);
private:
	double x, y;
};
void C::Getxy()
{
	cout << "(" << x << "," << y << ")" << endl;
}
double Distance(C &a, C &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
void task43()
{
	C p1(3.0, 4.0);
	C p2(6.0, 8.0);
	p1.Getxy();
	p2.Getxy();
	double d = Distance(p1, p2);
	cout << "Distance is" << " " << d << endl;
}
//重载运算符
class complex
{
	int real;
	int imagin;
public:
	complex(int x, int y) :real(x), imagin(y)
	{

	}
	complex operator+(complex & x)
	{
		return complex(real + x.real, imagin + x.imagin);
	}
	complex operator-(complex & x)
	{
		return complex(real - x.real, imagin - x.imagin);
	}
	string toString()
	{
		char buff[50];
		sprintf(buff, "(%d+%di)", real, imagin);
		return string(buff);
	}
};
ostream & operator<<(ostream &o, complex &c)
{
	o << c.toString();
	return o;
}
void task44()
{
	complex a(2, 3);
	complex b(6, 2);
	cout << a << "与" << b << "与" << (a + b).toString() << endl;
	//拷贝赋值
	a.operator-(b);
}
//继承会将所有成员继承 覆盖 隐藏
class University :public school
{
public:
	principal *Vice;//副校长
	University() :school("指针", "就业培训机构", "大庆")//参数列表
	{
		cout << "大学的构造" << endl;
	}
	//虚函数 重写覆盖  名字相同返回值不同 不可重写覆盖
	virtual void SchoolOpens()
	{
		cout << "该学校开学了" << endl;
	}
	~University()
	{
		cout << "调用了该学校析构" << endl;
		delete Vice;
	}
};
//多态思想 可以根据实际情况去拓展程序 多态：父类指针指向子类对象调用子类方法
//不写虚函数 很难实现多态
//虚析构函数是为了解决:在删除指向子类对象的基类指针时可以调用子类的析构函数达到释放子类中堆内存的目的而防止内存泄漏的
void printfSchool(school * school)
{
	school->SchoolOpens();
	delete school;
}
void printfSchool(school & school)
{
	school.SchoolOpens();
	delete &school;
}
void task45()
{
	University u;
	school* s = &u;//school &s1 = u;
	s->SchoolOpens();
	printfSchool(&u);
}
//纯虚函数:定义接口 java:interface 
//虚基类
//虚指针:虚指针指向该类对应的虚函数表
//虚函数表:存储量所有虚函数的函数指针
//虚函数:凡是有虚函数的类，就会有一个虚指针 虚函数就是重写
//调用函数时，发现函数是普通函数，很简单 直接调用
//调用函数时，发现函数是虚函数，通过虚指针找到对应函数去调用
class Nataorium
{
public:
	virtual void  wash() = 0;//纯虚函数  虚基类
};
vector<Nataorium*>allWash;
class A1
{
public:
	virtual void fun()
	{
		cout << "A1的fun" << endl;
	}
	virtual void druck()
	{
		cout << "A1的druck" << endl;
	}
	void eat()
	{
		cout << "A1的eat" << endl;
	}
};
class B :public A1
{
public:
	virtual void fun()
	{
		cout << "B的fun" << endl;
	}
	void eat()
	{
		cout << "B的eat" << endl;
	}
	virtual void druck()
	{
		cout << "B的druck" << endl;
	}
};
void show(A1 *p)
{
	p->druck();
	p->fun();
	p->eat();//eat不是虚函数
}
void task46()
{
	A1 a;
	B b;
	a.druck();
	A1 *pb = &b;
	pb->druck();
	pb->fun();
	cout << "==========================================" << endl;
	show(&a);
	cout << "==========================================" << endl;
	show(&b);
}
//初始化列表
//#define Lassert(t) (/(t))
class vec
{
	int *obj;
	vector<int>arr;
public:
	vec(initializer_list<int> arr)//初始化列表
	{
		obj = new int[arr.size()];
		//迭代
		for (auto i = 0; i < arr.size(); i++)
		{
			obj[i] = *(arr.begin() + i);
		}
		for (auto i = arr.begin(); i != arr.end(); i++)
		{
			cout << *i << endl;
		}
	}
	int& operator[](unsigned int index)
	{
		//assert(index >= 0 && index <arr.size());//断言 为1运行 为0退出
		//Lassert(index>=0&&index<<arr.size());
		return obj[index];
	}
};
void task47()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, };
	vec v = { 1, 2, 3, 4, 5, 6, 7, };//initializer_list<int> 能接收这种类型参数 或 vec v({ 1, 2, 3, 4, 5, 6, 7, });
	cout << v[2] << endl;
	v[2] = 5;
	cout << v[2] << endl;
	//vec tem{ 1, 2, 3 } = vec tem(1, 2, 3); //初始化参数列表
}
//默认构造函数
class tool
{
public:
	int value;
	tool()
	{
		cout << "tool构造了" << endl;
	}
	tool(int t)
	{
		cout << "单参数构造了" << t << endl;
	}
	tool(const tool &)
	{
		cout << "tool拷贝构造了" << endl;
	}
	tool(tool &&)
	{
		cout << "tool移动构造了" << endl;
	}
	~tool()
	{
		cout << "tool析构了" << endl;
	}
	tool& operator=(tool &&)
	{
		cout << "tool 移动赋值了" << endl;
		return *this;//*this当前对象
	}
	tool& operator=(const tool &)
	{
		cout << "tool 拷贝赋值了" << endl;
		return *this;
	}

};
class base
{
	virtual void run(){}
	//virtual void run()const {} //只读不可修改
	//virtual void run() final{} //无法重写  class base final 该base 类不能被继承
};
class S1 :public base
{
	tool t = 2;
	int numb = 5;
public:
	void run() override {}//重写 覆盖
	S1() :t(5){}//初始化列表
	//delete 不让编译器生成默认的
	//default 让编译器生成默认的
	//S1()=delete;
	//S1()=default;
};
void task48()
{
	S1 s;
}
//空指针nullptr
void f(int t)
{
	cout << "int重载函数" << endl;
}
void f(char *p)
{
	cout << "指针重载函数" << endl;
}
void task49()
{
	f(nullptr);//空指针
	f(1);
}
//大端内存 小端内存
void task50()
{
	int a;
	unsigned char *p = (unsigned char *)&a;//(int(p)+sizeof(char*)*n)
	a = 10;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	a = 255;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	a = 256;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	a = 65536;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	//大端内存结果 
	//0  0  0  10   一个字节8位
	//0  0  0  255/1111 1111
	//0  0  1  0    = 256/1 0000 0000
	//0  1  0  0    =65536/1 0000 0000 0000 0000
	//小端内存结果  internet运行效率高 低到高位
	//10  0   0   0
	//255 0   0   0
	//0   1   0   0
	//0   0   1   0
}
//类模板 函数模板
int Lmax(int a, int b)
{
	return a > b ? a : b;
}
double Lmax(double a, double b)
{
	return a > b ? a : b;
}
template <class T> T Lmax(T a, T b)//template <typename T> T Lmax(T a, T b)
{
	return a > b ? a : b;
}
template <int d, class T, class T1> T Lmax(T a, T1 b)
{
	cout << "模板推导函数" << endl;
	return a > b ? a : b;
}
void task51()
{
	int x1 = 2, x2 = 5;
	double d1 = 2.3, d2 = 4.4;
	//隐式推导
	cout << Lmax(x1, x2) << endl;
	cout << Lmax(d1, d2) << endl;
	//显示推导
	cout << Lmax<double>(x1, d1) << endl;
	cout << Lmax<2, int, double>(x1, d1) << endl;
	//显示指定模板，必须使用模板推导的函数，不能使用非模板的函数
	cout << Lmax<2>(d1, d2) << endl;
}
template<class T>void Lswap(T& a, T& b)
{
	T tem = a;
	a = b;
	b = tem;
}
class A3
{
public:
	int value = 0;
	char *p;
	tool * t;
	A3(int v)
	{
		p = new char[100];
		t = new tool;
		value = v;
		cout << "构造函数" << endl;
	}
	//重载某一个类型
	operator int()
	{
		cout << "A3转换为int" << endl;
		return value;
	}
	operator double()
	{
		cout << "A3转换为double" << endl;
		return value;
	}
	//复制赋值运算符
	A3 & operator=(const A3 & other)
	{
		delete p;
		delete t;
		p = new char[100];
		t = new tool;
		value = other.value;
		cout << "复制赋值A3" << endl;
		return *this;
	}
	//移动赋值运算符
	A3 & operator=(A3 && other)
	{
		p = new char[100];
		t = other.t;
		other.t = nullptr;
		value = other.value;
		cout << "移动赋值A3" << endl;
		return *this;
	}
	A3(const A3& other) : A3(other.value)
	{
		cout << "拷贝构造" << endl;
	}
	~A3()
	{
		cout << "析构函数" << endl;
		delete p;
	}
	A3(A3 &&other)
	{
		t = other.t;
		other.t = nullptr;
		value = other.value;
		cout << "移动构造A3" << endl;
	}
};
void Lswap(A &a, A & b)
{
	//tem 里自己的p a里面自己的p b里自己的p
	A tem = a;//深拷贝
	//移动构造 A tem(std::move(a));
	//复制赋值函数 a里是b的p
	a.operator=(b);//浅拷贝
	//移动赋值 a.operator=(std::move(b));
	//b里是tem的p
	b.operator=(tem);
	//移动赋值 b.operator=(std::move(tem));
}
void task52()
{
	int x1 = 2, x2 = 5;
	double d1 = 2.3, d2 = 4.4;
	A3 a1(25);
	A3 a2(31);
	int d = a1.operator int();
	Lswap(a1, a2);
	Lswap(x1, x2);
	Lswap(d1, d2);
	cout << a1.value << " " << "自定义类型交换函数" << "  " << a2.value << endl;
	cout << x1 << " " << "int类型交换函数" << " " << x2 << endl;
	cout << d1 << " " << "double类型交换函数" << " " << d2 << endl;
}
//模板类 栈 先入后出 
template<class T>class L_stack
{
	T a;
	vector<T>arr;
public:
	void push(T &&obj)
	{
		arr.push_back(obj);
	}
	void pop()
	{
		arr.pop_back();
	}
	T & top()
	{
		return arr.back();
	}
	//表示大小size_t
	size_t size()
	{
		return arr.size();
	}
	bool empty()
	{
		return arr.empty();
	}
};
//模板参数包 拆包
//print 的功能 传入任意多的参数，全输出到屏幕上
void run3(int){}
void Lprint()
{
	cout << "递归拆包终结" << endl;
}
template<class firstArgs, class...args>void Lprint(firstArgs f, args...d)
{
	cout << f << endl;
	//run3(d...);
	Lprint(d...);//递归拆包
}
void task53()
{
	Lprint(1, 3.0, 5, "123");
	L_stack<int> l;
	l.push(5);
	l.push(6);
	l.push(7);
	cout << l.top() << endl;
	l.pop();
	cout << l.top() << endl;
	cout << l.size() << endl;
}
//智能指针 管理指针 一种对象，能够管理一个对象释放
//堆区 空间大 由程序员管理 delete new 
//栈区 存储调用函数的过程需要的数据  系统自动管理
//代码区  存储所以代码  只读 不能修改
//常量区   所有常量 不可以修改
//静态区  所有静态成员对象变量 可以修改 不能删除  非静态全局变量也存放静态区  静态全局变量 静态局部变量 全局变量  
//所有区都是内存 都有对应地址
//模板化，可以接受任意类型
//构造方法，赋值一个指针
//析构方法，释放指针
//不标准的复制构造（转移内部指针控制权）
//不标准的复制赋值（转移内部指针的控制权）
//reset 释放之前的 获得新的指针
// release（） 释放控制权，返回指针
//operator*() 模拟指针访问方法
//operatpr->() 模拟指针箭头访问方法
//get（） 获得指针指向的指针
template<class T>
class L_autoPtr
{
	T *obj = nullptr;
public:
	L_autoPtr(T *ptr) :obj(ptr){}
	L_autoPtr() = default;
	~L_autoPtr()
	{
		delete obj;
	}
	L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release()){}
	L_autoPtr & operator=(L_autoPtr<T>& ptr)
	{
		obj = ptr.release();
		return *this;
	}
	void reset(T * newPtr = nullptr)
	{
		delete obj;
		obj = newPtr;
	}
	T * release()
	{
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	T & operator*()
	{
		return *obj;
	}
	T * operator->()
	{
		return obj;
	}
	T * get()
	{
		return obj;
	}
};
void run4()
{
	auto_ptr<tool> ptr(new tool);
	auto_ptr<tool> ptr2(ptr);//ptr2析构
	auto_ptr<tool> ptr3;
	L_autoPtr<tool> ptr4(new tool);
	L_autoPtr<tool> ptr5(ptr4);
	L_autoPtr<tool> ptr6;
	ptr3 = ptr2;//ptr3有东西 ptr ptr2空
	cout << (*ptr5).value << endl;
	cout << ptr5->value << endl;
	ptr5.reset();//销毁被管理对象
}
void task54()
{
	char *p = "123456";//p存放栈区 123456存放常量区
	//T * t = new T();//T存放堆区 t存放栈区
	run4();
}
void main()
{
	//task38();//异常问题
	//task39();//拷贝构造 深拷贝 浅拷贝
	//task40();//移动构造
	//task41();//构造和析构
	//task42();//指针与引用  空指针 在C++中，NULL却被明确定义为整常数0(int):
	//task43();//友元
	//task44();//重载运算符
	//task45();//继承
	//task46();//虚指针
	//task47();//初始化列表 断言 迭代器
	//task48();//默认构造函数
	//task49();//空指针  在C++中，NULL却被明确定义为整常数0（int）:
	//task50();//大端内存 小端内存
	//task51();//模板函数比较大小
	//task52();//模板函数交换
	//task53();//模板类[ 栈 先入后出] 模板参数包 拆包
	task54();//智能指针
}