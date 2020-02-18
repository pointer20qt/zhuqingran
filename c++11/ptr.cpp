#include<iostream>
using namespace std;
#include<memory>//内存 智能指针
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
//auto_ptr 被遗弃不建议使用 auto_ptr 对象的拷贝和赋值操作会转移指针的拥有权。离开作用域自动释放指针 不可移动构造move
//unique_ptr 独一无二  禁止拷贝构造和赋值操作  可以移动构造和移动赋值  析构自动释放对应指针  栈区  一个智能指针只能对应一个对象 对象在堆区或栈区
//shared_ptr 共享   可以拷贝。 引用计数。 shared_ptr会指向引用计数 shared_ptr删除、析构 引用计数-1。 shared_ptr 拷贝，赋值 引用计数+1。移动 引用计数不变。 当引用计数为0 对象析构. 一个对象对应一个引用对象  多个智能指针可以指向同一引用计数  容易循环引用 
//weak_ptr 弥补shared_ptr的循环引用缺陷 不能完整当智能指针使用  但可以随时召唤shared_ptr使用
//shared_ptr循环引用问题  解决shared_ptr循环引用问题
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
struct ListNode
{
	//shared_ptr<ListNode>_prev;//shared_ptr循环引用问题
	//shared_ptr<ListNode>_next;
	weak_ptr<ListNode>_prev;//解决shared_ptr循环引用问题
	weak_ptr<ListNode>_next;
	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};
