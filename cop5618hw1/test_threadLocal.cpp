//
//  threadLocal_test.cpp
//  cop5618hw1
//
//  Created by Mickey Vellukunnel on 10/4/16.
//  Copyright © 2016 University of Florida. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include "threadLocal.h"

int test_threadLocal1(int num_threads);
int test_threadLocal2(int num_threads);
int test_threadLocal3(int num_threads);
int test_threadLocal4(int num_threads);


int test_threadLocal() {
    //should run test suite and return number of errors.
	int numOfErrors = 0;
    cop5618::threadLocal<std::string> threadLocalStringVariable;
    cop5618::threadLocal<int> threadLocalVariable2;
    threadLocalStringVariable.set("M");
    numOfErrors += test_threadLocal1(10);
    numOfErrors += test_threadLocal2(10);
    numOfErrors += test_threadLocal3(10);
    numOfErrors += test_threadLocal4(2);
    threadLocalStringVariable.get();
    return numOfErrors;
}


/**
 * test_threadLocal1 tests having int variables
 *
 */
int test_threadLocal1(const int num_threads) {
    std::vector<std::thread> threads;
    cop5618::threadLocal<int> threadLocalIntVariable;
    
    std::atomic<int> sequencer(1);
    
    for (int t = 0; t < num_threads; t++) {
        threads.push_back(
                          std::thread(
                                      [&sequencer, &threadLocalIntVariable]() mutable ->void
                                      {
                                        threadLocalIntVariable.set(sequencer++);
                                        threadLocalIntVariable.get();
                                      }
                                      )
                          );
        
    }
    
    //join all the threads
    std::for_each(threads.begin(), threads.end(),
        std::mem_fn(&std::thread::join));
    
    return 0;
}

/**
 * test_threadLocal2 tests having string variables
 *
 */
int test_threadLocal2(const int num_threads) {
    std::vector<std::thread> threads;
    cop5618::threadLocal<std::string> threadLocalStringVariable;
    
    std::atomic<int> sequencer(1);
    
    for (int t = 0; t < num_threads; t++) {
        threads.push_back(
                          std::thread(
                                      [&sequencer, &threadLocalStringVariable]() mutable ->void
                                      {
                                        threadLocalStringVariable.set(std::to_string(sequencer++));
                                        threadLocalStringVariable.get();
                                      }
                                      )
                          );
        
    }
    
    //join all the threads
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    
    return 0;
}

/**
 * test_threadLocal3 tests if the values being returned are the ones that should.
 *
 */
int test_threadLocal3(const int num_threads) {
    std::vector<std::thread> threads;
    cop5618::threadLocal<int> threadLocalIntVariable;
    
     std::vector<int> threadValues(num_threads+1); //Thread at position 1 should have value 1

    
    std::atomic<int> sequencer(1);
    
    for (int t = 0; t < num_threads; t++) {
        threads.push_back(
                          std::thread(
                                      [&sequencer, &threadLocalIntVariable, &threadValues]() mutable ->void
                                      {
                                          int position = sequencer++;
                                          threadLocalIntVariable.set(position);
                                           threadValues[position] = threadLocalIntVariable.get();
                                      }
                                      )
                          );
        
    }
    
    //join all the threads
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    int errors = 0;
    for(int i = 1; i <= num_threads; i++) {
        if(threadValues.at(i) != i) { //Thread at position 1 should have value 1
            std::cout << "\nError! : Value set and returned at postition '"<< i <<"' is not as expected! Got value= '" << threadValues.at(i) <<"'"<< std::endl;
            errors++;
        }
    }
    
    return errors;
}

/**
 * test_threadLocal4 tests getting int values before setting (/initialization)
 *
 */
int test_threadLocal4(const int num_threads) {
    std::vector<std::thread> threads;
    cop5618::threadLocal<int> threadLocalIntVariable;
    std::atomic<int> errors(0);
    
    for (int t = 0; t < num_threads; t++) {
        threads.push_back(
                          std::thread(
                                      [&errors, &threadLocalIntVariable]() mutable ->void
                                      {
                                          try {
                                          threadLocalIntVariable.get();
                                          //If exception is not thrown, then it is an error, since these thread do not set/initialize their variables.
                                              errors++;
                                          } catch (std::exception& e) {
                                              //If exception is thrown, then it is correct behaviour, since these thread do not set/initialize their variables, and hence an exception is thrown.
                                          }
                                      }
                                      )
                          );
        
    }
    
    //join all the threads
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    
    return errors;
}



