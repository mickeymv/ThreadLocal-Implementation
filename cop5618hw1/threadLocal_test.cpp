//
//  threadLocal_test.cpp
//  cop5618hw1
//
//  Created by Mickey Vellukunnel on 10/4/16.
//  Copyright © 2016 University of Florida. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "threadLocal.h"

//void is_main_thread();

int test_threadLocal() {
    //should run test suite and return number of errors.
	int errors = 0;
    cop5618::threadLocal<std::string> threadLocalVariable;
    threadLocalVariable.set("I am the main thread!");
    std::thread th(&cop5618::threadLocal<std::string>::set,&threadLocalVariable,"I am th thread!");
std::thread th5(&cop5618::threadLocal<std::string>::set,&threadLocalVariable,"I am 5 thread!");
std::thread th2(&cop5618::threadLocal<std::string>::set,&threadLocalVariable,"I am 2 thread!");
std::thread th3(&cop5618::threadLocal<std::string>::set,&threadLocalVariable,"I am 3 thread!");
std::thread th4(&cop5618::threadLocal<std::string>::set,&threadLocalVariable,"I am 4 thread!");    
//std::thread th2(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
//	std::thread th(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
//th = std::thread(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
	th.join();
	th2.join();
th3.join();
th4.join();
th5.join();
    threadLocalVariable.get();
    return errors;
}
