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
#include <thread>     // std::thread, std::thread::id, std::this_thread::get_id


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
    
private:
    
    //Backing Map data structure which maps the thread-ids to their local variable values
    std::unordered_map<std::thread::id, T> backing_map;
    
    //std::thread::id main_thread_id = std::this_thread::get_id();
    
    
    /**
     * We will use this mutex to guard all accesses to data.
     */
    //mutable std::mutex m;  //a mutex.
    
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
    /*
    void is_main_thread() {
        if ( main_thread_id == std::this_thread::get_id() )
            std::cout << "This is the main thread.\n";
        else
            std::cout << "This is not the main thread.\n";
    }
     */
    
}; //class threadLocal
    
    
    /** Below are the definitions of the methods.
     */
//ADD DEFINITIONS
    
template<typename T>
threadLocal<T>::threadLocal() {
}

template<typename T>
threadLocal<T>::~threadLocal() {
	remove();
}

    /**
     * As the previous methods, this uses the mutex m to guard access to the
     * shared backing_map data structure, backing_map.
     */
    template<typename T>
    void threadLocal<T>::set(T val) {
        //std::lock_guard<std::mutex> lock(m);
	std::thread::id threadId = std::this_thread::get_id();
        backing_map[threadId] = val;
	std::cout << "\n\nFor thread: "<<threadId<<", Variable set= "<<backing_map.at(threadId)<<"\n";
    }
    
    template<typename T>
    const T& threadLocal<T>::get() const {
        //std::lock_guard<std::mutex> lock(m);
	std::thread::id threadId = std::this_thread::get_id();
        if (backing_map.find(threadId) != backing_map.end()) {
            std::cout << "\n\nIn get! Variable=  "<<backing_map.at(threadId)<<"\n";
        }
	else
            throw variable_not_set();
        return backing_map.at(threadId);;
    }

template<typename T>
    void threadLocal<T>::remove() {
        //std::lock_guard<std::mutex> lock(m);
        std::thread::id threadId = std::this_thread::get_id();
        std::cout << "\n\nFor thread: "<<threadId<<", going to remove variable= "<<backing_map.at(threadId)<<"\n";
	backing_map.erase(threadId);
        //std::cout << "\n\nFor thread: "<<threadId<<", Variable set! "<<backing_map.at(threadId)<<"\n";
    }
    
} /* namespace cop5618 */

#endif /* THREADLOCAL_H_ */
