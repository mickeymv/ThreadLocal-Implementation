/*
 * threadLocal.h
 *  Start with this and add what is necessary
 */

#ifndef THREADLOCAL_H_
#define THREADLOCAL_H_

#include <iostream>
#include <unordered_map>
#include <exception>  //for std::exception
#include <mutex>      //for std::mutex and std::lock_guard

namespace cop5618 {

    /**
     * Custom exception to throw when an attempt is made to remove get a variable which has not been set.
     * It inherits from std::exception and overrides
     * the what method to return an appropriate message.
     */
    struct variable_not_set: public std::exception{
        
        
        virtual const char* what() const throw(){
            return "Exception! : Attempting to retrieve a variable which was not set! ";
        }
    };

    
template <typename T>
class threadLocal {
public:
	threadLocal();
	~threadLocal();

	//disable copy, assign, move, and move assign constructors
	 threadLocal(const threadLocal&)=delete;
	 threadLocal& operator=(const threadLocal&)=delete;
	 threadLocal(threadLocal&&)=delete;
	 threadLocal& operator=(const threadLocal&&)=delete;

	 /**
	 * Returns the current thread's value.
	 * If no value has been previously set by this
	 * thread, an out_of_range exception is thrown.
	 */
	const T& get() const;


	/**
	 * Sets the value of the threadLocal for the current thread
	 * to val.
	 */
	void set(T val);

	/**
	 * Removes the current thread's value for the threadLocal
	 */
	void remove();

	/**
	 * Friend function.  Useful for debugging only
	 */
	template <typename U>
	friend std::ostream& operator<< (std::ostream& os, const threadLocal<U>& obj);

private:
	
    std::unordered_map<std::string, T> map;



};

//ADD DEFINITIONS

} /* namespace cop5618 */

#endif /* THREADLOCAL_H_ */
