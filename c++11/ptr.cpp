#include<iostream>
using namespace std;
#include<memory>//�ڴ� ����ָ��
class tool
{
public:
	int value;
	tool()
	{
		cout << "tool������" << endl;
	}
	tool(int t)
	{
		cout << "������������" << t << endl;
	}
	tool(const tool &)
	{
		cout << "tool����������" << endl;
	}
	tool(tool &&)
	{
		cout << "tool�ƶ�������" << endl;
	}
	~tool()
	{
		cout << "tool������" << endl;
	}
	tool& operator=(tool &&)
	{
		cout << "tool �ƶ���ֵ��" << endl;
		return *this;//*this��ǰ����
	}
	tool& operator=(const tool &)
	{
		cout << "tool ������ֵ��" << endl;
		return *this;
	}

};
//auto_ptr ������������ʹ�� auto_ptr ����Ŀ����͸�ֵ������ת��ָ���ӵ��Ȩ���뿪�������Զ��ͷ�ָ�� �����ƶ�����move
//unique_ptr ��һ�޶�  ��ֹ��������͸�ֵ����  �����ƶ�������ƶ���ֵ  �����Զ��ͷŶ�Ӧָ��  ջ��  һ������ָ��ֻ�ܶ�Ӧһ������ �����ڶ�����ջ��
//shared_ptr ����   ���Կ����� ���ü����� shared_ptr��ָ�����ü��� shared_ptrɾ�������� ���ü���-1�� shared_ptr ��������ֵ ���ü���+1���ƶ� ���ü������䡣 �����ü���Ϊ0 ��������. һ�������Ӧһ�����ö���  �������ָ�����ָ��ͬһ���ü���  ����ѭ������ 
//weak_ptr �ֲ�shared_ptr��ѭ������ȱ�� ��������������ָ��ʹ��  ��������ʱ�ٻ�shared_ptrʹ��
//shared_ptrѭ����������  ���shared_ptrѭ����������
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
	auto_ptr<tool> ptr2(ptr);//ptr2����
	auto_ptr<tool> ptr3;
	L_autoPtr<tool> ptr4(new tool);
	L_autoPtr<tool> ptr5(ptr4);
	L_autoPtr<tool> ptr6;
	ptr3 = ptr2;//ptr3�ж��� ptr ptr2��
	cout << (*ptr5).value << endl;
	cout << ptr5->value << endl;
	ptr5.reset();//���ٱ��������
}
void task54()
{
	char *p = "123456";//p���ջ�� 123456��ų�����
	//T * t = new T();//T��Ŷ��� t���ջ��
	run4();
}
struct ListNode
{
	//shared_ptr<ListNode>_prev;//shared_ptrѭ����������
	//shared_ptr<ListNode>_next;
	weak_ptr<ListNode>_prev;//���shared_ptrѭ����������
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
	//node1�ȴ� ���ü���a ���� Ȼ������
	//���ü���a �ȴ�node2->pre ����
	//node2->pre�ȴ�node2����
	//node2�ȴ� ���ü���b���� Ȼ������
	//���ü���b�ȴ�node1->next ����
	//node1->next �ȴ�node1 ����
	//node1 �ȴ�........��ѭ��...
}
void task55()
{
	unique_ptr<tool>ptr5(new tool);
	unique_ptr<tool>ptr6(move(ptr5));
	unique_ptr<tool>ptr7;
	ptr7.swap(ptr6);//����Ҫ��ת����
	//swap(ptr3,ptr2);��Ҫ��ת���󽻻�
	ptr7 = move(ptr6);
	shared_ptr<tool>ptr(new tool);
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	shared_ptr<tool>ptr2(ptr);
	shared_ptr<tool>ptr3;
	ptr3 = ptr2;
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	cout << "��ǰ���ü���" << ptr2.use_count() << endl;
	cout << "��ǰ���ü���" << ptr3.use_count() << endl;
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
//��Դ������
template<class T>class Ref
{
	//��ǰ��Դ����
	int r_count = 0;
	T *object = nullptr;
public:
	Ref(T * target) :object(target)
	{
		++r_count;
	}
	//����:���ܸ� 
	inline void increase()//����
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
// shared ����ָ����Ҫ�ķ���
//�޲ι��졢����ָ�빹�졢�������졢�ƶ����졢������ֵ���ƶ���ֵ
//reset(T*)�滻����   reset()���ٶ���  
//operator*���� operator->() 
//get()�����ָ�� ues_count()������ü���  
//unique�����жϵ�ǰ�Ƿ�Ψһ   use_count()==1    
//operator bool()�Ƿ��������
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
	//�жϵ�ǰ����ָ���Ƿ�Ͷ������
	operator bool()
	{
		return ref != nullptr;
	}
};
//����ָ��һ�����ü�����������Ҫʱ��� shared_ptr 
//�޲ι��� ����һ��shared_ptr ����
//��������  �ƶ����� 
//use_count()���ָ����������ü�����shared_ptr�ļ�����
//lock() ���һ��shared_ptr 
//expired()�ж��Ƿ��Ѿ�ɾ��
//swap()
//reset()
template<class T>class LweakPtr
{
	Ref<T>*ref = nullptr;
public:
	//�޲ι���
	LweakPtr() = default;
	//����һ��shared_ptr ����
	LweakPtr(LsharedPtr<T>& other) :ref(other.ref)
	{
		cout << "ʹ��shared����һ��weak" << endl;
		if (ref)
		{
			ref->increase_w();
		}
	}
	//��������
	LweakPtr(const LweakPtr<T> & other) :ref(other.ref)
	{
		if (ref)
		{
			ref->increase_w();
		}
	}
	//�ƶ�����
	LweakPtr(LweakPtr<T>&& other)
	{
		swap(ref, other.ref);
	}
	//������ֵ
	LweakPtr<T> & operator=(const LweakPtr<T> & other)
	{
		cout << "������weak������ֵ�����" << endl;
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
	//�ƶ���ֵ
	LweakPtr<T> & operator=(LweakPtr<T> && other)
	{
		cout << "������weak�ƶ���ֵ�����" << endl;
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
	//��ֵ����
	LsharedPtr<T> lock()
	{
		LsharedPtr<T> tem(ref);
		return tem;
	}
	//�������д���ŵ� �ṹ���� �Ĵ����� ��չ����
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
	//LsharedPtr<ListNode1>_prev1;//shared_ptrѭ����������
	//LsharedPtr<ListNode1>_next1;
	LweakPtr<ListNode1>_prev1;//���shared_ptrѭ����������
	LweakPtr<ListNode1>_next1;
	ListNode1()
	{
		cout << "�ڵ��ѹ���" << endl;
	}
	~ListNode1()
	{
		cout << "�ڵ�������" << endl;
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
	//ptr7.swap(ptr6);//����Ҫ��ת����
	//swap(ptr3,ptr2);//��Ҫ��ת���󽻻�
	ptr7 = move(ptr6);
	LsharedPtr<tool>ptr(new tool);
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	LsharedPtr<tool>ptr2(ptr);
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	cout << "��ǰ���ü���" << ptr2.use_count() << endl;
	LsharedPtr<tool>ptr3;
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	cout << "��ǰ���ü���" << ptr2.use_count() << endl;
	cout << "��ǰ���ü���" << ptr3.use_count() << endl;
	ptr3 = ptr2;
	cout << "��ǰ���ü���" << ptr.use_count() << endl;
	cout << "��ǰ���ü���" << ptr2.use_count() << endl;
	cout << "��ǰ���ü���" << ptr3.use_count() << endl;
}
void task57()
{
	test_shared_ptr();
}