/** Main function for HW1
 *
 * Make sure your program runs with this.
 */

#include <iostream>
#include "threadLocal_test.cpp"

//int test_threadLocal();

int main(){
	int err = test_threadLocal();
    std::cout<< "\n\nNumber of errors= "<<err<<"\n\n";
}


