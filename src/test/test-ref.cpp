#include "core/Ref.h"

class Res: public Reference{

public:
	Res(){
		printf("Res 1\n");
	}
	virtual ~Res(){
		printf("Res 2\n");
	}
};

int main()
{	
	Res r1;
	Ref<Res> ptr = new Res();
	Ref<Res> ptr1(ptr);
	ptr1 = ptr;
	
	
	
	ptr1 = new Res();
	ptr1 = new Res();
	ptr1 = new Res();
	ptr1 = new Res();
	ptr1 = new Res();

	Ref<Res> ppp = ptr1;
	ppp = ptr1;
	ppp = ptr1;
	ppp = ptr1;
	ppp = ptr1;

	return 0;
}