void test_shared_ptr_cycle_ref()
{
	shared_ptr<ListNode>node1(new ListNode);
	shared_ptr<ListNode>node2(new ListNode);
	node1->_next = node2;
	node2->_prev = node1;
	//node1等待 引用计数a 归零 然后析构
	//引用计数a 等待node2->pre 析构
	//node2->pre等待node2析构
	//node2等待 引用计数b归零 然后析构
	//引用计数b等待node1->next 析构
	//node1->next 等待node1 析构
	//node1 等待........死循环...
}
void task55()
{
	unique_ptr<tool>ptr5(new tool);
	unique_ptr<tool>ptr6(move(ptr5));
	unique_ptr<tool>ptr7;
	ptr7.swap(ptr6);//不需要中转对象
	//swap(ptr3,ptr2);需要中转对象交换
	ptr7 = move(ptr6);
	shared_ptr<tool>ptr(new tool);
	cout << "当前引用计数" << ptr.use_count() << endl;
	shared_ptr<tool>ptr2(ptr);
	shared_ptr<tool>ptr3;
	ptr3 = ptr2;
	cout << "当前引用计数" << ptr.use_count() << endl;
	cout << "当前引用计数" << ptr2.use_count() << endl;
	cout << "当前引用计数" << ptr3.use_count() << endl;
}
template<class T>class L_uniquePtr
{
	T *obj = nullptr;
public:
	L_uniquePtr(T *ptr) :obj(ptr){}
	L_uniquePtr() = default;
	~L_uniquePtr()
	{
		delete obj;
	}
	L_uniquePtr& operator=(const L_autoPtr<T>&) = delete;
	L_uniquePtr(L_autoPtr<T>&& ptr) :obj(ptr.release()){}
	L_uniquePtr & operator=(L_autoPtr<T>&& ptr)
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
	/*void swap(L_uniquePtr & other)
	{
	swap(obj, other.obj);
	}*/
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
//资源计数类
template<class T>class Ref
{
	//当前资源计数
	int r_count = 0;
	T *object = nullptr;
public:
	Ref(T * target) :object(target)
	{
		++r_count;
	}
	//内联:性能高 
	inline void increase()//增加
	{
		r_count++;
	}
	inline void reduce()
	{
		r_count--;
		if (r_count == 0)
		{
			delete object;
			delete this;
		}
	}
	T *get()
	{
		return object;
	}
	int getCount()
	{
		return r_count;
	}
};
// shared 智能指针需要的方法
//无参构造、传递指针构造、拷贝构造、移动构造、拷贝赋值、移动赋值
//reset(T*)替换对象   reset()销毁对象  
//operator*（） operator->() 
//get()获得裸指针 ues_count()获得引用计数  
//unique（）判断当前是否唯一   use_count()==1    
//operator bool()是否关联对象
template<class T>class LsharedPtr
{
	Ref<T> * ref = nullptr;
public:
	LsharedPtr() = default;
	~LsharedPtr()
	{
		if (ref)
		{
			ref->reduce();
		}
	}
	LsharedPtr(T *newP)
	{
		ref = new Ref<T>(newP);
	}
	LsharedPtr(const LsharedPtr & other)
	{
		ref = other.ref;
		if (ref)
		{
			ref->increase();
		}
	}
	LsharedPtr(LsharedPtr && other)
	{
		swap(ref, other.ref);
	}
	LsharedPtr & operator=(const LsharedPtr& other)
	{
		if (ref)
		{
			ref->reduce();
		}
		ref = other.ref;
		if (ref)
		{
			ref->increase();
		}
		return *this;
	}
	LsharedPtr & operator=(LsharedPtr &&other)
	{
		if (ref)
		{
			ref->reduce();
		}
		ref = other.ref;
		other.ref = nullptr;
		return *this;
	}
	void swap(LsharedPtr & other)
	{
		swap(ref, other.ref);
	}
	void reset(T * target = nullptr)
	{
		if (ref)
		{
			ref->reduce();
		}
		if (target != nullptr)
		{
			ref = new Ref<T>(target);
		}
		else
		{
			ref = nullptr;
		}
	}
	T& operator *()
	{
		if (ref)
		{
			return ref->get();
		}
		else
		{
			return (T *)nullptr;
		}
	}
	T *get()
	{
		if (ref)
		{
			return ref->get();
		}
		else
		{
			return (T *)nullptr;
		}

	}
	int use_count()
	{
		if (ref)
		{
			return ref->getCount();
		}
		else
		{
			return 0;
		}
	}
	bool unique()
	{
		if (ref)
		{
			return ref->getCount() == 1;
		}
		else
		{
			return false;
		}
	}
	//判断当前智能指针是否和对象关联
	operator bool()
	{
		return ref != nullptr;
	}
};
//可以指定一个引用计数对象，在需要时获得 shared_ptr 
//无参构造 传递一个shared_ptr 构造
//拷贝构造  移动构造 
//use_count()获得指定对象的引用计数（shared_ptr的计数）
//lock() 获得一个shared_ptr 
//expired()判断是否已经删除
//swap()
//reset()
template<class T>class LweakPtr
{
	Ref<T>*ref = nullptr;
public:
	//无参构造
	LweakPtr() = default;
	//传递一个shared_ptr 构造
	LweakPtr(LsharedPtr<T>& other) :ref(other.ref)
	{
		cout << "使用shared构造一个weak" << endl;
		if (ref)
		{
			ref->increase_w();
		}
	}
	//拷贝构造
	LweakPtr(const LweakPtr<T> & other) :ref(other.ref)
	{
		if (ref)
		{
			ref->increase_w();
		}
	}
	//移动构造
	LweakPtr(LweakPtr<T>&& other)
	{
		swap(ref, other.ref);
	}
	//拷贝赋值
	LweakPtr<T> & operator=(const LweakPtr<T> & other)
	{
		cout << "调用了weak拷贝赋值运算符" << endl;
		if (ref)
		{
			ref->reduce_w();
		}
		ref = other.ref;
		if (ref)
		{
			ref->increase_w();
		}
		return *this;
	}
	//移动赋值
	LweakPtr<T> & operator=(LweakPtr<T> && other)
	{
		cout << "调用了weak移动赋值运算符" << endl;
		if (ref)
		{
			ref->reduce_w();
		}
		ref = other.ref;
		other.ref = nullptr;
		return *this;
	}
	int use_count()
	{
		if (ref)
			return ref->getCount();
		else
			return 0;
	}
	bool expired()
	{
		if (ref)
			return ref->getCount() >0;
		else
			return false;
	}
	//右值对象
	LsharedPtr<T> lock()
	{
		LsharedPtr<T> tem(ref);
		return tem;
	}
	//面向对象写法优点 结构清晰 改错容易 扩展方便
	void swap(LweakPtr<T> &other)
	{
		swap(ref, other.ref);
	}
	void reset()
	{
		ref->increase_w();
		ref = nullptr;
	}
};
struct  ListNode1
{
	//LsharedPtr<ListNode1>_prev1;//shared_ptr循环引用问题
	//LsharedPtr<ListNode1>_next1;
	LweakPtr<ListNode1>_prev1;//解决shared_ptr循环引用问题
	LweakPtr<ListNode1>_next1;
	ListNode1()
	{
		cout << "节点已构造" << endl;
	}
	~ListNode1()
	{
		cout << "节点已析构" << endl;
	}
};
void test_shared_ptr()
{
	LsharedPtr<ListNode1>node3 = (new ListNode1);
	LsharedPtr<ListNode1>node4 = (new ListNode1);
	cout << node3->_next1.use_count() << endl;
	node3->_next1.operator = (node4);
	node4->_prev1.operator = (node3);
	cout << node3.use_count() << endl;
}
void task56()
{
	cout << "------------------------------------------" << endl;
	L_uniquePtr<tool>ptr5(new tool);
	L_uniquePtr<tool>ptr6(move(ptr5));
	L_uniquePtr<tool>ptr7;
	//ptr7.swap(ptr6);//不需要中转对象
	//swap(ptr3,ptr2);//需要中转对象交换
	ptr7 = move(ptr6);
	LsharedPtr<tool>ptr(new tool);
	cout << "当前引用计数" << ptr.use_count() << endl;
	LsharedPtr<tool>ptr2(ptr);
	cout << "当前引用计数" << ptr.use_count() << endl;
	cout << "当前引用计数" << ptr2.use_count() << endl;
	LsharedPtr<tool>ptr3;
	cout << "当前引用计数" << ptr.use_count() << endl;
	cout << "当前引用计数" << ptr2.use_count() << endl;
	cout << "当前引用计数" << ptr3.use_count() << endl;
	ptr3 = ptr2;
	cout << "当前引用计数" << ptr.use_count() << endl;
	cout << "当前引用计数" << ptr2.use_count() << endl;
	cout << "当前引用计数" << ptr3.use_count() << endl;
}
void task57()
{
	test_shared_ptr();
}