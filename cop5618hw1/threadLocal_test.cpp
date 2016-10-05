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
    cop5618::threadLocal<std::string> threadLocalVariable1;
    cop5618::threadLocal<int> threadLocalVariable2;
    threadLocalVariable1.set("M");
    std::thread th1(&cop5618::threadLocal<std::string>::set,&threadLocalVariable1,"1");
    std::thread th2(&cop5618::threadLocal<std::string>::set,&threadLocalVariable1,"2");
    std::thread th3(&cop5618::threadLocal<std::string>::set,&threadLocalVariable1,"3");
    std::thread th4(&cop5618::threadLocal<int>::set,&threadLocalVariable2,4);
    std::thread th5(&cop5618::threadLocal<int>::set,&threadLocalVariable2,5);
//std::thread th2(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
//	std::thread th(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
//th = std::thread(&cop5618::threadLocal<std::string>::get,&threadLocalVariable);
	th1.join();
	th2.join();
    th3.join();
    th4.join();
    th5.join();
    threadLocalVariable1.get();
    return errors;
}
