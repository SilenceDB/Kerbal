#include "exe_serve.h"

using namespace std;

unsigned long start_time = 0;
bool debug = false;

void program_start(bool is_debug)
{
	start_time = GetTickCount();
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << PRODUCT_NAME << " [�汾 " << VER_STRING << "]\n" << "(c) " << COMPANY_NAME << "����������Ȩ����" << endl;
	/*
	 Microsoft Windows [�汾 10.0.14393]
	 (c) 2016 Microsoft Corporation����������Ȩ����
	 */

	cout << "����Ʒ��Ȩ��" << get_user_name() << "ʹ��\n" << endl;
	/*
	 ����Ʒ��Ȩ��Peterʹ��
	 */

	/*	cout << __LINE__ << endl;
	cout << __FILE__ << endl;
	cout << __DATE__ << endl;
	cout << __TIME__ << endl;
	 cout << __STDC__ << endl;*/

	debug = is_debug;
}

unsigned long show_time_cost()
{
	unsigned long time_cost = GetTickCount() - start_time;
	cout << "\n���к�ʱ " << time_cost << " ms" << endl;
	return time_cost;
}

bool program_will_end()
{
	show_time_cost();
	char if_redo;

	const bool wait = false;
	if (wait) {
		printf("Press any key to continue...");
		scanf("%c", &if_redo);
		printf("%c\n", if_redo);
		if (if_redo == 'y' || if_redo == 'Y') {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//template <class T>
//string get_typename(T &a)
//{
//	typeid(a).name()<<endl;
//}

//template <class T>
//void print_bit2(T a)
//{
//	for(int i=8*sizeof(a)-1; i>=0; i--) {
//		cout<<( (a>>i)&1 );
//		if(i%8==0)
//			cout<<" ";
//	}
//	cout<<"\n";
//}

#pragma comment(lib,"Advapi32.lib")
string get_user_name()
{
	char strBuffer[256] = { 0 };
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return string(strBuffer);
}

class dbstream
{
	private:
		bool swit;

	public:
		dbstream()
		{
			swit = true;
		}

		void why_cannot_use()
		{
			if (debug == true) {
			} else {
				cout << "ֻ���ڵ���program_start����ʱ,is_debugֵ�������true,����������Ż������Ϣ" << endl;
			}
		}
		template <class T> friend dbstream& operator <<(dbstream&, T&);

};

#define enddb "enddb"
#include <iomanip>
//#include "basic_math.h"
template <class T>
dbstream& operator <<(dbstream& output, T&z)
{
	if (debug == true) {
		if (output.swit == true) {
			cout << "- ";
			output.swit = false;
		}

		/*if(strcmp((char*)(&z),"\n")==0) {
		 cout<< "\n  ";
		 } else*/if (strcmp((char*) (&z), enddb) == 0) {
			output.swit = true;
			cout << endl;
		} else {
			if (typeid(T).name() == typeid(double).name() || typeid(T).name() == typeid(float).name()) {
				cout << z;
			} else {
				cout << z;
			}

		}
	}

	return output;
}
dbstream cdb;
